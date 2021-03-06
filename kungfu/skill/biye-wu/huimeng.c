// meng.c 碧叶随风舞「回梦」

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「回梦」只能对战斗中的对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能使用「回梦」！\n");

	if( (int)me->query_skill("biye-wu", 1) < 40 )
		return notify_fail("你的碧叶随风舞不够娴熟，不会使用「回梦」。\n");

	if( (int)me->query_skill("biyun-xinfa", 1) < 30 )
		return notify_fail("你的碧云心法不够高，不能用来反震伤敌。\n");

	if( (int)me->query("neili", 1) < 100 )
		return notify_fail("你现在内力太弱，不能使用「回梦」。\n");

	msg = CYN "$N默念口诀，使出碧叶随风舞之「回梦」，意欲以内力震晕$n。\n"NOR;

	if (random(me->query_skill("unarmed")) > target->query_skill("force")/3 || random(me->query("xyzx_sys/level")) > target->query("xyzx_sys/level")/3)
	{

		damage = (int)me->query_skill("force") + me->query_skill("unarmed") *3;
		damage = damage/3 + random(damage/3);
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage);
		me->add("neili", -damage/3);

		msg += HIR"结果$n被$N的内力一震，眼前一黑，向后便倒，眼看就要不醒人事了！\n"NOR;

	}
	else
	{
		msg += CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;
	}
	message_vision(msg, me, target);
	me->start_busy(4);

	return 1;
}