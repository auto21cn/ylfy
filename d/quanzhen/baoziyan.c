// baoziyan.c 抱子岩 

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "抱子岩");
	set("long", @LONG
这里就是抱子岩,它的形状就象一位慈母抱着孩子，等待着丈夫的归
来。岩四周都是悬崖峭壁,眼前只有一条狭窄的山路通向山上。往上
是老妪岩。
LONG
	);
        set("outdoors", "quanzhen");

	set("exits", ([
	    "westup" : __DIR__"laoyuyan",
	    "southdown" : __DIR__"cuihuamiao",
        ]));
	setup();
	replace_program(ROOM);
}


