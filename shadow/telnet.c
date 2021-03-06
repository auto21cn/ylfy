// telnet.c

#include <net/socket.h>
#include <ansi.h>

inherit F_SHADOW;

static string from_user;        // 用户发送来的信息
static int fd;                  // 连接远端机器的套接字
static string dest_addr;        // 连接远端机器的地址
static int port;                // 连接远端机器的端口号

#define MAX_PENDING_INPUT               16384

// 取消所有人物的基本属性

private void send_to_remote();

void init()
{
}

int is_telneting() { return 1; }

string query_dest_addr() { return sprintf("%s %d", dest_addr, port); }

void telnet_input(string str)
{
	if ( str == "CLOSE" )
	{
		write(HIW"用户断开了连接。\n"NOR);
		destruct(this_object());
		return;
	}

	input_to("telnet_input");

	if ( strlen(str) + strlen(from_user) < MAX_PENDING_INPUT )
	{
		from_user += str + "\n";
		if ( find_call_out("send_to_remote") == -1 )
			send_to_remote();
	} 
	else
		write(HIY"你输入的太多了...\n"NOR);
}

int clean_up()
{
	if ( query_shadow_now() )
		return 1;

	destruct(this_object());
	return 0;
}

void connect_to(string arg)
{
	if ( sscanf(arg, "%s %d", dest_addr, port) != 2 )
	{
		write("网络地址错误。\n");
		return;
	}

	write(HIW"正在连接服务器("+dest_addr+" "+port+")，请稍候...\n"NOR);
	from_user = "";
	resolve(dest_addr, "telnet_resolve_callback");
	input_to("telnet_input");
}

void telnet_resolve_callback(string address, string resolved, int key)
{
	int ret;
	object sob;
	string full_addr;

	if ( !objectp(sob = query_shadow_now()) )
	{
		destruct(this_object());
		return;
	}

	if ( !resolved )
	{ // 解析域名失败
		// 是 IP 不用解析
		if ( sscanf(dest_addr, "%*d.%*d.%*d.%*d") == 4 )
			resolved = dest_addr;
		else
		{
			message("telnet", HIW"域名解析失败\n"NOR, sob);
			return;
		}
	}
	else if ( resolved != dest_addr ) 
		message("telnet", HIW"解析域名："+dest_addr+" = "+resolved+"\n"NOR, sob);

	full_addr = sprintf("%s %d", resolved, port);
	fd = socket_create(STREAM, "telnet_read_callback", "telnet_close_callback" );
	
	if ( fd < 0 )
	{
		message("telnet", HIW"连接初始化错误\n"NOR, sob);
		sob->write_prompt();
        destruct(this_object());
		return;
	}
        
	ret = socket_connect(fd, full_addr, "telnet_read_callback", "telnet_write_callback");
	
	if ( ret != EESUCCESS )
	{
		message("telnet", HIW"无法连接服务器("+full_addr+")"NOR, sob);
		sob->write_prompt();
		destruct(this_object());
		return;
	}

	message("telnet", HIY"如要中断连接，请输入( "HIR"CLOSE"HIY" )\n"NOR, sob);
}

void telnet_read_callback(int fd, string mess)
{
	object sob;

	if ( !objectp(sob = query_shadow_now()) )
	{
		destruct(this_object());
		return;
	}
	// 主物件断线了，sob应该连锁断线 Add By Wenwu
	if ( !interactive(sob) )
	{
		destruct(this_object());
		return;
	}
	if ( stringp(mess) ) message("telnet", mess, sob);
}

void telnet_write_callback(int fd)
{
	object sob;

	if ( !objectp(sob = query_shadow_now()) )
	{
		destruct(this_object());
		return;
	}

	message("telnet", HIW"连接成功\n"NOR, sob);

	if ( strlen(from_user) ) send_to_remote();
}

void telnet_close_callback(int fd)
{
	object sob;

	if ( objectp(sob = query_shadow_now()) )
		message("telnet", HIY "连接已断开：请按回车键继续...\n" NOR, sob);

	destruct(this_object());
}

void remove()
{
}

void remove_interactive()
{
	destruct(this_object());
}

varargs string short(int raw)
{
	object sob;
	string str;

	if ( objectp(sob = query_shadow_now()) )
	{
		str = sob->short(raw);
		str = replace_string(str, " <输入文字中>", HIY" <远程登录中>"NOR);
		return str;
	}

	return 0;
}

// 将用户发送来的数据发送到远端服务器上去
private void send_to_remote()
{
	switch ( socket_write(fd, from_user) )
	{
		// 发送成功
		case EESUCCESS:
		case EECALLBACK:
			from_user = "";
		return;
		// 发送数据阻塞
        case EEWOULDBLOCK:
			call_out("send_to_remote", 2);
			return;
		// 发送失败
        default:
			return;
	}
}
