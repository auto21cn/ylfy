// shulin3.c
#include <room.h>

inherit ROOM;

void create()
{ 
       set("short","树林");
       set("long", @LONG
这是一片偌大的树林，古木参天，遮晕蔽日，你进来就迷失了方向，
不知道现在自己身在何处，林中不时传来野兽的低吼,和怪异的啸叫令你
不禁毛骨悚然，只想早点离开。
LONG
     );

    
        set("exits", ([
                 "east" : __DIR__"shulin"+(random(10)+2),
                "south" : __DIR__"shulin"+(random(10)+2),
                "west" : __DIR__"shulin4",
                "north" : __DIR__"shulin2",        ]));             
        setup();
          replace_program(ROOM);
}


