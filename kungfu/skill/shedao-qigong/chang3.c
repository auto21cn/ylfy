
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
    int neili,damage,damage2;
    if( !target ) target = offensive_target(me);
    if( !target
    ||  !target->is_character()
    ||  !me->is_fighting(target) )
        return notify_fail("唱仙法只能在战斗中使用。\n");
    if( (int)me->query_skill("shedao-qigong", 1) < 100 )
        return notify_fail("你的蛇岛奇功不够娴熟，不会使用唱仙法吼字决。\n");
    if (!me->visible(target))    return notify_fail("你看不到"+target->name()+"。\n");
    if( environment(me)->query("no_fight") )
        return notify_fail("在这里不能攻击他人。\n");
    if( (int)me->query("neili") < 500 )
        return notify_fail("你已经唱得精疲力竭,内力不够了。\n");
if( (int)me->query_temp("chang") >=-20  )                         	
        return notify_fail("你必须先唱起前奏，协调自己的音律。\n");
    me->delete_temp("chang");
neili = me->query("neili");         	
    me->add("neili", -(300+random(200)));
    me->receive_damage("qi", 10);
    me->start_busy(random(5));
    message_vision( HIY "$N深深地吸一囗气，忽然仰天长啸，高声狂叫：不死神龙，唯我不败！\n" NOR, me);
        if( neili/2 + random(neili/2) < (int)target->query("neili")/3 ) 
        return notify_fail("敌人的内力比你高出太多,伤不了！\n");
if(target->query_skill_mapped("force") == "yunu-xinjing") {    	
if( target->query_skill("yunu-xinjing",1)>=600 || (target->query_skill("yunu-xinjing",1)>300 && !((int)target->query("make_loves") || (int)target->query("couple/couple_id")) ) )
return notify_fail("你等邪魔歪道,岂能伤得了我玉门中人!");	
}
if(target->query_skill("shedao-qigong",1) > me->query_skill("shedao-qigong",1))
{
if(target->query_skill("shedao-qigong",1) >= 2500 && random(100)<50 ) return notify_fail(""+target->query("name")+"回身淡淡一笑,"+RANK_D->query_respect(me)+"既有如此雅兴,合奏一曲<笑傲江湖>如何?");      
else if(target->query_skill("shedao-qigong",1) >= 1500 && random(100)<15 ) return notify_fail(""+target->query("name")+"回身淡淡一笑,"+RANK_D->query_respect(me)+"既有如此雅兴,合奏一曲<笑傲江湖>如何?"); 
else if(random(100)<10 ) return notify_fail(""+target->query("name")+"回身淡淡一笑,"+RANK_D->query_respect(me)+"既有如此雅兴,合奏一曲<笑傲江湖>如何?");             	
}
        
damage = (neili - (int)target->query("neili"))/15;                
        if( damage > 0 ) {
             target->receive_damage("jing", 20);
       if(damage < target->query("max_qi")/2) damage2 = damage;
else damage2 = (me->query("max_neili")*target->query("max_qi"))/target->query("max_neili");
if (damage2 < 0) damage2 = 45000;
target->receive_damage("qi", random(damage2/30),me);            	
target->receive_wound("qi", random(damage2/30),me);     	
target->receive_wound("jing", damage,me);	
target->receive_damage("jing", damage,me);        	
        message_vision( HIR "$N只觉脑中一阵剧痛，金星乱冒，犹如有万条金龙在眼前舞动。\n" NOR, target);
        }
        else
        {
        message_vision( HIR "$N只觉脑中微痛，似乎受了一点轻伤。\n" NOR, target);
        target->receive_damage("jing", 10,me );
        target->receive_damage("qi", 10,me );
        target->receive_wound("qi", 10,me);
        }
        if( !target->is_killing(me) ) target->kill_ob(me);
        if( !me->is_killing(target->query("id")) ) me->fight_ob(target);
    return 1;
}
