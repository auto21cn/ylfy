#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"石洞"NOR);
	set("long", CYN @LONG
这是一个黑漆漆石洞，周围都是坚硬的石壁。 
LONG NOR);
	set("exits", ([
		"east" : __DIR__"dong05",
		"south" : __DIR__"dong24",
                	]));
 set("objects", ([
               __DIR__"npc/lev" : 1,
                            ]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
