inherit ROOM;

nosave object *working_obs = ({});

void init()
{
    if ( this_player() ) add_action("do_work", "work");
    //      if ( !wizardp(this_user()) )
    add_action("discmds",({"duanlian","ansuan","touxi","persuade","teach","exert","exercise","study","learn","sleep","kill","steal","cast","conjure","expell","fight","hit","perform","prcatice","scribe","surrender"}));
}

int discmds()
{
    tell_object(this_player(),"还是老老实实工作吧？！\n");
    return 1;
}

void got_gold(object me,int amount)
{
    int money;
    money = me->query("money");
    money += amount*10000;
    if(money>100000000)
    {
	money -= 100000000;
	me->add("more_money",1);
    }
    me->set("money",money);
}

int do_work(string arg)
{
    object me;
    int max;

    me = this_player();

    if ( !objectp(me) ) return 0;
    if ( !arrayp(working_obs) ) working_obs = ({});

    working_obs -= ({ 0 });
    max = sizeof(working_obs);

    if ( (int)me->query("jing")<random(30) || (int)me->query("qi")<random(30) )
    {
	tell_object(me,"你开始辛苦地工作......\n");
	write("你突然感到头晕眼花。。。。。。\n");
	tell_room(environment(me), RED+me->name() +"脸色看起来不大对头，斗大的汗珠从脸上滑了下来。\n哎,又是一个要钱不要命的..!\n"NOR, ({me}));
	me->unconcious();
	return 1;
    }
    if ( (int)me->query("jing")<60 || (int)me->query("qi")<60 ) 
	return notify_fail("你快累死了，要钱不要命了吗？\n");
    if ( me->query_temp("working") ) return notify_fail("加油呀！谁叫你穷呀！\n");
    if ( max > get_system_config(DATA_CONFIG_DIR "work.h", "max_doing_user") ) 
    {               
	write("老板嘿嘿一笑：我这里人手已经够了，做义工可没工钱的哟！\n");
	me->start_busy(5);
	return 1;
    }
    tell_object(me,"你开始辛苦地工作......\n");
    working_obs += ({ me });
    me->set_temp("working", 1);
    me->add_temp("work_times", 1);
    return 1;
}

private void heart_beat()
{
    object me;
    int max, i,pay;

    if ( !arrayp(working_obs) ) 
    {
	working_obs = ({});
	return;
    }

    working_obs -= ({ 0 });

    if ( !(max=sizeof(working_obs)) ) return;

    for ( i=0; i<max; i++ )
    {
	me = working_obs[i];

	if ( !objectp(me) ) continue;

	me->receive_damage("jing", 50); 
	me->receive_damage("qi", 50);   

	if ( (string)environment(me)->query("short")!="谷物加工厂" || me->query_temp("work_out") )
	{
	    tell_object(me, "你工作的时候开小差，结果累了半天什么都没得到!\n");
	    me->delete_temp("working");
	    me->delete_temp("work_out");
	    working_obs[i] = 0;
	    continue;
	}
	if ( random((int)me->query_temp("work_times")) > 60+random(100) )
	{
	    tell_object(me,"老板对你说：嗯，做的不错，这是给你的奖励！\n");
	    tell_object(me,HIW"你的钱庄存款增加三十两黄金。"NOR"\n"NOR);
	    got_gold(me,10);
	    me->add("potential", 30, 1);
	    me->delete_temp("work_times");
	    me->delete_temp("working");
	    working_obs[i] = 0;
	    continue;
	}

	tell_object(me,"你辛苦的工作终于结束了，可人也累的半死。\n");
	pay = 5+random(get_system_config(DATA_CONFIG_DIR "work.h", "max_give_gold"));
	got_gold(me,pay);       
	me->add("combat_exp",random(10), 1);
	me->add("potential",random(10), 1);
	tell_object(me,"老板冷冷地对你说：这是你的工钱。\n");
	tell_object(me,sprintf(HIW"你的钱庄存款增加%s两黄金。"NOR"\n"NOR,chinese_number(pay)));
	me->set_temp("die_for","在谷物加工厂累");
	me->delete_temp("working");
	working_obs[i] = 0;
    }

    working_obs -= ({ 0 });
}

int valid_leave(object me, string dir)
{
    mapping exits;
    string *dirs;
    int i,leave;
    leave=0;
    mapp(exits = this_object()->query("exits"));
    dirs=keys(exits);
    dirs -= ({ 0 });
    for(i=0;i<sizeof(dirs);i++)
    {
	if(dir == dirs[i])
	{
	    leave = 1;
	    break;
	}
    }
    if ( me->query_temp("working") && leave ) 
	me->set_temp("work_out",1);
    me->delete_temp("working");
    return ::valid_leave(me, dir);
}

void reset()
{
    set_heart_beat(10+random(get_system_config(DATA_CONFIG_DIR "work.h", "do_heart_times")));
    ::reset();
}

