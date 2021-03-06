// chaos-steps.c

inherit SKILL;

string *dodge_msg = (
{
	"$n一招「天玑离枢」，身子掣忽一转，$N只觉的眼前一花，失去了目标。\n",
	"只见$n身影一晃，一式「天璇乱步」早已避在七尺之外。\n",
	"$n使出「倒转天权」，身体急转，化为一道白光，虚幻不定的出现在$N的周围。\n",
	"$n左足一点，一招「逐影天枢」腾空而起，避了开去。\n",
	"可是$n使一招「风动玉衡」，身子轻轻向上纵起，飘了开去。\n",
	"$n身影微动，已经藉一招「开阳薄雾」轻轻闪过。\n",
	"但是$n一招「瑶光音迟」使出，早已绕到$N身後！\n"
});

int valid_enable(string usage)
{
	return (usage=="dodge") || (usage=="move");
}

int valid_learn(object me)
{
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力不够，没有办法练全真身法。\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 30
	        ||	(int)me->query("neili") < 3 )
		return notify_fail("你的气或内力不够，不能练倒乱七星步法。\n");
	me->receive_damage("qi", 30);
//	me->add("neili", -3);
	return 1;
}
