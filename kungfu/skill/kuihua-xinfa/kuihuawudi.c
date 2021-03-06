//kuihuawudi 葵花无敌

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if( target != me )
		return notify_fail("你只能对自己用["+HIR+"葵花无敌功"+NOR+"]\n"NOR,);
	
	if ((int)me->query_skill("kuihua-xinfa", 1) < 100)
		return notify_fail("你的葵花心法太差了。\n");
	
	if( (int)me->query("neili") < 500 )
		return notify_fail("你的内力不够。\n");
	
	if( (int)me->query_temp("powerup") ) 
		return notify_fail("你已经在运功中了。\n");

	if(time() - me->query("powerupxb") <= 0)
		return notify_fail("你已经在运功中了。\n");
	
	if (!me->query("breakup"))
		return notify_fail("你任督二脉未通,无法使用["+HIR+"葵花无敌功"+NOR+"]\n"NOR,);

	if(!me->query("xy_huiyuan"))
		return notify_fail("只有会员才能使用["+HIR+"葵花无敌功"+NOR+"]\n"NOR,);
	
	skill = me->query_skill("force",1);
	
	me->add("neili", -500);
	me->receive_damage("qi",20);
	
	message_vision(HIW"$N突然大声 哈!哈!哈!哈!阴笑起来,向变了了人一样[全身如鬼如魅，飘忽来去，直似轻烟]。\n" NOR, me);
	
	me->add_temp("apply/attack", skill/5);
	tell_object(me,HIR"你的攻击力提高了!\n"NOR);
	me->add_temp("apply/dodge", skill/5);
	tell_object(me,HIR"你的防御力提高了!\n"NOR);
	me->set_temp("powerup", 1);
	me->set("powerupxb",time()+skill);
	//属性上升
	if(skill = me->query_skill("kuihua-xinfa",1))
	{
		me->add_temp("apply/strength",skill/25);
		tell_object(me,HIG"你的力量提高了!\n"NOR);
		me->add_temp("apply/dexerity",skill/25);
		tell_object(me,HIG"你的速度提高了!\n"NOR);
		me->add_temp("apply/constitution",skill/25);
		tell_object(me,HIG"你的根骨提高了!\n"NOR);
		me->add_temp("apply/intelligence",skill/25);
		tell_object(me,HIG"你的悟性提高了!\n"NOR);
	}
	
	me->start_call_out((:call_other,__FILE__,"remove_effect",me,me->query_skill("force",1)/5:),me->query_skill("force",1));
	
	if( me->is_fighting() )
		me->start_busy(4);
	return 1;
}

void remove_effect(object me, int amount)
{
	int skill;

	skill = me->query_skill("force",1);
    if (!me) return;
	me->add_temp("apply/attack", - amount);
	me->add_temp("apply/dodge", - amount);
	me->delete_temp("powerup");
	//属性还原
	if(skill = me->query_skill("kuihua-xinfa",1))
	{
		me->add_temp("apply/strength", -(amount/25));
		me->add_temp("apply/intelligence", -(amount/25));
		me->add_temp("apply/constitution", -(amount/25));
		me->add_temp("apply/dexerity", -(amount/25));
	}
		me->delete_temp("apply/strength");
		me->delete_temp("apply/intelligence");
		me->delete_temp("apply/constitution");
		me->delete_temp("apply/dexerity");
		me->delete_temp("apply/attack");
		me->delete_temp("apply/dodge");
	//删除识别参数
	me->delete("powerupxb");
	
	tell_object(me, "你的["+HIR+"葵花无敌功"+NOR+"]运行完毕，将内力收回丹田。\n");
}

