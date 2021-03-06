// 文件服务器 V-1.103 by Wenwu On 2007.09.10

//_____________________支持功能如下___________________
// 1、支持域名解析
// 2、支持单个、批量文件传送
// 3、支持传送任意长度(大小)的文件
// 4、客户端支持多个并行连接

// 定义这个用来作为本地调试
#undef DEBUG

// 侦听端口
#ifdef __SENSIBLE_MODIFIERS__
#define SV_PORT get_config(15)
#else
#define SV_PORT get_config(__MUD_PORT__)
#endif

// 服务密码
#define SERVER_PASS "Long12345"
// 每次读取的文件长度
#define MAX_SIZE 30000
// 较大文件发送每百分之几提示下进度
#define RATE_SHOW 3
// 文件长度大于这个才显示进度
#define MAX_SHOW_RATE 100000

#include <net/socket.h>
#include <runtime_config.h>
#include <net/server.h>

inherit F_DBASE;

nosave private int vfd = -1; // 服务端侦听 SOCKET
nosave private mapping sv_info = ([ ]); // 服务端信息
nosave private int cfd = -1; // 客户端 SOCKET
nosave private mapping cv_info = ([ ]); // 客户端信息
nosave private mapping temp_info = ([ ]); // 临时暂存信息
nosave private string *cmd_buffer = ({ }); // 命令暂存

//___________________提外部调用的函数_____________________
void connect_to(object ob, string arg);

//_____________________内部公用函数_______________________
protected void sys_msg(string msg);
protected void log_msg(string msg);
protected void setup();
protected int send_to_remote(int fd, mixed mess, int flag);
protected void send_message(int fd, int flag);
protected void send_dir(int fd, string dir);
protected int get_file(int fd, string dir, int type);
private void remove_temp(string address, int fd);
private void heart_beat();
void remove();
//_____________________服务端通讯函数_____________________
protected void in_read_callback(int fd, mixed mess);
protected void in_write_callback(int fd, mixed mess);
protected void in_close_callback(int fd);
//_____________________客户端通讯函数_____________________
protected void send_read_callback(int fd, mixed mess);
protected void send_write_callback(int fd, mixed mess);
protected void send_close_callback(int fd);

void create()
{
	seteuid(getuid());
	set("channel_id", "版本服务");
	sys_msg("版本服务已经启动。"NOR);
	set_heart_beat(1);
	setup(); // 初始化
}

protected void setup()
{
	// 创建侦听 socket
	vfd = socket_create(STREAM_BINARY, "in_read_callback", "in_close_callback" );

	if ( vfd < 0 )
	{ // 失败
		sys_msg("创建侦听 socket 失败");
		log_msg("创建侦听 socket 失败");
		return;
	}
	if ( socket_bind(vfd, SV_PORT) < 0 )
	{ // 绑定端口失败
		sys_msg("侦听 socket 绑定端口失败");
		log_msg("侦听 socket 绑定端口失败");
		socket_close(vfd);
		return;
	}
	if ( socket_listen(vfd, "in_listen_callback" ) < 0 )
	{ // 侦听失败
		sys_msg("侦听失败");
		log_msg("侦听失败");
		socket_close(vfd);
		return;
	}

	sv_info = ([ ]); // 初始化
	sys_msg("开始在端口 "+SV_PORT+" 上侦听");
}

protected void in_listen_callback(int fd)
{
	int new_fd;

	if ( (new_fd = socket_accept(fd, "in_read_callback", "in_write_callback")) < 0 ) 
	{ // 接受连接失败
		sys_msg("接受连接失败");
		log_msg("接受连接失败");
		in_close_callback(new_fd);
		return;
	}

	sv_info[new_fd] = ([ ]); // 初始化
	sv_info[new_fd][STATE] = WAIT; // 处于等待接收文件状态
}

