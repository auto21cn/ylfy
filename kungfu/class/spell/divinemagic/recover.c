// 治愈术

#include <ansi.h>

inherit SSERVER;
int do_execration(object me,object target,int i);
int do_hit(object me,object target,int skill);

int cast(object me, object target)
{


	int  skill;
	string msg;
	skill=me->query_skill("divinemagic",1);
	if(!skill||skill<=10)
		return notify_fail("你没有学会如何使用？\n");
	if(me->query_temp("execration"))
		return notify_fail("你正在念咒。\n");
	if(me->query_temp("execration"))
		return notify_fail("你正在念咒。\n");
	if((int)me->query("mana") < 50 )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("sen") < 10 )
		return notify_fail("你的精神没有办法有效集中！\n");

	if(target&&target!=me)
		return notify_fail("治愈术无法给他人疗伤\n");
	me->add("mana", -50);
	me->receive_damage("sen", 10);

	msg = ""+me->name()+"自言自语不知道在说些什麽。\n";
        message("vision",msg, environment(me), ({me}));
	tell_object(me,"你在脑海回忆起治愈术的咒语,低声吟诵着......\n");
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
	   	 	msg=HIC"天地间神圣的精灵\n"NOR;
	    		break;
		case 2:
	    		msg=HIC"拥有母性的大地气息\n"NOR;
	    		break;
        	case 3:
            		msg=HIC"用您慈爱的关怀,救救我吧\n"NOR;
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
	if(!objectp(me)) return 1;
	me->delete_temp("execration");
	if(random(100)<1)
	{
		msg="$N的治愈术失败了\n";	
		message_vision(msg,me);
		return 1;
	}
	else
	{
		me->receive_curing("kee", 100 + (int)me->query_skill("magic")/2 );
		me->add("kee", 100 + (int)me->query_skill("magic")/2 );
		if( (int)me->query("kee") > (int)me->query("eff_kee") ) 
			me->set("kee", (int)me->query("eff_kee"));
		msg="随着治愈术咒语的吟诵完毕,你感觉好多了\n";
		message_vision(msg,me);
		
		return 1;
	}
	return 1;
}
