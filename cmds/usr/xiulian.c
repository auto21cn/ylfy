// 离线练功 By 龙云梦(Wenwu) On 2006年1月21日

#include <ansi.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
	seteuid(getuid());
	set("channel_id", "离线修炼");
}

int main(object me, string arg)
{
	object ob;
	string name;

	if ( !interactive(me) ) return 0;
	// 非会员不予离线练功
	if ( !stringp(me->query("xy_huiyuan")) || !sscanf(me->query("xy_huiyuan"), "%*s年%*s月%*s日") )
		return notify_fail(HIY"只有会员才能离线闭关修炼。\n"NOR);
	/*if ( !me->query("xyhy_type") )
		return notify_fail(HIR"免费会员无法使用离线练功功能。\n"NOR);*/
	if ( !wizardp(me) && me->query_condition("killer") ) 
		return notify_fail(HIR"你目前正被官府下令通缉，无法安心闭关修炼。\n"NOR);

	ob = me->query_temp("link_ob");

	if ( me->query("biguan_is_online", 1) < 1800 && me->query("xyhy_type") != 2 )
		return notify_fail(HIR"你剩余的离线练功时间不足一小时，暂时无法离线闭关。\n"HIY"如想现在就离开游戏，请使用指令[quit]退出游戏。\n"NOR);

	if ( file_size(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__) == -1 
		&& file_size(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__) == -1 )
		return notify_fail(HIY"你还没有设置指令集，请使用指令"HIC" setcmds 或 setchufa "HIY"设置。\n"NOR);

	if ( me->query("block") ) return notify_fail(HIR"关监中该权限已被剥夺。\n"NOR);

	if ( ob )
	{
		// 元神出窍中
		if ( ob->is_character() )
			return notify_fail(HIY"你现在正元神出窍中，无法离线闭关修炼。\n"NOR);

		//exec(ob, me);
		ob->save();
		write(HIC"你开始闭关修炼，暂时离开游戏！！！\n"NOR);
		destruct(ob);
	}
	else
	{
		ob = new(LOGIN_OB);
		ob->set("id", me->query("id"));

		// 检查载入情况
		if ( !ob->restore() )
		{
			write( HIR"你的档案出现问题，请联系巫师处理。\n"NOR);
			destruct(ob);
        	return 0;
		}

		//exec(ob, me);
		write(HIC"你开始闭关修炼，暂时离开游戏！！！\n"NOR);
		destruct(ob);
	}

	me->set("lixian/biguan",1);
	me->delete_temp("do_xiulian_num");

	if ( !wizardp(me) )
	{
		if ( sscanf(base_name(environment(me)), "/u/%*s") 
			|| sscanf(base_name(environment(me)), "/d/automap/%*s") 
			|| sscanf(base_name(environment(me)), "/d/migong/%*s") 
			|| environment(me)->query("no_login")
			|| clonep(environment(me)) 
			|| virtualp(environment(me)) )
		{
			me->delete("startroom");
		}
		else
			me->set("startroom", base_name(environment(me)));
		me->set("quit_time",time());
	}
	else me->set("startroom", base_name(environment(me)));
	
	me->delete("exp_jiacheng");
	me->save();
	remove_interactive(me);
	BIGUAN_D->add_bg_user(me);

	// 组队清除
	if ( stringp(name = me->query_temp("xyzx_team/name")) )
			TEAMD->del_team_member(me);

	message("system", HIW + me->name(1) + "开始离线修炼。\n"NOR, environment(me));
	message("chat", HIY"【镜花水月】：" + HIW"听说 "HIC + me->query("name") + HIW" 开始离线闭关修炼,已然神游虚外试图窥视无上天道！\n"NOR, users() );

	return 1;
}

int help()
{
	write(@TEXT
指令格式：xiulian
   这个指令可以让你离线计划练功，离线后你的人物控制权转交给了系统，
系统会按照你的计划要求进行循环执行指令，这是需要消耗潜能的，每执行
一个指令会消耗一点潜能，当然如果你是注册会员的话就不用浪费这些潜能
了。至于如何编制需要的指令集可以请参考 help setcmds
TEXT
	);
	return 1;
}