protected void in_read_callback(int fd, mixed mess)
{
	string show, pass, file_name, msg;
	string send, get_dir, *fname_list;
	int i, file_size, type;
	
	// 检查初始化参数
	if ( !mapp(sv_info) ) sv_info = ([ ]);
	if ( !mapp(sv_info[fd]) ) sv_info[fd] = ([ ]);
	if ( !arrayp(sv_info[fd][WAIT_FILE]) ) sv_info[fd][WAIT_FILE] = ({ });
	
	if ( stringp(mess) ) msg = mess;
	else if ( bufferp(mess) ) msg = read_buffer(mess, 0, (sizeof(mess)));
	else 
	{ // 不符合的数据类型
		sys_msg("接收的数据类型错误");
		log_msg("接收的数据类型错误");
		return;
	}

	if ( sscanf(msg, VALID_CHECK, show, pass, file_name, file_size, type) == 5 )
	{ // 验证
		if ( pass != SERVER_PASS )
		{ // 验证密码
			sys_msg("服务密码验证失败");
			log_msg("服务密码验证失败");
			return;
		}
		if ( type == FINISH )
		{ // 收到发送全部完成的信息
			sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" "+show);
			// 关闭套接字
			in_close_callback(fd);
			return;
		}
		if ( type == CMD )
		{ // 收到指令
			send = sprintf(REPLY_MESSAGE, FILE, file_name);
			sv_info[fd][WAIT_FILE] += ({ send });
			send_message(fd, SFLAG);
			return;
		}
		//____________________________创建目录_______________________
#ifdef DEBUG
		file_name = "/temp"+file_name;
#endif
		if ( file_name[0..0] != "/" ) file_name = "/" + file_name;
		
		get_dir = "/";
		fname_list = explode(file_name, "/");
		for ( i=0; i<sizeof(fname_list)-1; i++ )
		{
			get_dir += fname_list[i];
			mkdir(get_dir);
			get_dir += "/";
		}
		//____________________________创建完成________________________
		//______________________是MUD里编译好的文件___________________
		/* 如果是直接运行 BINARY 的分站，那么在写入 .b 文件前必须先载入
		   原来的文件，不然如果文件没有完全写完时正好读入这个文件可能会
		   导致内存块出错而当机 */
		/*name_size = sizeof(file_name);
		if ( file_name[(name_size-2)..(name_size-1)] == ".b" )
		{
			if ( err = catch(call_other(replace_string(file_name[0..<3], "/binaries/", "/"), "???")) )
				sys_msg(HIR"发生错误："NOR+err);
		}*/
		//_____________________________ END __________________________
		if ( !write_file(file_name, "", 1) )
		{ // 删除原来的文件
			sys_msg("删除旧的文件("+file_name+")失败");
			log_msg("删除旧的文件("+file_name+")失败");
			return;
		}
		// 应答信息列表
		// 是空文件
		if ( file_size == 0 )
		{ // 通知发送下一个文件
			sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" "+show);
			sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" 接收文件 "HIG+file_name+HIW" ("HIY+file_size+"字节"HIW")");
			send = sprintf(REPLY_MESSAGE, FINISH, file_name);
			if ( member_array(send, sv_info[fd][WAIT_FILE]) == -1 ) 
				sv_info[fd][WAIT_FILE] += ({ send });
			send_message(fd, SFLAG);
			sv_info[fd][STATE] = FINISH;
			sv_info[fd][VALID] = 0;
			sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" 接收完成 "HIG+file_name+HIW" ("HIY+file_size+"字节"HIW")");
			return;
		}
		if ( sv_info[fd][STATE] == DOING && file_name != sv_info[fd][FILE_NAME] )
		{ // 上一个文件还没有发送完，无法接收新的文件，告知对方稍候发送
			send = sprintf(REPLY_MESSAGE, RESET_SEND, file_name);
			if ( member_array(send, sv_info[fd][WAIT_FILE]) == -1 ) 
				sv_info[fd][WAIT_FILE] += ({ send });
			send_message(fd, SFLAG);
			return;
		}
		sv_info[fd][FILE_NAME] = file_name;
		sv_info[fd][FILE_SIZE] = file_size;
		sv_info[fd][TYPE] = type;
		sv_info[fd][BUFFER] = "";
		sv_info[fd][VALID] = 1;
		sv_info[fd][FILE_POS] = 0;
		sv_info[fd][STATE] = DOING;
		sv_info[fd][RATE] = 0;
		sv_info[fd][SHOW] = BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" "+show;

		// 验证通过，发送一条消息通知发送文件
		send = sprintf(REPLY_MESSAGE, VALID_SEND, file_name);
		if ( member_array(send, sv_info[fd][WAIT_FILE]) == -1 ) 
			sv_info[fd][WAIT_FILE] += ({ send });
		send_message(fd, SFLAG);
		if ( sv_info[fd][FILE_SIZE] > MAX_SHOW_RATE )
			sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" 接收文件 "HIG+sv_info[fd][FILE_NAME]+HIW" ("HIY+sv_info[fd][FILE_SIZE]+"字节"HIW")");
		return;
	}

	if ( sv_info[fd][VALID] )
	{
		sv_info[fd][FILE_POS] += sizeof(mess);
		sv_info[fd][RATE] += sizeof(mess);
		sv_info[fd][BUFFER] = msg;
		
		if ( sv_info[fd][FILE_NAME] )
		{
			// 写入文件
			if ( sv_info[fd][TYPE] == ASCII )
			{ // ASCII 文件
				sv_info[fd][BUFFER] = replace_string(sv_info[fd][BUFFER], "\r", "");
				if ( write_file(sv_info[fd][FILE_NAME], sv_info[fd][BUFFER]) )
				{
					if ( sv_info[fd][FILE_SIZE] > MAX_SHOW_RATE )
					{ // 比较大的文件显示进度
						if ( sv_info[fd][RATE]/(sv_info[fd][FILE_SIZE]/100) >= RATE_SHOW )
						{
							sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" 接收进度 "HIY+sv_info[fd][FILE_POS]+" 字节 "HIW"("HIG+(sv_info[fd][FILE_POS]*10/(sv_info[fd][FILE_SIZE]/10))+"%"HIW")");
							sv_info[fd][RATE] = 0;
						}
					}
				}
				else
				{
					log_msg("写入 ASCII 文件("+sv_info[fd][FILE_NAME]+")失败");
					sv_info[fd][VALID] = 0;
					return;
				}
			}
			else if ( sv_info[fd][TYPE] == BINARY ) 
			{ // BINARY 文件
				if ( write_buffer(sv_info[fd][FILE_NAME], file_size(sv_info[fd][FILE_NAME]), mess) )
				{
					if ( sv_info[fd][FILE_SIZE] > MAX_SHOW_RATE )
					{ // 比较大的文件显示进度
						if ( sv_info[fd][RATE]/(sv_info[fd][FILE_SIZE]/100) >= RATE_SHOW )
						{
							sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" 接收进度 "HIY+sv_info[fd][FILE_POS]+" 字节 "HIW"("HIG+(sv_info[fd][FILE_POS]*10/(sv_info[fd][FILE_SIZE]/10))+"%"HIW")");
							sv_info[fd][RATE] = 0;
						}
					}
				}
				else
				{
					log_msg("写入 BINARY 文件("+sv_info[fd][FILE_NAME]+")失败");
					sv_info[fd][VALID] = 0;
					return;
				}
			}
			//_____________________重置参数表____________________
			if ( sv_info[fd][FILE_POS] == sv_info[fd][FILE_SIZE] )
			{ // 发送完成
				if ( sv_info[fd][FILE_SIZE] > MAX_SHOW_RATE )
					sys_msg(BBLU+HIR"[ "HIG+fd+HIR" ]"NOR+HIW" 接收进度 "HIY+sv_info[fd][FILE_POS]+" 字节 "HIW"("HIG+(sv_info[fd][FILE_POS]*10/(sv_info[fd][FILE_SIZE]/10))+"%"HIW")");
				sv_info[fd][FILE_NAME] = 0;
				sv_info[fd][FILE_SIZE] = 0;
				sv_info[fd][TYPE] = 0;
				sv_info[fd][BUFFER] = "";
				sv_info[fd][FILE_POS] = 0;
				sv_info[fd][VALID] = 0;
				sv_info[fd][STATE] = FINISH;
				sv_info[fd][RATE] = 0;
				// 这个文件接收完毕，发条信息通知发送下一个文件
				send = sprintf(REPLY_MESSAGE, FINISH, file_name);
				if ( member_array(send, sv_info[fd][WAIT_FILE]) == -1 ) 
					sv_info[fd][WAIT_FILE] += ({ send });
				send_message(fd, SFLAG);
				sys_msg(sv_info[fd][SHOW]); // 显示进度
			}
			else if ( sv_info[fd][FILE_POS] > sv_info[fd][FILE_SIZE] )
			{ // 文件长度不对，要求重新发送
				send = sprintf(REPLY_MESSAGE, RESET_SEND, sv_info[fd][FILE_NAME]);
				if ( member_array(send, sv_info[fd][WAIT_FILE]) == -1 ) 
					sv_info[fd][WAIT_FILE] += ({ send });
				send_message(fd, SFLAG);
				// 重置参数
				sv_info[fd][FILE_NAME] = 0;
				sv_info[fd][FILE_SIZE] = 0;
				sv_info[fd][TYPE] = 0;
				sv_info[fd][BUFFER] = "";
				sv_info[fd][FILE_POS] = 0;
				sv_info[fd][VALID] = 0;
				sv_info[fd][STATE] = FINISH;
				sv_info[fd][RATE] = 0;
			}
			//______________________重置完成_____________________
		}
		return;
	}

	sys_msg("非法数据");
	// 提示信息
	send = HIW"\n"HBRED"正在同步数据中. . .\n"HIY"请稍候再行连线 或 使用其他端口重新登录，谢谢合作！"NOR"\n";
	sv_info[fd][WAIT_FILE] += ({ send });
	send_message(fd, SFLAG);
}

