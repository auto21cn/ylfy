// dusongge.c 独松阁 

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "独松阁");
	set("long", @LONG
这里是独松阁，与宝泉同位于山腰。应阁中有一株千年古松而得
名。阁四周鸟语花香，景色如画，为览胜之佳地。往上是观音台。
LONG
	);
        set("outdoors", "quanzhen");

	set("exits", ([
		"west" : __DIR__"baoquan",
		"northup" : __DIR__"guanyintai",
        ]));
	setup();
	replace_program(ROOM);
}



