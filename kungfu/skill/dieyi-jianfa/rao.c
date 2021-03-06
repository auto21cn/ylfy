// 彩云绕琼山 rao.c
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character()|| !me->is_fighting(target) )
		return notify_fail("彩云绕琼山只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧!\n");

	if(me->query("family/family_name") != "舞蝶仙" && me->query("combat_exp") > 50000000)
	{
		msg = HIW "$N心魔重生，五脏移位走火入魔。\n";
		message_vision(msg, me, target);
		/*
		        me->delete_skill("dieyi-jianfa");
		        me->delete_skill("wudie-xinjing");
		        me->delete_skill("wudie-bu");
		*/
		me->add("neili", -5000);
		// me->set("qi",0);
		return 1;
	}

	if( (int)me->query_skill("dieyi-jianfa", 1) < 50 )
		return notify_fail("你的蝶翼剑法极不够娴熟，不会使用「缠」字诀。\n");

	msg = HIW "$N使出蝶翼剑法之彩云绕琼山，在$n四周舞出重重剑影。\n";
	me->start_busy(1);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/10 )
	{
		msg += RED " 结果$n被$N攻了个措手不及！\n" NOR;
		target->start_busy( 10+random(4) );
	}
	else
	{
		msg += MAG "可是$n看破了$N的企图，并没有上当。\n" NOR;
		me->start_busy( 1+random(1) );
	}
	message_vision(msg, me, target);

	return 1;
}