protected void in_write_callback(int fd, mixed mess)
{
	sys_msg("服务器应答");
}

protected void in_close_callback(int fd)
{
	if ( fd > -1 ) 
	{
		socket_close(fd);
		sys_msg("服务端套接字( "+fd+" )断开连接");
	}

	map_delete(sv_info, fd);
}

// 调试信息
protected void sys_msg(string msg)
{
	message("wiz", HIR"版本服务："HIW+msg+"\n"NOR, users());
}

// 记录
protected void log_msg(string msg)
{
	log_file("/net/server", sprintf("%s：%s\n", CHINESE_D->chinese_time(7, time()), msg));
}

void connect_to(object ob, string arg)
{
	string ip, file_name, pass;
	int port, name_size;

	if ( sscanf(arg, "%s %d,%s,%s", ip, port, file_name, pass) == 4 )
	{ // 检查命令格式
		if ( !mapp(temp_info) ) temp_info = ([ ]);
		if ( sizeof(temp_info) )
		{ // 尚有未完成信息
			if ( !arrayp(cmd_buffer) ) cmd_buffer = ({ });
			if ( member_array(arg, cmd_buffer) == -1 ) cmd_buffer += ({ arg });
			if ( objectp(ob) ) tell_object(ob, "系统繁忙，命令暂存入缓冲区等待发送。\n");
			return;
		}

		name_size = strlen(file_name) - 1;

		if ( file_name[name_size..name_size] == "/" )
		{ // 是目录
			if ( file_size(file_name[0..(name_size-1)]) != -2 )
			{ // 没有这个目录
				if ( objectp(ob) ) tell_object(ob, "目录("+file_name+")不存在。\n");
				return;
			}
		}
		else if ( file_size(file_name) < 0 )
		{ // 发送的文件不存在
			if ( objectp(ob) ) tell_object(ob, "文件("+file_name+")不存在。\n");
			return;
		}

		//______________________________初始化参数___________________________
		temp_info[IP] = ip;
		temp_info[PORT] = port;
		temp_info[FILE_NAME] = file_name;
		temp_info[PASS] = pass;
		temp_info[BUFFER] = sprintf(VALID_CHECK, pass, file_name, 0, CMD);
	}
	else
	{
		if ( objectp(ob) ) tell_object(ob, "命令格式错误\n");
		return;
	}
	
	sys_msg("正在连接服务器("+temp_info[IP]+" "+temp_info[PORT]+")，请稍候...");
	resolve(temp_info[IP], "resolve_callback");
}

