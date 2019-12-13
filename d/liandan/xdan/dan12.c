inherit ITEM;
#include <ansi.h>
void init()
{
        add_action("do_eat", "eat");
}
void create()
{
    set_name( HIY "仙丹" NOR, ({"xian dan","xian","dan"}));
        set("unit", "株");
        set("value", 0); 
    set("long", "一枚青黄色的丹药，发出淡淡的的黄光。\n");
        setup();
}
void add_age(object me)
{
    if (me!=environment()) return; 
    message_vision(HIG "过了一阵，$N头上冒出淡淡的紫气，又神采奕奕的站了起来。\n" NOR, me);
    if ( ( me->query("mud_age") / 86400) > 5 ){
    if ( ((int)me->query("mud_age") / 86400)  > 5 - me->query("age_modify") )
    me->add("age_modify",-1);
    else
    me->set("age_modify",-((int)me->query("mud_age") / 86400) + 5 );
    }
    me->set_temp("add_age",0);
    me->update_age();
    destruct(this_object());
}

int do_eat(string arg)
{
    object me;
    me = this_player();
    if (!id(arg))  return notify_fail("你要吃什么？\n");
    if ( me->query_temp("add_age"))  return notify_fail("你要吃什么？\n");
     
    message_vision(HIG "$N将仙丹嚼碎了咽到肚中，脸色突然转绿，一下跌倒在地！\n" NOR, me);
    tell_object(me,MAG "你腹中如同刀搅一般难受，痛的你在地下直打滚！\n\n" NOR);
    if (me->query("age")<20){
       tell_object(me,HIR"看来您的岁数还太小了,此丹对你无效。\n"NOR);
        destruct(this_object());
        return 1;
     }
     call_out("add_age",1,this_player());
     me->set_temp("add_age",1);
    return 1;
}
void reset(){ }

