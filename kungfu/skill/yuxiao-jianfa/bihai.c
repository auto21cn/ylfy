// bihai.c
// by victori

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp, jing_wound;
	me->clean_up_enemy();
	target = me->select_opponent();
	skill = me->query_skill("yuxiao-jianfa",1);
	if( !(me->is_fighting() ))
		return notify_fail("���̺���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("id") != "xiao")
		return notify_fail("�����Ҫʹ���ܴ���������\n");
	if( me->query_skill("bibo-shengong",1) < 150)
		return notify_fail("��ı̲��񹦵ȼ�����, ����ʹ�á��̺�����������\n");
	if( skill < 90)
		return notify_fail("������｣���ȼ�����, ����ʹ�á��̺�����������\n");
	if( me->query("neili") < 250 )
		return notify_fail("��������������޷����á��̺�����������\n");
	msg = HIC "$N����̤�Ű��Է�λ����������̺���������"+weapon->name() +"������һʱ���羪���İ���һʱ����ϸ���ḧ��̲��\n";
	message_vision(msg, me, target);
	ap = me->query_skill("sword",1) + skill;
	dp = target->query_skill("dodge",1) / 2;
	if( dp < 1 )
		dp = 1;
	if( random(ap) > dp )
	{
		if(userp(me))
			me->add("neili",-200);
		msg = "$n��֪�����������������裬��ȫʧȥ�ֿ�֮����\n" NOR;
		jing_wound = (int)me->query_skill("yuxiao-jianfa",1)+(int)me->query_skill("sword");
		jing_wound = jing_wound/2 + random(jing_wound);
		if(jing_wound > target->query("jing"))
			jing_wound = target->query("jing");
		target->receive_damage("jing", jing_wound);
		target->receive_wound("jing", jing_wound/2);
		target->start_busy(2);
		me->start_busy(random(3));
	}
	else
	{
		if(userp(me))
			me->add("neili",-100);
		msg = "ǿ���ڹ���ǿ���ƣ��������ѿ���ס����\n"NOR;
		me->start_busy(random(3));
	}
	message_vision(msg, me, target);
	if(!target->is_fighting(me)) target->fight_ob(me);
	return 1;
}