//【百花掌】baihua-zhang.c
inherit SKILL;

mapping *action = ({
        ([      "action":               "$N浅浅一笑，一招「自在飞花轻似梦」若有若无地拍向$n的$l",
                "damage":150,
                "damage_type":  "瘀伤",
        ]),
        ([      "action":               "$N身形一顿，似有退意。$n正待反攻，\n忽见$N纤纤五指，直拂$n双目。正是“百花掌”之杀手「一枝红杏出墙来」",
                "damage":190,
                "damage_type":  "刺伤",
                        "weapon":               "右手掌",
        ]),
        ([      "action":               "只见$N嫣然一笑，双掌翻飞，一招「人面桃花相映红」当真是妙到毫巅",
                "damage":230,
                "damage_type":  "瘀伤",
        ]),
        ([      "action":               "$N纤腰一摆，陡然滑出数尺，右手顺势一招「黄菊枝头生晓寒」往$n的$l拍去",
                "damage":260,
                "damage_type":  "瘀伤",
        ]),
            ([  "action":               "只见$N双唇紧闭，面色凝重，一招「此花开尽更无花」全力击向$n的$l",
                "damage":400,
                "damage_type":  "瘀伤",
        ]),
});

int valid_learn(object me)
{
        if( (string)me->query("gender") != "女性" )
                return notify_fail("百花掌是只有女子才能练的武功。\n");
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail("练百花掌必须空手。\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("jing") < 30)
                return notify_fail("你的精神无法集中了，休息一下再练吧。\n");
        if( (int)me->query("qi") < 30 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");
        if( (int)me->query("neili") < 40 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 30);
        me->add("neili", -10);

        return 1;
}
