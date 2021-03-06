//guxing-sword.c 孤星剑法

inherit SKILL;
mapping *action = ({
([  "action" : "$N虚步提腰，一招「"+HIM+"寒星伴月"+NOR+"」，手中$w轻轻颤动，一剑剑点向$n的$l",
    "force" : 400,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([  "action" : "$N向前跨上一步，左手剑诀，右手$w使出一式「"+YEL+"星光瞬闪"+NOR+"」直刺$n的$l",
    "force" : 370,
    "lvl" : 10,
    "damage_type" : "刺伤"
]),
([  "action" : "$N身形往右一挫，左手剑诀，右手$w使出一式「"+WHT+"流星赶月"+NOR+"」刺向$n的$l",
    "force" : 380,
    "lvl" : 15,
    "damage_type" : "刺伤"
]),
([  "action" : "$N一招「"+HIW+"天刹孤星"+NOR+"」，$w自上而下划出一个大弧，平平地向$n的$l挥去",
    "force" : 330,
    "lvl" : 37,
    "damage_type" : "刺伤"
]),
([  "action" : "$N上身往左侧一拧，一招「"+BLK+"神龙摆尾"+NOR+"」，右手$w反手向$n的$l挥去",
    "force" : 410,
    "lvl" : 48,
    "damage_type" : "刺伤"
]),
([  "action" : "$N左腿提膝，手中$w斜指，一招「"+HIC+"翻山越岭"+NOR+"」刺向$n的$l",
    "force" : 430,
    "lvl" : 60,
    "damage_type" : "刺伤"
]),
([  "action" : "$N一招「"+CYN+"芙蓉出水"+NOR+"」，$w自下而上划出一个大弧，平平地挥向$n的$l",
    "force" : 140,
    "lvl" : 70,
    "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
int practice_level(){   return 145;  }
int valid_learn(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
    if (!objectp(weapon = me->query_temp("secondary_weapon"))
    || (string)weapon->query("skill_type") != "sword")
        return notify_fail("你必须先找把剑才能学孤星剑法。\n");

    if ((int)me->query("max_neili") < 100)
        return notify_fail("你的内力不够。\n");
    if (me->query_skill("sword", 1) <=me->query_skill("guxing-sword", 1))
        return notify_fail("你的基础不够，无法领会更高深的技巧。\n");
    return 1;
}
mapping query_action(object me, object weapon)
{
    mapping a_action;
    int i, level;
    level   = (int) me->query_skill("guxing-sword", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]){
                        a_action = action[NewRandom(i, 20, level/5)];
                        break;
                }
    a_action["dodge"]  = 0-level*3;
    a_action["parry"]  = 0-level*3;
    a_action["attack"]  = level*3;
    a_action["damage"] = level*3;
    return a_action;

}
int practice_skill(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
    if (!objectp(weapon = me->query_temp("secondary_weapon"))
    || (string)weapon->query("skill_type") != "sword")
        return notify_fail("你使用的武器不对。\n");
    if ((int)me->query("qi") < 50)
        return notify_fail("你的体力不够练孤星剑法。\n");
    me->receive_damage("qi", 30);
    return 1;
}
string perform_action_file(string action)
{
    return __DIR__"guxing-sword/" + action;
}
