// quit.c

#include <ansi.h>
#include <command.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void do_quit(object, object);

void create() 
{
	seteuid(getuid());
	set("channel_id", "离线指令");
}

int main(object me, string arg)
{
	object link_ob;
	int flag = 0;
	
	if (query_heart_beat(me))
		return notify_fail("这个指令只能由系统执行。\n");
	
	if (me->query_temp("quit"))
		return notify_fail("正在退出过程中，请稍候。\n");

	/*if ( !wizardp(me) && me->query_condition("killer") ) 
		return notify_fail(HIR"你目前正被官府通缉，想潜逃么？\n"NOR);*/

	link_ob = me->query_temp("link_ob");

	// We might be called on a link_dead player, so check this.
	if( link_ob )
	{
		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me));
		link_ob->save();
		
		// Are we possessing in others body ?
		if( link_ob->is_character() )
		{
			write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
			exec(link_ob, me);
			link_ob->setup();
			return 1;
		}
	}

	if( LOGIN_D->get_madlock() == 1) 
		return notify_fail("时空已经封闭，没有人能够退出这个时空了。\n");
	
	if (me->query_temp("sleeped"))
		me->set("marks/insleeping",1);

	if (!(interactive(me) && query_idle(me) < 10))
		flag = 1;
	
	me->set_temp("quit", 1);
	me->set_temp("no_kill", 1);
	me->set_temp("disable_inputs",1);
	
	CHANNEL_D->do_channel(this_object(), "sys", HIW + me->query("name")+"("+me->query("id")+")" + HIY " 准备离开游戏了。");
	
	if (!flag && !wizardp(me))
	{
		write("正在退出游戏 ,档案保存中......\n");
		call_out("do_quit", 3, me, link_ob);

	}
	else
		do_quit(me, link_ob);

	return 1;
}

void do_quit(object me, object link_ob)
{
	int i;

	if (!me)
		return;
	
	if( !wizardp(me) )
	{
		foreach (object ob in all_inventory(me))
		{
			if ( ob && !ob->query_autoload() && !ob->query("xyzx_save_item") )
				DROP_CMD->do_drop(me, ob,1);
		}
		me->set("quit_time",time());
	}

	//if ( in_input(me) ) /*remove_input_to(me)*/;
	
	write("欢迎下次再来！\n");
	//message("system", HIR+me->query("name")+"("+me->query("id")+")" + "由于无心跳，离开游戏。\n", environment(me), me);

	CHANNEL_D->do_channel(this_object(), "sys", NOR + me->short(1) + HIR " 离开游戏了。");

	if (link_ob)
	{
		link_ob->set("last_on", time());
		if ( query_ip_name(me) )
			link_ob->set("last_from", query_ip_name(me));
		else
			link_ob->set("last_from", me->query_temp("last_ip_name"));
		destruct(link_ob);
	}

	if (me->query("mud_age") == me->query_temp("mud_age"))
		me->add("mud_age", 1);
	
	if (!wizardp(me) && (i = (me->query("combat_exp") - me->query_temp("temp_exp")) * 60 / (me->query("mud_age") - me->query_temp("mud_age"))) > 100)
		log_file("static/EXP",sprintf("%s 上次经验：%d，本次经验：%d，平均：%d/min\n",geteuid(me), me->query_temp("temp_exp"),me->query("combat_exp"), i));
	
	CHANNEL_D->do_channel(this_object(), "sys",me->name() + "(" + me->query("id") + ")离开游戏了。本次连线经验增长"+i+"。\n");

	me->set_temp("quit", 0);
	me->delete_temp("no_kill");
    me->delete_temp("disable_inputs");
	me->delete("exp_jiacheng");
	me->save();
	destruct(me);
}

int help(object me)
{
	write(@HELP
指令格式 : quit

当你想暂时离开时, 可利用此一指令。
HELP
    );
    return 1;
}
