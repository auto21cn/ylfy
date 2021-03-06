// 完善优化 By 龙云梦(Wenwu) On 2004年12月21日
// 检查登陆系统的载入情况防止登陆出错损坏数据。
// 心跳检查残留的 LOGIN_OB ，并清除其中被废弃的。

#include <login.h>
#include <dbase.h>

#define OUT_MUD_GAME_TIME 900

inherit F_DBASE;
inherit F_SAVE;

nosave int is_check_times = 0;

void create()
{
	set_temp("pob", previous_object(-1));
	set_heart_beat(1);
}

void logon()
{
	if ( !find_object(LOGIN_D) )
	{
		write("游戏尚未启动完毕，请等五秒再来。\n");
		destruct(this_object());
		return;
	}

	/*if ( !find_object(BIGUAN_D) )
	{
		load_object(BIGUAN_D);
		write("游戏正在整理离线闭关数据，请等五秒再来。\n");
		destruct(this_object());
		return;
	}*/
	
	//remove_call_out("time_check");
	//call_out( "time_check", OUT_MUD_GAME_TIME );
	LOGIN_D->logon( this_object() );
}

object find_body(string name)
{
	object ob;
	
	if (!name)
		return 0;
	
	if( objectp(ob = find_player(name)) )
		return ob;

	return 0;
}

void time_out()
{
	//object user;
	object me = this_object();
	object ob = query_temp("body_ob");
	
	if ( objectp(ob) )
	{
		if ( !environment(ob) ) 
		{
			if ( interactive(ob) ) write("您花在连线进入手续的时间太久了，下次想好再来吧。\n");
			destruct(ob);
		}
		else 
		{
			set_heart_beat(0); // 设为0，不需要再检查了
			return;
		}
	}
	
	/*user=find_body(this_object()->query("id"));
	
	if (user && !environment(user))
		destruct(user);*/
	
	if ( me && interactive(me) ) write("您花在连线进入手续的时间太久了，下次想好再来吧。\n");

	destruct(me);
}

void time_check()
{
	string id = query("id");
	
	if ( !id || file_size("/data/login/"+id[0..0]+"/"+id+".o") > 0 )
	{
		time_out();
		return;
	}
	
	//remove_call_out("time_out");
	//call_out( "time_out", LOGIN_TIMEOUT );
}

// Don't destruct(this_object()) in the net_dead() interactive apply or
// there'll be error message: Double call to remove_interactive()
void net_dead()
{
	time_out();
}

// This is used by F_SAVE to determinethe file name to save our data.
string query_save_file()
{
	string id;

	id = query("id", 1);

	if( !stringp(id) )
		return 0;
	
	return sprintf(DATA_DIR "login/%c/%s", id[0], id);
}

void receive_message(string type, string str)
{
	if( type!= "write" )
		return;
	
	if (query_temp("big5"))
		str = (string)LANGUAGE_D->toBig5(str);
	
	receive(str);
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
}

void window_size(int x, int y)
{
	set_temp("window_size/x", x);
	set_temp("window_size/y", y);
}

void telnet_suboption(string opt)
{
	set_temp("telnet_suboption", opt);
}

// Protect login object's data against hackers.
nomask mixed set(string prop, mixed data)
{
	if( geteuid(previous_object()) != ROOT_UID && base_name(previous_object()) != USER_OB )
		return 0;
	
	return ::set(prop, data);
}

string process_input(string str)
{
	if (this_object()->query_temp("big5") )
		str=LANGUAGE_D->Big52GB(str);

	return str;
}

private void heart_beat()
{
	is_check_times++;

	if ( is_check_times == OUT_MUD_GAME_TIME/2 ) time_check();
	if ( is_check_times == LOGIN_TIMEOUT/2 ) time_out();
}