// Room: /d/cxwxm/huayuan.c
// marry 8,14
inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short",HIC"花园"NOR);
        set("long", 
"你的眼前出现了一个美丽的大花园，花园里种着五彩缤纷的花，花丛中\n"
"闪烁着许多倩影，那是本门的姐妹。花园中央有一个喷水池，一年四季水都\n"
"不断涌出，谁都不知道这水从何而来。花园的西北面就是本门的大院。\n\n" 
);
        set("outdoors","cxwxm");
        set("exits", ([ /* sizeof() == 1 */
  "northwest" : __DIR__"dayuan",
]));
        set("objects",([
                "/d/cxwxm/npc/nvdizi":2,
               "/d/cxwxm/npc/qian":1,
]));

        setup();
}
/*
void init()
{
        object me;
        me=this_player();
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
