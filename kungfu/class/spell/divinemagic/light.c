// 照明术

#include <ansi.h>

inherit SSERVER;
int do_execration(object me,object target,int i);
int do_hit(object me,object target,int skill);

int cast(object me, object target)
{


	int  skill;
	string msg;
	skill=me->query_skill("divinemagic",1);
	if(!skill||skill<=20)
		return notify_fail("你还无法明白照明术的咒语\n");
	if(me->query_temp("execration"))
		return notify_fail("你正在念咒。\n");
	if(me->query_temp("execration"))
		return notify_fail("你正在念咒。\n");
	if((int)me->query("mana") < 50 )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("sen") < 10 )
		return notify_fail("你的精神没有办法有效集中！\n");
	if(me->query_temp("cast_light")) return notify_fail("你已经施展了照明术\n");
	me->add("mana", -50);
	me->receive_damage("sen", 10);

	msg = ""+me->name()+"自言自语不知道在说些什麽。\n";
        message("vision",msg, environment(me), ({me}));
	tell_object(me,"你在脑海回忆起照明术的咒语,低声吟诵着......\n");
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
	   	 	msg=HIC"万能的光之神\n"NOR;
	    		break;
		case 2:
	    		msg=HIC"恳求您赐予我耀眼的光芒\n"NOR;
	    		break;
        	case 3:
            		msg=HIC"照亮这漆黑的大地\n"NOR;
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
		msg="$N的照明术失败了\n";	
		message_vision(msg,me);
		return 1;
	}
	else
	{
		msg="随着$N将照明术咒语吟诵完毕,\n"
		    "$N身上开始渐渐发出柔和的光芒,\n"
		    "周围的景物渐渐明亮起来\n";
		message_vision(msg,me);
		me->set_temp("cast_light",1);
        	//add_light(me,1); 未知改函数的用处，有时间再查
		if(me->is_fighting())
			me->start_busy(me->query_busy()+2);
		me->start_call_out((: call_other, __FILE__,"remove_effect",me :),skill*2);
	}
	return 1;
}


void remove_effect(object me)
{      
	string msg;
	if (!me) return;
    	me->delete_temp("cast_light");
    	// add_light(me,-1); 未知改函数的用处，有时间再查
    	msg=CYN"$N的身体渐渐暗淡了下去，恢复了正常。\n"NOR;
    	message_vision(msg,me);
    	return;
    
}
