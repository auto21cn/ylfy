//npc�书��������!!
#include <ansi.h>
inherit SKILL;
#include <ansi.h>
#include <combat.h>
//inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";
string *order = ( {""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});


mapping *action = (
{
([   "action": "$N���һ�� "HIC"����֮ʥ��"NOR" ����$w��$n��$lֱ��������",
	"force" : 8620,
	"dodge":     100,
	"parry":                300,
	"damage":     8600,
"damage_type":   "����"
	 ]),
([   "action": "$N���һ�� "HIY"����֮��"NOR" ����$w��$n��$lб��������",
	"force" : 8620,
	"dodge":     100,
	"parry":                300,
	"damage":     8600,
"damage_type":   "����"
	 ]),
([   "action": "$N���һ�� "HIB"���ں�����"NOR" ���е�$w����һ�����ǣ���$n��$l���˹�ȥ��",
	"force" : 8620,
	"dodge":     100,
	"parry":                300,
	"damage":     8600,
"damage_type":   "����"
	 ]),
([   "action": "$N���һ�� "HIW"���������"NOR"���е�$w���˸���Բ����$n��$l���˹�ȥ��",
	"force" : 8620,
	"dodge":     100,
	"parry":                300,
	"damage":     8600,
"damage_type":   "����"
	 ]),
([   "action": "$N���һ�� "HIM"��������"NOR"���е�$w����$n��$l���˹�ȥ��",
	"force" : 8620,
	"dodge": 100,
	"parry": 300,
	"damage": 8600,
"damage_type":   "����"
	 ]),
([   "action": "$N���һ�� "HIR"��ħ���ȵ���"NOR"���е�$w����$n��$l���˹�ȥ��",
	"force" : 8620,
	"dodge": 100,
	"parry": 300,
	"damage": 8600,
"damage_type":   "����"
	 ]),
});