protected void resolve_callback(string address, string resolved, int key)
{
	string full_addr;
	int ret;
	
	if ( !resolved )
	{ // 域名解析失败
		if ( sscanf(temp_info[IP], "%*d.%*d.%*d.%*d") == 4 )
			resolved = temp_info[IP];
		else
		{
			sys_msg("域名("+temp_info[IP]+")解析失败");
			temp_info = ([ ]); // 清空参数
			return;
		}
	} 
	else if ( resolved != temp_info[IP] )
		sys_msg("解析域名 "+temp_info[IP]+" = "+resolved);
	
	full_addr = sprintf("%s %d", resolved, temp_info[PORT]);
	cfd = socket_create(STREAM_BINARY, "send_read_callback", "send_close_callback" );
		
	if ( cfd < 0 )
	{
		sys_msg("创建客户端 socket 失败");
		log_msg("创建客户端 socket 失败");
		temp_info = ([ ]); // 清空参数
		return;
	}
		
	ret = socket_connect(cfd, full_addr, "send_read_callback", "send_write_callback");
		
	if ( ret != EESUCCESS )
	{
		sys_msg("无法连接服务器("+full_addr+")");
		log_msg("无法连接服务器("+full_addr+")");
		temp_info = ([ ]); // 清空参数
		send_close_callback(cfd); // 回收资源
		return;
	}

	//______________________________初始化参数___________________________
	if ( !mapp(cv_info) ) cv_info = ([ ]);
	cv_info[cfd] = ([ ]);
	cv_info[cfd][WAIT_POT] = ({ });
	cv_info[cfd][WAIT_FILE] = ({ });
	cv_info[cfd][DOMAIN] = temp_info[IP];
	cv_info[cfd][IP] = resolved;
	cv_info[cfd][PORT] = temp_info[PORT];
	cv_info[cfd][FILE_NAME] = temp_info[FILE_NAME];
	cv_info[cfd][FILE_SIZE] = 0;
	cv_info[cfd][PASS] = temp_info[PASS];
	cv_info[cfd][TYPE] = BINARY;
	cv_info[cfd][MAX_FILE] = 0;
	cv_info[cfd][FINISH_FILE] = 0;
	cv_info[cfd][VALID] = 0;
	cv_info[cfd][RATE] = 0;
	cv_info[cfd][FILE_POS] = 0;
	cv_info[cfd][BUFFER] = "";
	cv_info[cfd][VALID] = 0;
	cv_info[cfd][FINISH] = 0;

	call_out("remove_temp", 30, full_addr, cfd);
}

