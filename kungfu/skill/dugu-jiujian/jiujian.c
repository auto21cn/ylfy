// 九剑和一
// by lonely
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon, ob;
	int count,skill;
	string msg;
	if( !me->is_fighting() )
		return notify_fail("「九剑合一」只能在战斗中使用。\n");
	if( !target ) target = offensive_target(me);
	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「九剑合一」只能在战斗中使用。\n");
	if (me->query_temp("perform"))  return notify_fail("你上一个招式还没完成!\n");
	if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if((int)me->query_skill("dugu-jiujian",1) < 1000)
		return notify_fail("你的独孤九剑的火候还不到家, 不能使用这一绝技 !\n");
	if((int)me->query_skill("sword",1) < 1000)
		return notify_fail("你的基本剑法的火候还不到家, 不能使用这一绝技 !\n");
	if( (int)me->query("neili") < 8000 )
		return notify_fail("你的真气不够！\n");
	if( (int)me->query("max_neili") < 20000 )
		return notify_fail("你的内力修为不够！\n");
	msg =
	    HIY "\n$N心中默念无招胜有招，轻叹一声求拜不得，使出独孤九剑的绝技「九剑合一」！\n" NOR;
	message_vision(msg,me,target);
	me->clean_up_enemy();
	skill=me->query_skill("dugu-jiujian",1);
	ob = me->select_opponent();
	me->add("neili", -3000);
	if (weapon == me->query_temp("secondary_weapon"))
		me->set_temp("secondly_weapon",1);
	for (count=0; count<10; count++)
	{
		me->add_temp("str",skill/10);
		COMBAT_D->do_attack(me, ob, weapon, 0);
	}
	me->delete_temp("str");
	me->delete_temp("secondly_weapon");
	
	return 1;
}

void del_perform(object me)
{
	if (!me) return;
	me->delete_temp("perform");
}
