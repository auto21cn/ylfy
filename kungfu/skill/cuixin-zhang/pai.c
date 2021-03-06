#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("一拍两散只能对战斗中的对手使用。\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "已经不能动了！\n");

	if( (int)me->query_skill("cuixin-zhang", 1) < 500 )
		return notify_fail("你的摧心掌不够娴熟，不会使用「一拍两散」。\n");

	if ( (string)me->query("family/family_name") != "玄天派")
		return notify_fail("「一拍两散」只有玄天派传人才能使用。\n");

	msg = HIM "$N手一摇，一招「一拍两散」已然隐隐击在$n的身上。\n"NOR;

	if( random( me->query_skill("cuixin-zhang",1)+me->query_skill("unarmed",1) ) > (me->query_skill("unarmed",1)*2)/3 )
	{
		msg += HIR "$p躲闪不及，被$N拍中身上几处穴道，顿时动弹不得。\n" NOR;
		target->start_busy( (int)me->query_skill("cuixin-zhang") / 40 );
		me->add("neili", -500);
	}
	else
	{
		me->start_busy(2);
		me->add("neili",-300);
		msg += HIC "$p看出了$N的招式空隙，躲了过去。\n" NOR;
	}
	message_vision(msg, me, target);

	return 1;
}

