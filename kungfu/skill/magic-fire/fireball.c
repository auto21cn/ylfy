//fireball.c  ������

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage,damagic;
        string msg;       

    if (!target ) target = offensive_target(me);
    if (!target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail(RED"��������ֻ�ܶ�ս���еĶ���ʹ�á�\n"NOR);
       
	if((int)me->query("neili")< 600)
	    return notify_fail("��ķ���̫���ˣ�\n");
	
	if((int)me->query_skill("magic-fire",1)< 150)
	     return notify_fail("��Ļ�ϵħ��̫���ˣ�\n");

        msg = RED "$N"RED"��������������������.���н���������һ�Ż���.���򽥴�.\n"NOR;
        msg += RED"$N"RED"��������,��֪�������Ѷ�׼��$n"RED"��$n"RED"���������⣬������Ծ��\n"NOR;
        msg += RED"$N"RED"���һ��  ������!!  ,���еĻ���ֱ��$n"RED"��ȥ���������.��\n"NOR;
        if ( random(me->query("combat_exp"))>(int)target->query("combat_exp")/3)
        {
                damage = (int)me->query_skill("magic-fire", 1);
//�Ի�����Ŀ��������
       if ((int)target->query("magicgift")==1)
{
damagic=100+damage;
                target->receive_damage("qi", damagic);
damagic=50+damage;
                target->receive_wound("qi", damagic);
if (wizardp(me))
tell_object(me, "\n����ɱ��Ϊ"+damagic+"�㡣\n" NOR);
}
//��ˮ����Ŀ��ǿ��
else  if ((int)target->query("magicgift")==2)
{
damagic=1800+damage*4;
                target->receive_damage("qi", damagic);
damagic=1800+damage*2;
                target->receive_wound("qi", damagic);
if (wizardp(me))
tell_object(me, "\n����ɱ��Ϊ"+damagic+"�㡣\n" NOR);
}
else 
{
damagic=350+damage;
target->receive_damage("qi", 350+damage*2);
target->receive_wound("qi", 350+damage);
if (wizardp(me))
tell_object(me, "\n����ɱ��Ϊ"+damagic+"�㡣\n" NOR);
}

        msg += HIR"$n"HIR"����û����ܣ�һ���޴����,�˶���\n"NOR;
        msg += HIR"������$n"HIR"�����ϣ�$n"HIR"ȫ������������!!\n"NOR;
		message_vision(msg, me, target);
		COMBAT_D->report_status(target);
        } else
        {
        msg += HIY"����$p"HIY"����һЦ��������ת.\n"NOR;
        msg += HIY"������$p"HIY"���໮�����������ˡ�\n"NOR;
		message_vision(msg, me, target);
        }
if (target->query("qi") < 1)target->set("qi",0);
if (target->query("eff_qi") < 1)target->set("eff_qi",0);
if (target->query("max_qi") < 1)target->set("max_qi",0);                
if (target->query("jing") < 1)target->set("jing",0);
if (target->query("eff_jing") < 1)target->set("eff_jing",0);
if (target->query("max_jing") < 1)target->set("max_jing",0);                
if (target->query("neili") < 1)target->set("neili",1);
if (target->query("max_neili") < 1)target->set("max_neili",0);
                me->start_busy(2);
                me->add("neili", -250);
        return 1;
}