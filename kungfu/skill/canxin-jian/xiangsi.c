//xiangxi.c  相思三剑

#include <ansi.h>
#include <combat.h>
#include <condition.h>
inherit F_SSERVER;

int perform(object me, object target)
{       
	int times, i;
	object weapon = me->query_temp("weapon");
	
	if ( !target ) target = offensive_target(me);
	if ( !target || !target->is_character() || target->is_corpse() || target==me) 
		return notify_fail("你要对谁施展「相思三剑」？\n");
	if ( !weapon ) 
		return notify_fail("「相思三剑」用剑才能使出！\n");
	if ( !me->is_fighting(target) ) 
		return notify_fail("「相思三剑」只能在战斗中使用！\n");
	if ( playerp(me) && me->query("family/family_name") != "蜀山派" ) 
		return notify_fail("非蜀山不能用「相思三剑」！\n");
	if ( playerp(me) && me->query("shushan/xiangsi_perform") !=1 ) 
		return notify_fail("没有伤心的体会，用不了缠绵的「相思三剑」！\n");
	if ( me->query_skill_mapped("force")!="shushan-force" ) 
		return notify_fail("「相思三剑」必须以蜀山心法做底子！\n");
	if ( me->query_skill_mapped("sword")!="canxin-jian" ) 
		return notify_fail("残心剑法必须激发在基本剑法上，才可以使用「相思三剑」！\n");
	if ( (int)me->query("max_neili") < 10000 ) 
		return notify_fail("你的内力不够！\n");
	if ( (int)me->query("neili") < 5000 ) 
		return notify_fail("你的内力不足！\n");
	if ( (int)me->query("jing") < 300 ) 
		return notify_fail("你的精神不足，没法子施用外功！\n");
	if ( (int)me->query_skill("shushan-force", 1) < 500 ) 
		return notify_fail("你的蜀山心法修为还不够，使用这一招会有困难！\n");
	if ( (int)(times=me->query_skill("canxin-jian", 1)) < 900) 
		return notify_fail("你的残心剑修为还不够，使用这一招会有困难！\n");
	
	message_vision(MAG"$N集思凝神，猛地施出残心剑的绝招「相思三剑」，向$n连续发动进攻！\n\n"NOR,me,target);
	times /= 90;
	if( times > 50 ) times = 50;
	me->add_temp("lianzhao", times);
	
	for ( i=0; i<times; i++ )
	{
		switch ( random(4) )
		{
			case 0:
				message_vision(HIG"$n被剑意中的相思之苦感染，身中情毒！\n"NOR,me,target);
				target->apply_condition("xiangsi", 20);
				break;
			case 1:
				message_vision(HIG"一股酒气冲向$n，$n似乎有了点酒意！\n"NOR,me,target);
				target->apply_condition("drunk", 20);
				break;
			case 2:
				message_vision(HIG"问世间情为何物？\n"NOR,me,target);
				message_vision(HIG"梦无痕，随风逝，仙灵如月长伴君．\n"NOR,me,target);  
				target->apply_condition("xiang_air", 20);
				break;
		}
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	}
	me->start_busy(1+random(3));
	target->start_busy(1+random(3));
	message_vision(HIG"$N的「相思三剑」用功完毕，气回丹田,缓缓收功.\n"NOR,me,target);
	me->receive_damage("qi", 100);
	me->receive_damage("jing", 100);
	me->add("neili", -100*times);
	me->delete_temp("lianzhao");
	return 1;
}
