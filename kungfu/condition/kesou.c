//咳嗽
//modified by wind

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( duration < 1 ) return 0;
   if( !living(me) ) {
      message("vision", me->name() + "痛苦地哼了一声。\n", environment(me), me);
   }
   else {
      tell_object(me, HIB "忽然一阵奇痒，你不由猛烈的咳嗽起来\n" NOR );
      message("vision", me->name() + "的身子突然一抖，整个人都被咳的缩成了一团。\n",
            environment(me), me);
   }
      me->receive_wound("qi",20);
      me->receive_wound("jing", 9);
      if(me->query("neili")>30)
              me->add("neili",-30);
      else
              me->set("neili",0);
      me->apply_condition("kesou", duration - 1);
      if ( (int)me->query_temp("powerup") ) 
         { me->add_temp("apply/attack", - (int)(me->query_skill("force")/3));
             me->add_temp("apply/dodge", - (int)(me->query_skill("force")/3));
             me->delete_temp("powerup");  }

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}
