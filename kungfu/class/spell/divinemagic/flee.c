// feeblebolt.c

#include <ansi.h>

inherit SSERVER;
int do_execration(object me,object target,int i);
int do_hit(object me,object target,int skill);

int cast(object me, object target)
{


	int  skill;
	string msg;
	skill=me->query_skill("divinemagic",1);
	if(!skill||skill<=50)
		return notify_fail("你没有学会如何使用？\n");
	if(me->query_temp("execration"))
		return notify_fail("你正在念咒。\n");
	if(me->query_temp("execration"))
		return notify_fail("你正在念咒。\n");
	if((int)me->query("mana") < 50 )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("sen") < 10 )
		return notify_fail("你的精神没有办法有效集中！\n");

	me->add("mana", -50);
	me->receive_damage("sen", 10);

	msg = ""+me->name()+"自言自语不知道在说些什麽。\n";
        message("vision",msg, environment(me), ({me}));
	tell_object(me,"你开始施展移动法愿......\n");
	me->set_temp("execration",1);
	call_out("do_execration",1,me,target,1);
	return 1;
}


int do_execration(object me,object target,int i)
{
	string msg;
	int skill;
	switch(i)
	{
		case 1:
	   	 	msg=HIC"闪耀于夜空的星晨,请指引我到达彼方之路途\n"NOR;
	    		break;
		case 2:
	    		msg=HIC"以黑夜之王,大气之精灵下令,风啊！送我一程吧！\n"NOR;
	    		break;
        	case 3:
            		msg=HIC"移动法愿\n"NOR;
            		break;
		default: 
			break;
	}
	tell_object(me,msg);
        i++;
    	if(i<4&&i>=0) call_out("do_execration",1,me,target,i);
	else 
	{
  	    	skill=me->query_skill("divinemagic",1);
        	if(!skill) return 1;
            	call_out("do_hit",1,me,target,skill);
	    	return 1;
    	}
	return 1;
}



int do_hit(object me,object target,int skill)
{

	string msg;
	int num;//周围敌人的数目
	me->delete_temp("execration");
	num="/std/magic"->check_enemy_beside(me);//检查me的周围有没有敌人.敌人越多,逃跑的机会就越小,机会最小是80%
	//这个函数在magic的继承文件里面
	num*=5;
	//num的最大值是20,最小值是0
	//tell_object(me,"num is "+num+"\n");
	if(random(100)<num)
	{
		msg="$N施展移动法愿失败了\n";	
		message_vision(msg,me);
		return 1;
	}
	else
	{
		msg="$N开始施展移动法愿.....化做一道青光消失了\n";
		message_vision(msg,me);
		me->remove_all_enemy();
		"/cmds/std/go"->do_flee(me);
		msg="$N从青烟中缓缓出现......\n";
		message_vision(msg,me);
		return 1;
	}
	return 1;
}


