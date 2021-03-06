#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("悲痛莫明只能对战斗中的对手使用。\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "已经不能动了！\n");

	if( (int)me->query_skill("damo-force", 1) < 600 )
		return notify_fail("你的达摩神功不够娴熟，无法施展大悲掌。\n");

	if( (int)me->query_skill("dabei-zhang", 1) < 600 )
		return notify_fail("你的大悲掌不够娴熟，不会使用「悲痛莫明」。\n");

	msg = HIB "$N脸上露出一丝悲痛的神情，和手念了一声阿弥陀佛,\n"NOR;
	msg += HIB "双手缓缓的推出，看似平常的一招，可是看不出一丝\n"NOR;
	msg += HIW "破绽，次招正是大悲掌最后绝技「悲痛莫明」。\n"NOR;

	if( random(me->query("xyzx_sys/level")) > (int)target->query("xyzx_sys/level")/3 )
	{
		msg += HIW "$p企图突破$N的攻击范围，但是被$N的掌风避的毫无退路。\n" NOR;
		target->start_busy( random(4));
		target->apply_condition("no_perform", 10);
		me->add("neili", -500);
	}
	else
	{
		me->start_busy(2);
		me->add("neili",-300);
		msg += HIC "$p一眼看出了$N的破绽，躲了过去。\n" NOR;
	}
	message_vision(msg, me, target);

	return 1;
}

