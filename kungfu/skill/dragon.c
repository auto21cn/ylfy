// dragon.c 龙之力量
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
        "可是$n一声狂吼，$N竟愣住了，不敢放手进攻。\n",
        "但是$n身子一闪，$N这一招扑了个空。\n",
        "$n腾空跃起，躲开了$N的这一招。\n",
        "$n也不躲闪，直冲$N而去，$N一看不妙只得收招退开。\n",
});

mapping *action = ({
([  "action":"$N身子一侧，尾巴忽然从身后甩出，扫向$n",
    "dodge" : 40,
    "damage": 600,
    "damage_type":  "瘀伤"
]),
([  "action":"$N猛然接近，张嘴就咬$n",
    "dodge" : 60,
    "damage": 300,
    "damage_type":  "瘀伤"
]),
([  "action":"$N右抓撑地，左抓直击$n面部",
    "dodge" : 50,
    "damage": 400,
    "damage_type":  "瘀伤"
]),
([  "action":"$N突然一跃，从空中直扑$n",
    "dodge" : 100,
    "damage": 600,
    "damage_type":  "瘀伤"
]),
([  "action":"$N身子前倾，以全身之力撞向$n",
    "dodge" : 40,
    "damage": 1000,
    "damage_type":  "瘀伤"
]),

});

int valid_enable(string usage) 
{ 
	return usage == "unarmed" ||  usage == "dodge" ||usage == "parry" ; 
}

mapping query_action(object me, object weapon)
{
return action[random(sizeof(action))];
}


int practice_skill(object me)
{
	return notify_fail("龙之力量无法通过练习来成长。\n");
}
int valid_learn(object me)
{
	 return 1; 
 }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
string perform_action_file(string action)
{
        return __DIR__"dragon/" + action;
}