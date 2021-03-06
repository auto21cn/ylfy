// cuijin.c  九阴白骨爪「摧筋破骨」
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	int damage, damage1, qi;
	string msg;
	if( !target ) target = offensive_target(me);
	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「摧筋破骨」只能对战斗中的对手使用。\n");
	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「摧筋破骨」只能对战斗中的对手使用。\n");

	if( (int)me->query_skill("jiuyin-baiguzhao", 1) < 500 )
		return notify_fail(WHT"你的九阴白骨爪不够娴熟，还使不出「摧筋破骨」。\n"NOR);

	if( (int)me->query_skill("force", 1) < 500 )
		return notify_fail(RED"你的内功心法火候不够，使用「摧筋破骨」会震伤自己的经脉。\n"NOR);

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你内力不够了。\n");

	msg = HIC "$N一声怪啸，绕着$n急转数圈，而后施展出「摧筋破骨」，双爪齐出，直插$n前胸。\n"NOR;
	if ( target->query("qi") < me->query("max_qi") )
		qi = target->query("qi");
	else
	{
		if ( target->query("qi") < me->query("qi") )
			qi = target->query("qi");
		else
			qi = me->query("qi");
	}
	damage1 = qi / 3;
	damage = damage1 + random(damage1*2);
	if (random(me->query("xyzx_sys/level")) > random(target->query("xyzx_sys/level")))
	{
		if (random(me->query("neili")) > random(target->query("neili")))
		{
			me->start_busy(3);
			target->receive_damage("qi", damage/2, me);
			target->receive_wound("qi", damage/2, me);
			target->apply_condition("jy_poison",10);
			me->add("neili", -1000);
			msg += HIR"$N已在$n前胸留下了五个整整齐齐的指洞！$n只觉胸口巨痛，鲜血狂喷而出！！！\n"NOR;
			target->start_busy(3);
		}
		else
		{
			me->start_busy(3);
			target->receive_damage("qi", damage/10, me);
			target->receive_wound("qi", damage/10, me);
			me->add("neili", -1000);
			msg += HIY"$N只觉$n内力浑厚！双爪竟不能惯胸而入,只在$n胸前留下了一道血痕！！！\n"NOR;
			target->start_busy(1);
		}
	}
	else
	{
		me->start_busy(3);
		me->add("neili", -1000);
		msg += HIY"可是$p早有防备，不慌不忙,卸开了$P的双爪。\n"NOR;
	}
	message_vision(msg, me, target);
	if( !target->is_killing(me) ) target->kill_ob(me);
	return 1;
}
