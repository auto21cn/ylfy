//Edit by cloth 2000-09-19
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	int extra;
	object weapon;
	extra = me->query_skill("murong-jianfa",1);
	if ( me->query_skill("murong-jianfa",1) < 200) 
		return notify_fail("你的慕容剑法还不够纯熟！\n");
	if( !target ) target = offensive_target(me);
	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("［快剑］只能对战斗中的对手使用。\n");
	if (!weapon || weapon->query("skill_type") != "sword" || me->query_skill_mapped("sword") != "murong-jianfa")
		return notify_fail("你手里没有剑，无法使用［快剑］\n");
	if ((int)me->query("neili")<150)
		return notify_fail("你的内力不够。\n");
	me->add("neili",-150);
	weapon = me->query_temp("weapon");
	message_vision(HIM"$N使出慕容剑法中的绝招［快剑］，一招连环六剑，手中的"+weapon->name()+"闪电般向$n攻出第一剑！\n\n" NOR,me,target);
	if (random((int)me->query_skill("dodge"))>random((int)target->query_skill("dodge")/3 ) )
	{
		COMBAT_D->do_attack(me,target, weapon);
		message_vision(HIW"华山剑法！\n" NOR,me,target);
		COMBAT_D->do_attack(me,target, weapon);
		message_vision(HIC"泰山剑法！\n" NOR,me,target);
		COMBAT_D->do_attack(me,target, weapon);
		message_vision(HIR"衡山五神剑！\n" NOR,me,target);
		COMBAT_D->do_attack(me,target, weapon);
		message_vision(HIY"恒山剑法！\n" NOR,me,target);
		COMBAT_D->do_attack(me,target, weapon);
		message_vision(HIB"嵩山剑法！\n" NOR,me,target);
		COMBAT_D->do_attack(me,target, weapon);


		message_vision(WHT"$N连出六剑，结果$n被攻了个手忙脚乱！\n" NOR,me,target);
		me->start_busy(2);
		target->start_busy(3);
	}
	else
	{
		message_vision(HIC"可是$n看破了$N的招式,趁机发动进攻！\n" NOR,me,target);
		me->start_busy(3);
	}
	return 1;
}