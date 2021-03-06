#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "亢龙有悔" NOR "」"
#define HUIP "「" HIR "亢龙有悔" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);
	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail(HUI "只能对战斗中的对手使用。\n");

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail(HUI "只能空手使用。\n");

	if ((int)me->query_skill("force") < 380)
		return notify_fail("你内功修为不够，难以施展" HUI "。\n");

	if ((int)me->query("max_neili") < 6000)
		return notify_fail("你内力修为不够，难以施展" HUI "。\n");

	if ((int)me->query_skill("xianglong-zhang", 1) < 250)
		return notify_fail("你降龙十八掌火候不够，难以施展" HUI "。\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你现在真气不够，难以施展" HUI "。\n");

	if (! living(target))
		return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	// 第一掌
	ap = me->query_skill("xianglong-zhang", 1) + me->query_str(1) * 5;
	dp = target->query_skill("dodge" ,1) + target->query_dex(1) * 5;

	message_vision(HIW "\n忽然$N" HIW "身形激进，左手一划，右手呼的一掌"
	               "拍向$n" HIW "，正是降龙十八掌" HUIP "。\n力自掌生之际"
	               "说到便到，以排山倒海之势向$n" HIW "狂涌而去，当真石"
	               "破天惊，威力无比。\n" NOR, me, target);

	if (ap * 3 / 5 + random(ap) > dp)
	{
		damage = ap + random(ap)*3;
		target->add("qi",-damage);
		target->add("eff_qi",-damage);
		msg =HIR "$P身形一闪，竟已晃至$p跟前，$p躲闪不及，顿被击个正中。\n" NOR;
	}
	else
	{
		msg = HIC "却见$p气贯双臂，凝神应对，$P掌力如泥牛入海，尽数卸去。\n" NOR;
	}
	message_vision(msg, me, target);

	// 第二掌
	ap = me->query_skill("xianglong-zhang", 1) + me->query_str(1) * 5;
	dp = target->query_skill("parry", 1) + target->query_int(1) * 5;

	message_vision(HIW "\n$N" HIW "一掌既出，身子已然抢到离$n" HIW "三"
	               "四丈之外，后掌推前掌两股掌力道合并，\n又是一招" HUIP
	               "攻出，掌力犹如怒潮狂涌，势不可当。霎时$p便觉气息窒"
	               "滞，立足不稳。\n" NOR, me, target);

	if (ap * 2 / 3 + random(ap) > dp)
	{
		damage = ap + random(ap)*3;
		target->add("qi",-damage);
		target->add("eff_qi",-damage);
		msg =HIR "$p一声惨嚎，被$P这一掌击中胸前，喀嚓喀嚓断了几根肋骨。\n" NOR;
	}
	else
	{
		msg = HIC "可是$p全力抵挡招架，竟似游刃有余，将$P的掌力卸于无形。\n" NOR;
	}
	message_vision(msg, me, target);

	// 第三掌
	ap = me->query_skill("xianglong-zhang", 1) + me->query_str(1) * 5;
	dp = target->query_skill("force", 1) + target->query_con(1) * 5;

	message_vision(HIW "\n紧跟着$N" HIW "右掌斜挥，前招掌力未消，此招掌"
	               "力又到，竟然又攻出一招" HUIP "，\n掌夹风势，势如破竹，"
	               "便如一堵无形气墙，向前疾冲而去。$n" HIW "只觉气血翻"
	               "涌，气息沉浊。\n" NOR, me, target);

	if (ap *11 / 20 + random(ap) > dp)
	{
		damage = ap + random(ap)*3;
		target->add("qi",-damage);
		target->add("eff_qi",-damage);
		msg =HIR "结果$p躲闪不及，$P掌劲顿时穿胸而过，顿时口中鲜血狂喷。\n" NOR;
	}
	else
	{
		msg = HIC "$p眼见来势凶猛，身形疾退，瞬间飘出三丈，脱出掌力之外。\n" NOR;
	}
	message_vision(msg, me, target);
	me->start_busy(3);
	me->add("neili", -300 - random(600));
	return 1;
}
