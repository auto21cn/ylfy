// message.c

#include <dbase.h>
#include <liebiao.h>

#define MAX_MSG_BUFFER 500

nosave string *msg_buffer = ({});

void write_prompt();

void receive_message(string msgclass, string msg)
{
	object me;
	string subclass, *ch, huiyuan, year, mon, day, file_str, *chufa_list, chufa_msg, chufa_cmds;
	int len, v, i, prop;

	me = this_object();

	if(!msg || (len=strlen(msg))<1)
		return;

	if(len>8000)
		msg=msg[0..8000]+"\n\n．．．\n";

	prop = -1;

	if ( interactive(me) )
		prop = 1;
	else if ( playerp(me) && me->query("lixian/biguan") )
		prop = 0;

	if ( prop == -1 )
	{
		me->relay_message(msgclass, msg);
		return;
	}
	// 使用BIG5的
	//if ( query_ip_port(me) == BIG5_PORT )
	//	msg = efun::gbtobig5(msg);

	if ( prop == 1 )
	{
		// 远程登陆
		if ( msgclass == "telnet" )
		{
			receive(msg);
			return;
		}
		// 巫师信息
		if ( msgclass == "wiz" )
		{
			if ( !wizardp(me) ) return;
			if ( me->query("env/block_wiz_msg") ) return;
			receive(msg);
			return;
		}
		// 帮会信息
		if ( msgclass == "party" )
		{
			if ( !living(me) ) return;
			if ( !me->query("xieyi/zmud") )
			{
				msg = replace_string(msg,BLINK,"");
				msg = PTEXT(msg);
			}
			receive(msg);
			return;
		}
		if ( msgclass == "notify_fail" )
		{
                 efun::notify_fail(ESC "[256D" ESC "[K" + msg);
			return;
		}
		// 行走信息
		if ( msgclass == "go" && me->query("env/block_go_msg") ) return;
		// 聊天频道
		if( sscanf(msgclass, "%s:%s", subclass, msgclass)==2 )
		{
			switch(subclass)
			{
				case "channel":
					if( !pointerp(ch = query("channels")) || member_array(msgclass, ch)==-1 )
					return;

					if ( !me->query("xieyi/zmud") )
					{
						if ( sscanf(msg,"%*s【迷雾森林】%*s") || sscanf(msg,"%*s【镜花水月】%*s")
							|| sscanf(msg,"%*s〖赌场消息〗%*s") || sscanf(msg,"%*s【系统精灵】%*s")
							|| sscanf(msg,"%*s【[1;31m江湖追杀令[1;34m】%*s") || sscanf(msg,"%*s【[1;33m江湖赦免令[1;34m】%*s") )
						{
							if ( !sscanf(msg,"%*sptext%*s") )
								msg = PTEXT(msg);
						}
						//过滤旧版本Tomud无法解释的ANSI字符串
						if ( sscanf(msg,"%*sptext%*s") )
							msg = replace_string(msg,BLINK,"");
					}

					//增加昏迷或睡眠状态可接收聊天信息
					if( !living(me) && prop == 1 )
					{
						receive( msg );
						return;
					}
					break;

				case "outdoor":
					if( !environment() || !environment()->query("outdoors") )
					return;

				case "room":
					if( !environment() || environment()->query("outdoors") )
					return;

				default:
					error("Message: Invalid Subclass " + subclass + ".\n");
			}
		}

		if( query_temp("block_msg/all") || query_temp("block_msg/" + msgclass) ) return;

		if ( prop == 1 )
		{
			/*if( in_input(me) || in_edit(me) )
			{
				if ( !wizardp(me) && query_idle(me) > 300 && !objectp(me->query_temp("query_shadowed")) )
				{
					//remove_input_to(me);
					//tell_object(me, HIY"\n您输入文字发呆的时间超过"HIC" 五 "HIY"分钟了，还是先想好了再说吧。\n"NOR);
					write_prompt();
				} else if( sizeof(msg_buffer) < MAX_MSG_BUFFER )
					msg_buffer += ({ msg });
			}*/
			if( in_input(me) || in_edit(me) ){
                if( sizeof(msg_buffer) < MAX_MSG_BUFFER )
                 msg_buffer += ({ msg });
                }
			else
				receive( msg );
		}
	}

	if ( prop ) return;

	// 触发
	// --------------------------------------------------------------------
	// 触发是关闭的
	if ( me->query("xyzx_chufa_stop") )
		return;

	// 有未完成的触发则暂停触发等待
	if ( me->query_temp("xyzx_sys_chufa") )
		return;

	// 不是会员不能使用触发
	if ( !me->query("xy_huiyuan") )
		return;

	if ( !stringp(huiyuan = me->query("xy_huiyuan")) )
		return;

	if ( sscanf(huiyuan, "%d年%d月%d日", year, mon, day) != 3 )
		return;

	// 不是玩家
	if ( !playerp(me) )
		return;

	// 检查触发档案文件
	if ( file_size(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__) < 0 )
		return;

	file_str = read_file(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__);
	chufa_list = explode(file_str, "\n");
	v = sizeof(chufa_list);

	if ( v > CHUFA_CMD_SIZE )
		v = CHUFA_CMD_SIZE;

	// 去掉 ANSI 字符串
//	msg = efun::remove_ansi(msg);

	for ( i = 0; i < v; i++ )
	{
		if ( sscanf(chufa_list[i], "%s:%s", chufa_msg, chufa_cmds) == 2 && stringp(chufa_msg) && 0 < strlen(chufa_msg) )
		if ( sscanf(chufa_list[i], "%s:%s", chufa_msg, chufa_cmds) == 2 )
		{
			if ( strlen(msg) >= strlen(chufa_msg) && sscanf(msg, "%*s"+chufa_msg+"%*s") )
			{
				me->set_temp("xyzx_sys_chufa", chufa_cmds);
				break;
			}
		}
	}

	return;
	// --------------------------------------------------------------------
}

void write_prompt()
{
	if ( sizeof(msg_buffer) )
	{
		receive(BOLD +"[输入时暂存讯息]\n" + NOR);
		for(int i=0; i<sizeof(msg_buffer); i++)
			receive(msg_buffer[i]);
		msg_buffer = ({});
	}
	write(NOR"　"NOR);
}


void receive_snoop(string msg)
{
	receive("%" + msg);
}
