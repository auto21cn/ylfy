// si-huochan.c

#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIW"死火蟾"NOR, ({"si huochan", "corpse"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 5000);
        }
        setup();
}

int do_eat(string arg)
{
       
        if (!id(arg))
        return notify_fail("你要吃什么？\n");
         {
               this_player()->add("max_neili", 5);
                 message_vision(HIY "$N吃下一只死火蟾，顿然间只觉一股的真气直冲顶门...\n" NOR, this_player());
         }

        destruct(this_object());
        return 1;
}

int query_autoload() { return 1; }