protected void send_read_callback(int fd, mixed mess)
{
	string msg, filename, show;
	int i, max, type, filesize, rate, name_size;
	mixed send;
	
	if ( stringp(mess) ) msg = mess;
	else if ( bufferp(mess) ) msg = read_buffer(mess, 0, (sizeof(mess)));
	else return;

#ifdef DEBUG
	msg = replace_string(msg, "/temp/", "/");
#endif

	if ( sscanf(msg, REPLY_MESSAGE, type, filename) == 2 )
	{
		switch ( type )
		{
			// 开始发送文件
			case VALID_SEND :
				if ( (filesize=file_size(filename)) < 0 ) 
				{ // 文件不存在
					sys_msg("文件("+filename+")不存在");
					return;
				}
				if ( !arrayp(cv_info[fd][WAIT_POT]) ) cv_info[fd][WAIT_POT] = ({ });
				if ( filesize < MAX_SIZE )
				{
					send = read_buffer(filename);
					cv_info[fd][WAIT_POT] += ({ send });
				}
				else
				{
					rate = 0;
					do
					{
						send = read_buffer(filename, rate, MAX_SIZE);
						cv_info[fd][WAIT_POT] += ({ send });
						rate += MAX_SIZE;
					}
					while ( rate < filesize );
				}
				
				if ( filesize > MAX_SHOW_RATE )
					sys_msg(BRED+HIB"[ "HIW+fd+HIB" ]"NOR+HIW" 发送文件 "HIC+filename+HIW" ("HIY+filesize+"字节"HIW")");

				send_message(fd, CFLAG);
				return;
			// 未成功接收到的文件放入队列等待下次发送
			case RESET_SEND :
				if ( (filesize=file_size(filename)) < 0 ) 
				{ // 文件不存在
					sys_msg("文件("+filename+")不存在");
					return;
				}
				if ( !arrayp(cv_info[fd][WAIT_FILE]) ) cv_info[fd][WAIT_FILE] = ({ });
				if ( member_array(filename, cv_info[fd][WAIT_FILE]) == -1 ) 
					cv_info[fd][WAIT_FILE] += ({ filename });
				// 检查如果已停止了发送，则继续发送未成功完成的
				cv_info[fd][WAIT_POT] -= ({ 0 });
				if ( !(sizeof(cv_info[fd][WAIT_POT])) && cv_info[fd][FINISH] ) 
					send_read_callback(fd, sprintf(REPLY_MESSAGE, FINISH, "reset"));
				return;
			// 上个文件已成功发送，继续发送下个文件
			case FINISH :
				if ( filename != "reset" ) cv_info[fd][FINISH_FILE]++;
				if ( cv_info[fd][FINISH_FILE] <= cv_info[fd][MAX_FILE] )
				{
					show = "完成度("HIY+(cv_info[fd][FINISH_FILE]*100/cv_info[fd][MAX_FILE])+"%"+HIW")："HIG + 
						cv_info[fd][FINISH_FILE]+HIY" / "HIC+cv_info[fd][MAX_FILE];
					sys_msg(BRED+HIB"[ "HIW+fd+HIB" ]"NOR+HIW" "+show);
					if ( cv_info[fd][FINISH_FILE] == cv_info[fd][MAX_FILE] )
					{ // 全部发送完成，发送一条信息通知
						send = sprintf(VALID_CHECK, show, cv_info[fd][PASS], "out", 0, FINISH);
						cv_info[fd][WAIT_POT] += ({ send });
						send_message(fd, CFLAG);
						cv_info[fd][FINISH] = 1; // 标志全部完成

						if ( !mapp(cv_info[fd]) ) cv_info[fd] = ([ ]);
						if ( !arrayp(cv_info[fd][WAIT_FILE]) ) cv_info[fd][WAIT_FILE] = ({ });

						cv_info[fd][WAIT_FILE] -= ({ 0 });

						if ( sizeof(cv_info[fd][WAIT_FILE]) && filename != "reset" ) 
						{
							sys_msg(HIR"发生错误，缓冲区还有文件未成功发送");
							log_msg("发生错误，缓冲区还有文件未成功发送");
						}
						return;
					}
				}

				if ( !mapp(cv_info[fd]) ) 
				{
					send_close_callback(fd);
					return;
				}
				if ( !arrayp(cv_info[fd][WAIT_FILE]) )
				{
					send_close_callback(fd);
					return;
				}

				cv_info[fd][WAIT_FILE] -= ({ 0 });

				if ( !(max=sizeof(cv_info[fd][WAIT_FILE])) )
				{
					send_close_callback(fd);
					return;
				}
				
				for ( i=0; i<max; i++ )
				{
					send = cv_info[fd][WAIT_FILE][i];

					if ( !stringp(send) && !bufferp(send) )
					{ // 无效的文件名
						cv_info[fd][WAIT_FILE][i] = 0;
						continue;
					}
					if ( (filesize=file_size(send)) < 0 )
					{ // 没有这个文件
						cv_info[fd][WAIT_FILE][i] = 0;
						continue;
					}
					//____________________更新状态信息__________________
					cv_info[fd][FILE_NAME] = send;
					cv_info[fd][FILE_SIZE] = filesize;
					cv_info[fd][TYPE] = BINARY;
					show = "完成度("HIY+(cv_info[fd][FINISH_FILE]*100/cv_info[fd][MAX_FILE])+"%"+HIW")："HIG + 
						cv_info[fd][FINISH_FILE]+HIY" / "HIC+cv_info[fd][MAX_FILE];
					cv_info[fd][BUFFER] = sprintf(VALID_CHECK, show, cv_info[fd][PASS], send, filesize, cv_info[fd][TYPE]);
					//_____________________发送信息_____________________
					cv_info[fd][WAIT_POT] += ({ cv_info[fd][BUFFER] });
					cv_info[fd][WAIT_FILE][i] = 0;
					break;
				}
				send_message(fd, CFLAG);
				return;
			// 收到发文件的请求
			case FILE :
				name_size = strlen(filename)-1;

				if ( filename[name_size..name_size] == "/" )
				{ // 是目录
					send_dir(fd, filename);
					return;
				}
				if ( file_size(filename) < 0 )
				{ // 发送的文件不存在
					sys_msg("要发送的文件("+filename+")不存在");
					send_close_callback(fd);
					return;
				}

				cv_info[fd][MAX_FILE] = 1;
				cv_info[fd][FINISH_FILE] = 0;
				cv_info[fd][WAIT_FILE] += ({ filename });

				// 开始发送文件
				send_read_callback(fd, sprintf(REPLY_MESSAGE, FINISH, "reset"));
				return;
			// 其他
			default:
				return;
		}
	} 
	else if ( sscanf(msg, SHOW_MESSAGE, type, filename) == 2 )
	{
		switch ( type )
		{
			// 状态显示信息
			case SHOW_SEND :
				sys_msg(filename);
				return;
			// 其他
			default:
				return;
		}
	}

	sys_msg(msg);
}

