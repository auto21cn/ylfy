
inherit SKILL;

mapping *action = (
{
([  "action": "$N˫��һ�Σ����е�$w��һ�����߰����$n��$l",
    "dodge": -20,
	"damage": 30,
    "damage_type":  "����"
	 ]),
([  "action": "$N����һ����$w�����̶����ƿ���ֱ��$n��$l",
    "dodge": -40,
	"damage": 30,
    "damage_type":  "����"
	 ]),
([  "action": "$N��ָ΢����$wбб�ķ���$n��$l",
    "dodge": -40,
    "damage_type":  "����"
	 ]),
([  "action": "$N�������⣬����һ˦�����е�$w����һ����������$n��$l",
	"dodge": 20,
	"damage": 1000,
    "damage_type":  "����"
	 ]),
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_neili") < 150000 )
		return notify_fail("�������������û�а취���ɵ�������\n");


	if( !(ob = me->query_temp("weapon"))
	        ||      (string)ob->query("skill_type") != "throwing" )
		return notify_fail("���������һЩ�����������ɵ���\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="throwing" ;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("jing") < 30 || (int)me->query("neili") < 500 )
		return notify_fail("�����������������û�а취��ϰ�ɵ�������\n");
	me->receive_damage("jing", 30);
	me->add("neili", -300);
	write("�㰴����ѧ����һ��ɵ�������\n");
	return 1;
}

string perform_action_file(string action)
{
	return  __DIR__"feidao/" + action;
}

int effective_level()
{
	return 15;
}

int learn_bonus()
{
	return -2220;
}
int practice_bonus()
{
	return -1110;
}
int black_white_ness()
{
	return 15;
}
