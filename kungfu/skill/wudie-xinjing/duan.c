#include <ansi.h>
 
inherit F_CLEAN_UP;
//inherit F_SSERVER;
 
int exert(object me)
{
        string msg;
        object weapon2, target;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("wudie-xinjing",1);

        if( !(me->is_fighting() ))
            return notify_fail("「蝶翼断金」只能对战斗中的对手使用。\n");

        if (!objectp(weapon2 = target->query_temp("weapon")) )
            return notify_fail("对方没有使用任何武器，你用不了「舞蝶心经」。\n");

        if( skill < 300)
                return notify_fail("你的「舞蝶心经」等级不够, 不能使用「蝶翼断金」！\n");

        if( me->query("neili") < 250 )
                return notify_fail("你的内力不够，无法运用「夺剑式」！\n");

        msg = HIY "$N微一凝神，运起「舞蝶心经」之「蝶翼断金」，一道金光射向$n。\n";
        message_vision(msg, me, target);
 
        damage = 1000 + random(skill * 2);
        ap = me->query_skill("sword",1) + skill;
        dp = target->query_skill("dodge",1);
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp )
        {
                if(userp(me))
                        me->add("neili",-10);
                msg = HIR"$n顿时觉得眼前一道金光闪过手中"NOR;
                msg += weapon2->name();
                msg += HIR"已经断成两节！\n" NOR;

                target->receive_damage("qi", damage);
                target->start_busy(2);
                weapon2->set("name","断掉的" + weapon2->query("name"));
                weapon2->set("id","trash " + weapon2->query("id"));
                weapon2->set("hit_trash",1);
                weapon2->move(environment(me));
        }
        else
        {
                if(userp(me))
                        me->add("neili",-10);
                msg = "可是$n看破了$N的剑路，立刻将手中" + weapon2->name() + "舞得风雨不透，使$N的「蝶翼断金」没有起到作用。\n"NOR;
                      }
        message_vision(msg, me, target);

        return 1;
}