protected void send_write_callback(int fd, mixed mess)
{
	sys_msg("连接成功");
	cv_info[fd][VALID] = 1;
	send_to_remote(fd, temp_info[BUFFER], TFLAG);
	temp_info = ([ ]); // 清空参数
	remove_call_out("remove_temp");
}

protected void send_close_callback(int fd)
{
	if ( fd > -1 ) 
	{
		socket_close(fd);
		sys_msg("客户端套接字( "+fd+" )断开连接");
	}

	map_delete(cv_info, fd);
}

protected int send_to_remote(int fd, mixed mess, int flag)
{	
	switch ( socket_write(fd, mess) )
	{
		// 发送成功了
		case EESUCCESS:
		case EECALLBACK:
			return 1;
		// 发送数据阻塞
		case EEWOULDBLOCK:
			if ( flag == TFLAG )
				call_out("send_to_remote", 0, fd, mess, flag);
			return 0;
		default:
			// 发送过程中出现错误
			return -1;
	}
}

protected void send_message(int fd, int flag)
{
	mixed send;
	int i, max, type;

	switch ( flag )
	{
		// 客户端处理
		case CFLAG :
			if ( !mapp(cv_info) ) return;
			if ( !mapp(cv_info[fd]) ) return;
			if ( !arrayp(cv_info[fd][WAIT_POT]) ) return;

			cv_info[fd][WAIT_POT] -= ({ 0 });

			if ( !(max=sizeof(cv_info[fd][WAIT_POT])) ) return;
			
			for ( i=0; i<max; i++ )
			{
				send = cv_info[fd][WAIT_POT][i];

				if ( !stringp(send) && !bufferp(send) )
				{ // 未知数据类型
					cv_info[fd][WAIT_POT][i] = 0;
					continue;
				}
				if ( !(type=send_to_remote(fd, send, flag)) )
				{ // 信息阻塞，重新发送
					call_out("send_message", 0, fd, flag);
					return;
				}
				if ( type == -1 ) 
				{
					sys_msg(HIY"发送过程中出现错误");
					send_close_callback(fd);
					return;
				}
				if ( bufferp(cv_info[fd][WAIT_POT][i]) 
					&& cv_info[fd][FILE_SIZE] > MAX_SHOW_RATE )
				{ // 较大文件显示发送进度
					cv_info[fd][FILE_POS] += sizeof(cv_info[fd][WAIT_POT][i]);
					cv_info[fd][RATE] += sizeof(cv_info[fd][WAIT_POT][i]);
					if ( cv_info[fd][RATE]/(cv_info[fd][FILE_SIZE]/100) > RATE_SHOW 
						|| cv_info[fd][FILE_POS] == cv_info[fd][FILE_SIZE] )
					{
						cv_info[fd][RATE] = 0;
						sys_msg(BRED+HIB"[ "HIW+fd+HIB" ]"NOR+HIW" 发送进度 "HIG+cv_info[fd][FILE_POS]+" 字节 "HIW"("HIM+(cv_info[fd][FILE_POS]*10/(cv_info[fd][FILE_SIZE]/10))+"%"HIW")");
					}
				}
				else
				{ // 不是文件内容，重置发送进度参数
					cv_info[fd][RATE] = 0;
					cv_info[fd][FILE_POS] = 0;
				}

				cv_info[fd][WAIT_POT][i] = 0;
				break;
			}

			send_message(fd, flag);
			return;
		// 服务端处理
		case SFLAG :			
			if ( !mapp(sv_info) ) return;
			if ( !mapp(sv_info[fd]) ) return;
			if ( !arrayp(sv_info[fd][WAIT_FILE]) ) return;

			sv_info[fd][WAIT_FILE] -= ({ 0 });

			if ( !(max=sizeof(sv_info[fd][WAIT_FILE])) ) return;
			
			for ( i=0; i<max; i++ )
			{
				send = sv_info[fd][WAIT_FILE][i];

				if ( !stringp(send) && !bufferp(send) )
				{ // 未知数据类型
					sv_info[fd][WAIT_FILE][i] = 0;
					continue;
				}
				if ( !(type=send_to_remote(fd, send, flag)) )
				{ // 信息阻塞，重新发送
					call_out("send_message", 0, fd, flag);
					return;
				}
				if ( type == -1 ) 
				{
					sys_msg(HIY"发送过程中出现错误");
					in_close_callback(fd);
					return;
				}

				sv_info[fd][WAIT_FILE][i] = 0;
				break;
			}

			send_message(fd, flag);
			return;
		// 其他
		default:
	}
}

