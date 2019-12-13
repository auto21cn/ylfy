// Room: /d/cxwxm/beiwu.c
// This is a room made by roommaker. write by Xyx.

inherit ROOM;

#include <ansi.h>
void create()
{
        set("short",HIC"北屋"NOR);
        set("long", 
"你一进屋便看到一排排兵器架整整齐齐的放在地上，上面有\n"
"各式的兵器。原来这里是痴心妄想门的兵器室。\n\n"
);
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"gc",
]));
        set("no_fight",1);
        set("objects", ([
        __DIR__"obj/axe" : 2,
        __DIR__"obj/whip" : 2,
        __DIR__"npc/xiaojin" : 1
        ]));

        setup();
}
/*
void init()
{
        object me;
        me = this_player();
        if (wizardp(me)) return 0;
        if (!me->query("jihao",1))
        {
        message_vision(HIC"突然,眼前出现了一大票的人，其中一个人指着$N大叫：\n"NOR
                    CYN"“我想起来了，就是他干的！”\n"NOR
                    HIR"立刻黑压压的一群人提着西瓜刀冲了过来，向$N一阵乱砍！\n"NOR,me);
                me->move("/d/cxwxm/tianye");
                me->unconcious();
        }
}  
*/