// lifeheal.c（疗伤）

#include <ansi.h>

int exert(object me, object target)
{
    if( me->is_fighting() )
        return notify_fail("战斗中运功疗伤？找死吗？\n");

   if( !target )
      return notify_fail("你要用真气为谁疗伤？\n");
 
   if( (int)me->query("max_neili") < 240 )
      return notify_fail("你的内力修为不够。\n");

   if( (int)me->query("neili") < 120 )
      return notify_fail("你的真气不够。\n");

   if( (int)target->query("eff_qi") == (int)target->query("max_qi") )
      {
         if ( me == target )
            return notify_fail("你现在没有受任何伤。\n");
         return notify_fail( target->name() + "现在没有受任何伤。\n");
      }

   if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 5 )
      return notify_fail( target->name() + "已经受伤过重，经受不起你的真气震荡！\n");

      message_vision( MAG"$N坐了下来运起内功，将手掌贴在$n背心，缓缓地将真气输入$n体内....\n"
"过了不久，$N额头上冒出豆大的汗珠，$n吐出一口瘀血，脸色看起来红润多了。\n" NOR, me, target );

   target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
   target->add("qi", 10 + (int)me->query_skill("force")/3 );
   if( (int)target->query("qi") > (int)target->query("eff_qi") )
target->set("qi", (int)target->query("eff_qi"));

   me->add("neili", -120);
   me->add("combat_exp",1);
    if( (int)me->query("mud_age")>86400) me->start_busy(2+random(1));

   return 1;
}