protected void send_dir(int fd, string dir)
{
	int max;

	if ( !get_file(fd, dir, 1) ) 
	{ // 没有文件
		send_close_callback(fd);
		return;
	}

	cv_info[fd][WAIT_FILE] -= ({ 0 });

	if ( !(max = sizeof(cv_info[fd][WAIT_FILE])) )
	{
		sys_msg("目录("HIY+dir+HIW")下没有任何文件");
		send_close_callback(fd);
		return;
	}

	cv_info[fd][MAX_FILE] = max;
	cv_info[fd][FINISH_FILE] = 0;
	
	// 开始发送文件
	send_read_callback(fd, sprintf(REPLY_MESSAGE, FINISH, "reset"));
}

protected int get_file(int fd, string dir, int type)
{
	mixed *file;
	int i, j;
	
	// 取得目录内文件
	file = get_dir(dir, -1);
	
	if ( type )
	{
		if ( !sizeof(file) )
		{ // 没有文件
			if ( file_size(dir) == -2 ) sys_msg("目录("HIY+dir+HIW")是空的");
			else sys_msg("没有这个目录("HIY+dir+HIW")");
			return 0;
		}
	}

	i = sizeof(file);
	while ( i-- ) 
	{ // 是子目录
		if ( file[i][1] == -2 ) file[i][0] += "/";
	}
	
	sys_msg(HIG"读入目录：" + dir);

	if ( sizeof(file) )
	{
		for ( i=0, j = sizeof(file); i<j; i++ )
		{
			if ( file[i][1] > -1 ) 
			{
				cv_info[fd][WAIT_FILE] += ({ (dir+file[i][0]) });
				sys_msg(NOR"读入文件：" + dir+file[i][0]);
			}
			else if ( file[i][1] == -2 ) 
				call_other(__FILE__, "get_file", fd, dir+file[i][0], 0);
		}
	}
	else
		sys_msg(HIY"没有任何档案");

	return 1;
}

