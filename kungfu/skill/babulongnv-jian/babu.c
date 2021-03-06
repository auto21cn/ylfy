#include <ansi.h>
#include "/kungfu/skill/eff_msg.h"
#include <combat.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)

{
	object weapon;
	string msg;
	int damage;
	weapon = me->query_temp("weapon");
	if(!target) target = offensive_target(me);
	if(!target || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("「八部剑阵」只能在战斗中使用。\n");
	if( (int)me->query_str() < 40 || (int)me->query_dex() < 40 || (int)me->query_con() < 40 || (int)me->query_int() < 50 )
		return notify_fail("你现在还用不了这么精深奥妙的绝技.\n");
	
	if (me->query_skill_mapped("parry") != "babulongnv-jian")
		return notify_fail("你所使用的招架不对。\n");
	
	if( (int)me->query("max_neili") < 1200 )
		return notify_fail("这么强的武技岂能是你这点儿内力修为就能用的！\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的内力不够！\n");
	msg = HIC "\n$N清呤一声"HIY"“八部剑阵断人魂”"BLU"“龙女飞天惊神魔!”"HIC"腾身一跃，踪迹全无！。\n" NOR;
	if (random(me->query("per")) > target->query("per") / 3)
	{
		msg += HIR "陡然间，$N飞身而下，千丝剑气绕向$n，姿势曼妙无比，直如天女散花！$n看得呆了，竟然忘记了出招\n"NOR;
		target->start_busy(7);
		damage = me->query_skill("babulongnv-jian") * me->query("per");
		damage = damage + random(damage/2);
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
		me->add("neili", -200);
		call_out("perform2", 6, me, target);
	}
	else
	{
		me->start_busy(1);
		me->add("neili", -100);
		msg += HIW"$n全神贯注，毫不大意，$N眼见无机可趁，只得将身形显露出来。\n"NOR;
	}
	message_vision(msg, me, target);
	return 1;
}

int perform2(object me, object target)
{
	string msg,msg1;
	int i;
	object weapon;
	weapon = me->query_temp("weapon");

	if(!target) target = offensive_target(me);
	if(!target || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("「八部剑阵」只能在战斗中使用。\n");

	if (!me || !target) return 0;
	if(!living(target))
		return notify_fail("对手已经不能再战斗了。\n");
	if (!weapon || weapon->query("skill_type") != "sword" || me->query_skill_mapped("sword") != "babulongnv-jian")
		return notify_fail("你手中无剑，八部剑阵无法使完！\n");
	if( (int)me->query("neili", 1) < 800 )
		return notify_fail("你待要再乘胜追击，突然发现自己已经无力出招了。\n");

	i = (me->query_skill("sword")*2/3);
	msg = HIW "$N手中的"+weapon->query("name")+HIW"如同陀螺一般围住自己转动不息，解着一股螺旋之力，迅捷无比的射向$n。\n"NOR;
	msg1=YEL"$N落回地面，趁着$n慌乱之时，连接攻击。\n"NOR;
	me->add_temp("apply/attack", i);
	me->add_temp("apply/dodge", i);
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_QUICK);
	msg = HIR "$N剑出连环，似真似幻,招招不离$n的要害之处。\n"NOR;
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_QUICK);
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_QUICK);
	msg = HIC "$N反身回刺,竟然将$n的招数齐齐逼回自身。\n"NOR;
	message_vision(msg, me, target);
	COMBAT_D->do_attack(target,target, me->query_temp("weapon"),TYPE_QUICK);
	message_vision(msg, me, target);
	COMBAT_D->do_attack(target,target, me->query_temp("weapon"),TYPE_QUICK);
	me->add("neili", -300);
	target->start_busy(2);
	me->add_temp("apply/attack", -i);
	me->add_temp("apply/dodge", -i);
	message_vision(msg1, me,target);
	call_out("perform3", 2, me, target);
	return 1;
}


int perform3(object me, object target)
{
	object weapon;
	string msg;
	int skill, damage, p;
	weapon = me->query_temp("weapon");
	if(!target) target = offensive_target(me);
	if(!target || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("「八部剑阵」只能在战斗中使用。\n");

	skill = (int)me->query_skill("babulongnv-jian", 1);

	if(!living(target))
		return notify_fail("对手已经不能再战斗了。\n");

	if( (int)me->query("neili", 1) < 800 )
		return notify_fail("你待要再乘胜追击，突然发现自己已经无力出招了!\n");

	msg = HIG "\n$N手中的"+weapon->query("name")+HIG"连画半圆，光幕将$N全身护住竟然变为一个巨大的光球，身剑合一，射向$n。\n"NOR;
	if (random(20) > 10)
	{
		msg += HIR "$n呆立当场，未待闪躲，被$N的巨大光球穿透而过！！。\n" NOR;
		me->start_busy(2);
		target->start_busy(2);
		damage = skill*8;
		damage = damage + random(damage/8);
		p = target->query("qi")*100/target->query("max_qi");
		msg += damage_msg(damage, "内伤");
		msg += "( $n"+eff_status_msg(p)+" )\n";

		target->receive_damage("qi", damage*2/5);
		target->receive_wound("qi", damage*2/5);
		me->add("neili",700);
	}
	else
	{
		me->add("neili", -200);
		target->start_busy(3);
		msg += HIW"\n$n连忙一个跟头翻出圈外，却也被吓的浑身是汗！\n" NOR;
	}
	message_vision(msg, me, target);
	return 1;
}

