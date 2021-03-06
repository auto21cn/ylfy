#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon, ob;
	string msg;
	int i;

	ob = me->select_opponent();

	if (!target ) target = offensive_target(me);
	if (!target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「三分刀」只能在战斗时使用。\n");
	if (me->query_temp("perform")>time()) return notify_fail("你上一招未使完！\n");
	if ( (string)me->query("family/family_name") != "玄天派")
		return notify_fail("「三分刀」只有玄天派传人才能使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))|| (string)weapon->query("skill_type") != "blade")
    if (!objectp(weapon = me->query_temp("secondary_weapon"))|| (string)weapon->query("skill_type") != "blade")
		 return notify_fail("你使用的武器不对。\n");
		else me->set_temp("secondly_weapon",1);
	if( (int)me->query("neili") < 200 )
		return notify_fail("你的真气不够！\n");
	if( (int)me->query_skill("blade",1) < 100 || me->query_skill_mapped("blade") != "tianxin-blade")
		return notify_fail("你的「天行刀法」还不够精纯，无法使用「三分刀」！\n");
	msg = HIY "$N脚踏太虚，步法缥缈，瞬间已闪至$n的面前，“刷……刷……刷”三刀已砍向$n！\n" NOR;
	message_vision(msg, me, ob);
	me->clean_up_enemy();
	me->add("neili", -150);
	me->set_temp("perform",time()+3);
	me->set_temp("perform_sanfen",1);
	for(i = 0; i < 3; i++)
		if (me->is_fighting(ob) && ob->is_fighting(me) && ob->query("eff_qi")>0)
		{
			me->set_temp("action_msg",NOR WHT"刀光涣散\n"NOR);
			if (!weapon->query("equipped")) break;
			COMBAT_D->do_attack(me, ob,weapon, 0);
		}
		else break;
	me->delete_temp("perform_sanfen");
	me->delete_temp("secondly_weapon");
	return 1;
}

