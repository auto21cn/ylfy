//Cracked by Roath
//Ansi 99.12
// lilong alter 2002.01.17
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int ap, dp, damage, chance;
	string msg;
	object weapon;
                
	if ( !target ) target = offensive_target(me);
	if ( !target || !target->is_character() || target->is_corpse() || target==me) return notify_fail("你要对谁施展「断水无痕」？\n");
	if ( !me->is_fighting(target) ) return notify_fail("「断水无痕」只能在战斗中使用！\n");     
	if ( playerp(me) && me->query("family/family_name") != "蜀山派" ) return notify_fail("不是蜀山的不能用「断水无痕」！\n");
	if ( playerp(me) && me->query("shushan/duanshui_perform") !=1 ) return notify_fail("你还没领会「断水无痕」！\n");
	if ( (int)me->query("max_neili") < 5000 ) return notify_fail("你的内力不够！\n");
	if ( (int)me->query("neili") < 5000 ) return notify_fail("你的内力不足！\n");
	if ( (int)me->query("jing") < 3000 ) return notify_fail("你的精神不足，没法子施用外功！\n");
	if ( (int)me->query_skill("songhe-sword", 1) < 500 ) return notify_fail("你的松鹤剑法修为还不够，使用这一招会有困难！\n");
	if ( me->query_skill_mapped("force") != "shushan-force" ) return notify_fail("没有蜀山心法无法驾驭剑气。\n");
	if ( (int)me->query_skill("shushan-force", 1) < 500 ) return notify_fail("你的蜀山心法等级不够，不能使用这一招！\n");
	if ( !(weapon = me->query_temp("weapon")) ) return notify_fail("你必须手持剑才能使用剑法。\n");
	
	msg = CYN"\n$N手腕晃动如疾风，以砍断三千尺飞流的速度，直逼$n！\n"NOR;
	ap = me->query_skill("sword");
	dp = target->query("dodge"); 
	chance = ap*10/((ap+dp)/10);
	
	if ( target->is_busy() ) chance *= 3;
	if ( chance > 40 ) 
	{
		damage = (me->query_skill("sword")+me->query("jiali"))*2;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2, me);
		target->start_busy(1+random(3));
		msg += CYN"结果$n被$N的「断水无痕」拦腰而过！\n"NOR;
	}  
	else msg += "但是被$n躲开了。\n"NOR;
	
	message_vision(msg, me, target);
	
	if ( damage > 0 ) COMBAT_D->report_status(target);
	if ( !target->is_fighting(me) ) 
	{
		if ( living(target) ) 
		{
			if ( playerp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}
	
	me->receive_damage("qi", 200+me->query("jiali"));
	me->start_busy(1+random(3));
	return 1;
}

