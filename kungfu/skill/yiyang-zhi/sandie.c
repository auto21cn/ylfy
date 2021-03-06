#include <ansi.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
	string msg;
	int damage, p;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("「阳关三叠」只能在战斗中使用。\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("只有空手才能施展「阳关三叠」。\n");

	if( (int)me->query_skill("yiyang-zhi", 1) < 100 || (int)me->query_str() < 25)
		return notify_fail("你有的功夫还不够娴熟，不会使用「阳关三叠」。\n");

	if(me->query_skill("kumu-shengong", 1) <320)
		return notify_fail("以你现在的内功修为还使不出「阳关三叠」。\n");

	if (me->query_skill_mapped("force") != "kumu-shengong" )
		return notify_fail("你所使用的内功不对。\n");

    if ( me->query_skill_mapped("unarmed") != "yiyang-zhi" )
        return notify_fail("你现在无法使用「阳关三叠」进行攻击。\n");

	if (me->query_skill_mapped("parry") != "yiyang-zhi")
		return notify_fail("你所使用的招架不对。\n");
	if( (int)me->query("neili") < 1200 )
		return notify_fail("你的内力修为太弱，不能使用「阳关三叠」！\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("你的真气不够！\n");

	if (me->query("yd_2") && (target->query_skill_mapped("force")=="hamagong" || target->query_skill_mapped("unarmed") == "hamagong"))
	{
		msg = YEL "\n$N背向$n，凝气于指，一式「阳关三叠」反手缓缓点出，纯阳指力直袭$n胸口！\n" NOR;
		if (random(me->query_skill("unarmed")) > target->query_skill("dodge") /4 )
		{
			me->start_busy(1);
			target->start_busy(1);
			damage = (int)me->query_skill("yiyang-zhi", 1) + me->query_skill("unarmed");
			damage = (int)me->query_skill("kurong-changong", 1) +damage;
			damage = random(damage)+150;
			target->receive_damage("qi", damage);
			target->receive_wound("qi", damage/2);
			me->add("neili", -300);
			p = (int)target->query("qi")*100/(int)target->query("max_qi");
			msg += HIR "$n一见之下，大为失色，发现这似乎正是自己的克星！\n"NOR;
			msg += damage_msg(damage, "内伤");
			msg += "( $n"+eff_status_msg(p)+" )\n";
		}
		else
		{
			me->start_busy(3);
			me->add("neili", -200);
			msg += HIY"$p见这反手点穴似乎正是蛤蟆功的克星，识得厉害，危及之中一个铁板桥，上身向后一倒，艰难的躲过这一招。\n"NOR;
		}
	}
	else
	{
		msg = YEL "\n$N凝气于指，一式「阳关三叠」点出，但听得嗤嗤声响，一股纯阳的内力直袭$n胸口！\n" NOR;
		if (random(me->query_skill("unarmed")) > target->query_skill("parry") / 4)
		{
			me->start_busy(1);
			target->start_busy(2);
			damage = (int)me->query_skill("yiyang-zhi", 1);
			//              damage = (int)me->query_skill("qiantian-yiyang", 1) +damage;
			damage = (int)me->query_skill("kurong-changong", 1) +damage;
			damage = damage + random(damage/2);
			target->receive_damage("qi", damage);
			target->receive_wound("qi", damage/3);
			me->add("neili", -(damage/2));
			p = (int)target->query("qi")*100/(int)target->query("max_qi");
			msg += damage_msg(damage, "内伤");
			msg += "( $n"+eff_status_msg(p)+" )\n";
			if(me->query_skill("yiyang-zhi", 1) > 150)
				call_out("perform2", 0, me, target);
		}
		else
		{
			me->start_busy(3);
			me->add("neili", -100);
			msg += HIY"可是$p一个巧云翻身，远远的躲了开去。\n"NOR;
		}
	}
	message_vision(msg, me, target);
	return 1;
}

int perform2(object me, object target)
{
	string msg;

	if (!me || !target) return 0;
	if(!living(target))
		return notify_fail("对手已经不能再战斗了。\n");

	if( (int)me->query("neili", 1) < 600 )
		return notify_fail("你待要再出第二指，却发现自己的内力不够了！\n");

	msg = YEL "\n接着$N踏前一步，出第二指隔空点向$n胸前“玉堂穴”，认穴竟无厘毫之差！\n"NOR;
	if (random(me->query_skill("unarmed")) > target->query_skill("dodge") / 4)
	{
		msg += HIR "结果一指点中，$n只觉得全身气脉通道阻塞，真气立受干挠！\n"NOR;
		me->start_busy(1);
		target->start_busy(me->query_skill("force",1)/30);
		me->add("neili", -(me->query_skill("force",1)/2));
		if((int)me->query_skill("yiyang-zhi", 1) > 200)
			call_out("perform3", 0, me, target);
	}
	else
	{
		me->start_busy(3);
		me->add("neili", -150);
		target->add("neili", -50);
		msg += HIY"\n$p眼看逼无可逼，便也一指点去，两根指尖相碰，$p顺势跳了开去。\n" NOR;
	}
	message_vision(msg, me, target);
	return 1;
}

int perform3(object me, object target)
{
	int skill;
	string msg;
	skill = (int)me->query_skill("yiyang-zhi", 1);
	skill = skill/10;

	if(!living(target))
		return notify_fail("对手已经不能再战斗了。\n");

	if( (int)me->query("neili", 1) < 400 )
		return notify_fail("你待要再出第三指，却发现自己的内力不够了！\n");

	msg = YEL "\n紧跟着$N一阳指第三次点出，以纯阳内力，同时透入$n体内任脉紫宫穴、阴维脉大横穴、冲脉幽门穴、带脉章门穴和阴跤脉晴明穴！\n"NOR;
	if (random(me->query_skill("unarmed")) > target->query_skill("dodge") / 4)
	{
		me->add("neili", -200);
		msg += HIR "$n只觉体内奇经八脉中内息为之一怠，全身气力竟然提不起来了！\n" NOR;
		target->add_temp("apply/attack", -100);
		target->add_temp("apply/dodge", -100);
		target->add_temp("apply/parry", -100);
		target->add("neili", -500);
		call_out("back", 3 + skill, target);
	}
	else
	{
		me->start_busy(target->query_skill("force",1)/30);
		me->add("neili", -300);
		target->start_busy(2);
		msg += HIY"\n$p喘息未定，见$P指力如狂风般点来，连忙又跃开数尺，狼狈地避开。\n" NOR;
	}
	message_vision(msg, me, target);
	return 1;
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 100);
	target->add_temp("apply/dodge", 100);
	target->add_temp("apply/parry", 100);
}
