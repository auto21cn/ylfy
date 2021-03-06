// guangchang.c 广场
// by kyd

#include <ansi.h> 
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "全真教广场");
        set("long", @LONG
这是一个由大石板铺成的广场，周围种满了梧桐树，一到秋天就是满
地的落叶。几个年纪轻轻的道童正在打扫。北边是重阳宫玉皇殿。
LONG
        );
        set("outdoors", "quanzhen");

        set("exits", ([
                "southdown" : __DIR__"tyroad2",
                "north" : __DIR__"yuhuangdian",
                "west" : __DIR__"lwc1",
                "east" : __DIR__"bwc",
        ]));
        
        set("objects", ([
"/d/quanzhen/npc/zhaozhijing" : 1]));
        
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

        if ((!myfam || myfam["family_name"] != "全真教") && dir == "north" &&                 objectp(present("master zhao", environment(me))))
     return notify_fail(HIW"\n 赵志敬喝道：你不是全真弟子，要想过去先胜过我手中长剑! \n\n"NOR);
                
        return ::valid_leave(me, dir);
}


