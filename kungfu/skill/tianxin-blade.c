//tianxin-blade  by:pipip
#include <ansi.h>
inherit SKILL;
int tydamage = this_player()->query("tydamage/blade")?this_player()->query("tydamage/blade"):this_player()->query_skill("tianxin-blade");

string type() { return "zhongji"; }
mapping *action = ({
([      "action" : "$N脚步轻浮，手中单刀斜挥，一式「"HIM"花开花落"NOR"」虚虚实实向$n攻出二十三刀",
        "force" : 660,
        "dodge" : 480,
        "parry" : 340,
        "damage" : tydamage,
        "skill_name" : "花开花落",
        "damage_type" : "内伤",
]),
([      "action" : "$N直冲向$n，接着身子一缩，竟然到了$n的身后，接着一记「"HIG"背车一刀"NOR"」向后砍去",
        "force" : 660,
        "dodge" : 480,
        "parry" : 340,
        "damage" : tydamage,
        "skill_name" : "背车一刀",
        "damage_type" : "内伤",
]),
([      "action" : "$N长身前扑，手中$w使一招「"HIB"风狂雨暴"NOR"」，只见一片刀光向$n罩下",
        "force" : 660,
        "dodge" : 480,
        "parry" : 340,
        "damage" : tydamage,
        "skill_name" : "风狂雨暴",
        "damage_type" : "内伤",
]),
([      "action" : "$N脚踩太虚，刀走偏锋，一手「"HIY"轻风微拂"NOR"」从下往上直取$n的喉咙"NOR,
        "force" : 660,
        "dodge" : 480,
        "parry" : 340,
        "damage" : tydamage,
        "lvl" : 1001,
        "skill_name" : "轻风微拂",
        "damage_type" : "劈伤",
]),
([      "action" : "$N急越上半空，使出「"HIB"星云直坠"NOR"」绝招，一连数十刀从天而降，将$n攻个错手不及"NOR,
        "force" : 660,
        "dodge" : 480,
        "parry" : 340,
        "damage" : tydamage,
        "lvl" : 1100,
        "skill_name" : "星云直坠",
        "damage_type" : "刺伤",
]),
([      "action" : "$N脚踩太白虚浮，身形如影，手中刀光忽隐忽现，$n一时不觉，$N手中刀光竟然已扑面而至"NOR,
        "force" : 660,
        "dodge" : 480,
        "parry" : 340,
        "damage" : tydamage,
        "lvl" : 1200,
        "skill_name" : "天马行空",
        "damage_type" : "内伤",
]),
});


int valid_enable(string usage) { return usage == "blade"; }
int valid_learn(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "blade")
    if (!objectp(weapon = me->query_temp("secondary_weapon"))
    || (string)weapon->query("skill_type") != "blade")
        return notify_fail("你还是先找把刀来吧。\n");
    if ((int)me->query("max_neili") < 20000)
        return notify_fail("你的内力不够。\n");
    if (me->query_skill("blade", 1)<=me->query_skill("tianxin-blade",1))
        return notify_fail("你的基础不够，无法领会更高深的技巧。\n");
       if ((int)me->query_skill("yijing-force", 1) < 100)
        return notify_fail("你的易经神功火候太浅。\n");

        if (me->query("family/master_id")!="wuming laoren")
        return notify_fail("天行刀法乃是无名老人的得意武功，你只能找他学习。\n");
    if ((int)me->query_skill("tianxin-blade",1) > 300)
        return notify_fail("这套刀法我就教此处，你今后在这套刀法上的成就就要看你自己了。\n");
     return 1;
}