int valid_learn(object me)
{
	object ob;

	if( !(ob = me->query_temp("weapon"))
	        ||   (string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ�ѽ�������������\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry";
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("magic-sword", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 300
	        ||   (int)me->query("neili") < 300 )
		return notify_fail("�����������������û�а취��ϰ���󽣷���\n");
	me->receive_damage("qi", 300);
	me->add("neili", -300);
	//write("�㰴����ѧ����һ�����󽣷���\n");
	return 1;
}


mixed hit_ob(object me, object victim,int damage_bonus)

{
	int level;
	object weapon;
	level   = (int) me->query_skill("magic-sword",1);
//        target = me->select_opponent();
	weapon = me->query_temp("weapon");

	if( random(2)==1 && random(level) > 150)
	{
		if (userp(victim))
			victim->start_busy(3+random(2));
		else    victim->start_busy(2);
		return HIC "��������!!����$NͻȻ����,����һ��ħ����$n������ס��ʱ���ܶ���!!\n" NOR;
	}
	if( random(2)==1 && random(level) > 150 && victim->query("qi") > 50
	        && victim->query("eff_qi") > 50)
	{
		if (userp(victim))
		{
			if (victim->query("qi")/12 > 20)
				victim->add("qi",-victim->query("qi")/12);
			if (victim->query("eff_qi")/12 > 20)
				victim->add("eff_qi",-victim->query("eff_qi")/12);
		}
		else
		{
			victim->add("qi",-1090);
			victim->add("eff_qi",-1090);
		}
		return HIB "�����ں�����!!����$NͻȻ����,����һ��ħ����$n��ը�÷�������!!\n" NOR;
	}
	if( random(2)==1 && random(level) > 150 && victim->query("jing") > 50
	        && victim->query("eff_jing") > 50)
	{
		if (userp(victim))
		{
			if (victim->query("jing")/12 > 20)
				victim->add("jing",-victim->query("jing")/12);
			if (victim->query("eff_jing")/12 > 20)
				victim->add("eff_jing",-victim->query("eff_jing")/12);
		}
		else
		{
			victim->add("jing",-500);
			victim->add("eff_jing",-500);
		}
		return HIW "�����ǹ�ʸ!!����$NͻȻ����,����һ��ħ����$n�����к����ͷʹ�ޱ�!!\n" NOR;
	}
	if (damage_bonus < 100) damage_bonus=100;
	if( damage_bonus > 200 )
	{
		victim->receive_wound("qi", damage_bonus );
		return HIR "ͻ!!һ��Ӱ������һ����Ѫ��$n���������\n" NOR;
	}
	if( damage_bonus < 120 )
	{
		victim->receive_wound("qi", damage_bonus );
		return YEL "��!!һ��Ӱ������$n�ƺ�һ��,���ӻ������Σ�\n" NOR;
	}
	else
	{
		victim->receive_wound("qi", damage_bonus );
		return HIM "��!!һ��Ӱ��������������������һ�����죬���Ͼ�����һЩѪ�Σ�\n" NOR;
	}

}

int ob_hit(object ob, object me, int damage)
{

	string msg, *limbs;
	int level;

	limbs = ob->query("limbs");
	level = me->query_skill("magic-sword", 1);

//        if( me->is_busy()) return 1;
	if( damage < 10 ) return 1;
	if (  random(level) > 50          )
	{
		msg = RED"$N���$n�Ĺ��ơ�����һ����ͻȻʩ��ħ��!!!��\n"NOR;
		message_vision(msg, me, ob);
		if ( random(2) == 0 && random(level) > 160)
		{
			msg = YEL"�� �ؾ�����! ����$NͻȻ����,����һ��ħ����$n�о��������ס���ܶ���!!��\n"NOR;
//             if (!ob->is_busy())
			if (userp(ob) && ob->query("qi") > 50
			        && ob->query("eff_qi") > 50)
			{
				ob->start_busy(3+random(2));
				if (ob->query("qi")/12 > 20)
					ob->add("qi",-ob->query("qi")/12);
				if (ob->query("eff_qi")/12 > 20)
					ob->add("eff_qi",-ob->query("eff_qi")/12);
			}
			else
			{
				ob->start_busy(3);
				ob->add("qi",-100);
				ob->add("eff_qi",-100);
			}
			msg += damage_msg(damage, "����");
		}
		else  if (random(2)==1&& random(level) > 160)
		{
			msg = HIR"��������!����$NͻȻ����,����һ��ħ����$n��һ�����������!!\n"NOR;
			if (userp(ob) && ob->query("qi") > 50
			        && ob->query("eff_qi") > 50)
			{
				if (ob->query("qi")/12> 20)
					ob->add("qi",-ob->query("qi")/12);
				if (ob->query("eff_qi")/12 > 20)
					ob->add("eff_qi",-ob->query("eff_qi")/12);
			}
			else
			{
				ob->add("qi",-200);
				ob->add("eff_qi",-200);
			}
			msg += damage_msg(damage, "����");
		}
		else  if (random(2)==2&& random(level) > 150)
		{
			msg = HIC"����������!����$NͻȻ����,����һ��ħ����$n��һ�����������!!\n"NOR;
			if (userp(ob) && ob->query("qi") > 50
			        && ob->query("jing") > 50 && ob->query("eff_qi") > 50
			        && ob->query("eff_jing") > 50)
			{
				if (ob->query("qi")/12 > 20)
					ob->add("qi",-ob->query("qi")/12);
				if (ob->query("eff_qi")/12 > 20)
					ob->add("eff_qi",-ob->query("eff_qi")/12);
				if (ob->query("jing")/12 > 20)
					ob->add("jing",-ob->query("jing")/12);
				if (ob->query("eff_jing")/12 > 20)
					ob->add("eff_jing",-ob->query("eff_jing")/12);
			}
			else
			{
				ob->add("qi",-1000);
				ob->add("eff_qi",-1000);
				ob->add("jing",-1000);
				ob->add("eff_jing",-1000);
			}
			msg += damage_msg(damage, "����");
		}
		else
			msg = HIG"$n���ȳ��У�ʹ$N������ʧ����!��\n"NOR;
		message_vision(msg, me, ob);
		return damage;
	}
}