// 析构函数
void remove()
{
	int i, *fd;
	
	if ( mapp(sv_info) )
	{ // 处理服务端连接信息
		fd = keys(sv_info);
		for ( i=0; i<sizeof(fd); i++ )
		{
			in_close_callback(fd[i]);
		}
	}

	if ( mapp(cv_info) )
	{ // 处理客户端连接信息
		fd = keys(cv_info);
		for ( i=0; i<sizeof(fd); i++ )
		{
			send_close_callback(fd[i]);
		}
	}

	in_close_callback(vfd);
}

private void remove_temp(string address, int fd)
{
	if ( !mapp(cv_info) 
		|| !mapp(cv_info[fd]) 
		|| cv_info[fd][VALID] ) 
		return;

	sys_msg("无法连接到服务器("+address+")");
	temp_info = ([ ]); // 清空参数
	send_close_callback(fd);
}

private void heart_beat()
{ // 执行等待中的命令
	string cmd;
	int i, max;

	if ( !arrayp(cmd_buffer) ) cmd_buffer = ({ });

	cmd_buffer -= ({ 0 });

	if ( !(max = sizeof(cmd_buffer)) ) return;

	for ( i=0; i<max; i++ )
	{
		if ( !stringp(cmd=cmd_buffer[i]) )
		{ // 不是字串
			cmd_buffer[i] = 0;
			continue;
		}
		
		cmd_buffer[i] = 0;
		connect_to(0, cmd);
		return;
	}
}

mapping get_info1()
{
	return sv_info;
}

mapping get_info2()
{
	return cv_info;
}

mapping get_info3()
{
	return temp_info;
}