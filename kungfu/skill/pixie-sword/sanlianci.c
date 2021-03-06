// jianzhang.c  三连刺

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg;
 
	if( !target ) target = offensive_target(me);
	 if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「三连刺」只能在战斗中使用。\n");
 
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("「三连刺」开始时必须拿着一把剑！\n");

	if( (int)me->query("neili") < 100 )
		return notify_fail("你的真气不够！\n");

	if((int) me->query_skill("pixie-jian",1) < 100)
		return notify_fail("你的辟邪剑法还不到家，无法使用三连刺！\n");
	if ( (string)me->query("gender") != "无性" )
		return notify_fail("你的阴柔之气不足，无法使出辟邪剑法。\n");

	msg = RED "$N嫣然一笑，诡异之极，身法陡然加快！" NOR;
	message_vision(msg, me);
msg = 	RED"先刺双目！"NOR;
 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
msg = 	RED"后刺双足！"NOR;
 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
msg = 	RED"最后刺心！"NOR;
 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);

	me->add("neili", -50);
	me->start_busy(2);

	return 1;
}