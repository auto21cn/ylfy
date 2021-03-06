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
      tell_object(me, HIB "你感到全身忽冷忽热，经脉疼痛欲裂，看来是玄冰碧火毒发作了！" NOR );
      message("vision", me->name() + "的身子突然晃了两晃，脸色忽青忽白起来。\n",
            environment(me), me);
   }
      me->receive_wound("qi",25000 + random(100));
      me->receive_wound("jing", 25000);
      me->apply_condition("binghuo", duration - 1);
      if ( (int)me->query_temp("powerup") ) 
         { me->add_temp("apply/attack", - (int)(me->query_skill("force")/3));
             me->add_temp("apply/dodge", - (int)(me->query_skill("force")/3));
             me->delete_temp("powerup");  }

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