mapping query_action(object me, object weapon)
{
        int i, level;
    level   = (int) me->query_skill("tianxin-blade",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
      object weap,weap1;
      weap = victim->query_temp("weapon");
      weap1 = me->query_temp("weapon");
      if( damage_bonus < 100 ) return 0;

           if( (me->query_skill("tianxin-blade") > 450) && (me->query("neili") > 10000)
       && (victim->query_temp("weapon")) 
       && random(10) > 7){
       message_vision(HIY "只见$N手中" + weap1->name() + ""HIY"如风火轮一般，一刀连着一刀将对方的" + weap->name() +""HIR"劈的火星直冒！\n" NOR, me ); 
       victim->start_busy(1);
       if ((me->query_skill("force")) > victim->query_skill("force") ){
       message_vision(HIR "\n潜运全身真劲全力一刀劈下，只听 乒! 的一声巨响，" + weap->name()
  + "被"+weap1->name()+""HIR"从$N"HIR"手中直劈成两段，$N"HIR"情急之下只好空手应战。\n" NOR, victim );
       weap->move(environment(me));
       weap->set("name", "断掉的"+ weap->query("name") );
       victim->reset_action();
       weap->set("value", 0);
       weap->set("weapon_prop", 0);
       weap->set("long", "一把断掉的武器，从中断开，破口整齐，看来是被绝顶高手一刀劈开的。\n");
       } else {
      message_vision(HIY "\n$N暗运卸字决，" + weap->name()
   + ""HIY"顺着方向快速旋转数下，将"+weap1->name()+""HIY"上的真劲全数卸去。\n" NOR, victim );
      victim->add("neili", -1000);
      }
      me->add("neili", - (20+random(30)));
      }
      if( me->query("neili") < 50000   ) return 0;
      if( random(10) < 2   ) return 0;

 //  第六等级的伤气
      if( me->query_skill("tianxin-blade",1)>4000
    && me->query_skill("yijing-force",1)>1500
  && me->query("zjb_dj/dj")>=25  ) {
              victim->receive_damage("qi", (damage_bonus ) * 2 , me);
return WHT "$N体内的易经神功的刚劲与刀招中发出的天行刀意融合为一，化做一股混元真力震碎了$n的心脉！！！\n" NOR;
  }      

 //  第五等级的伤气
      if( me->query_skill("tianxin-blade",1)>3000
    && me->query_skill("yijing-force",1)>1200
  && me->query("zjb_dj/dj")>=15 ) {
              victim->receive_damage("qi", damage_bonus  , me);
return YEL "$N的天行刀已到第五等级，一刀随意挥出,如生了眼睛一般扑向$n！！！！！\n" NOR;
  }      
      if( damage_bonus < 100 ) return 0;

 //  第四等级的伤气
      if( me->query_skill("tianxin-blade",1)>2000
    && me->query_skill("yijing-force",1)>1000
  && me->query("zjb_dj/dj")>=10 ) {
           victim->receive_damage("qi", (damage_bonus - 100)  , me);
return MAG "$N的天行刀已到第四等级，配合易经神功发出阵阵刀影罩住$n！！！！！\n" NOR;
  }  

 //  第3等级的伤气
        if( me->query_skill("tianxin-blade",1)>1000
       && me->query("zjb_dj/dj")>=4
    && me->query_skill("yijing-force",1)>1000
&& (me->query("neili")*3) > victim->query("max_neili") ) {
                victim->receive_damage("qi", (damage_bonus - 100) / 3 , me);
return CYN "$N的天行刀已入返璞归真境界，随意一招带出无数劲气扑向$n！！！！！\n" NOR;
  }  
 // 第二等级的伤气
        if ( me->query_skill("tianxin-blade",1)>200
         && me->query_skill("yijing-force",1)>200
  && me->query("zjb_dj/dj")>=2        ) {
             victim->receive_damage("qi", (damage_bonus - 100) / 8 , me);
return RED "$N暗暗运功将易经神功的柔劲混入天行刀法阴柔的刀气内攻向$n！！！\n" NOR;
}    
}

int practice_skill(object me)
{
    return notify_fail("天行刀法只能通过「"+HIC+"天马行空式"+NOR+"」来提升。\n");
}


string perform_action_file(string action)
{
        return __DIR__"tianxin-blade/" + action;
}


