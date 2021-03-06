// tanan.c

inherit ROOM;
#include <ansi.h>

void create()
{
    set("short", HIY"水潭岸边"NOR);
    set("long", @LONG
你站在一片山谷中的一处水潭(tan）岸边。游目四顾，只见繁花青草，便
如一个极大的花园。然而花影不动，幽谷无人，四下里十分安静。草地上一条
蜿蜒的小路直通向不远处一所茅屋。
LONG
        );
    set("item_desc", ([
          "tan":HIC"你举目向潭中望去，但见水潭里面水草晃动，几条不知名的白鱼游来游去。\n"NOR,      
          ]));

    set("outdoors", "古墓");

    set("objects", ([
                __DIR__"obj/shi3" : 1,
                __DIR__"obj/shi1" : 2,
        ]));
    set("exits", ([
          "north" : __DIR__"xiaolu",
    ]));        

    setup();

}

void init()
{
      add_action("do_tiao", "tiao");
       
}

int do_tiao(string arg)
{
        object me;

        me=this_player();
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if ( !arg || arg != "tan")
                return notify_fail("你要往哪跳？\n");
        message_vision(HIY"$N扑通一声，涌身跳入了水潭。\n"NOR, me);
        me->set("water", me->max_water_capacity()+200);
        me->move(__DIR__"tanmian");
        tell_room(environment(me), me->name() + "从岸边跳了下来。\n", ({ me }));
        return 1;
}

