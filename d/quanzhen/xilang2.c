//xilang2.c 西厢走廊

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "西厢走廊");
	set("long", @LONG
你走在一条长长的走廊上。房顶一侧支在北面的南极殿上，另一侧则
与南边八仙殿的屋顶相连。走廊二边的墙上刻着的是老子的《道德经》，
往南是八仙殿，往北是南极殿。
LONG
	);

	set("exits", ([
		"southeast" : __DIR__"baxiandian",
             "north" : __DIR__"nanjidian",
	]));
	setup();
	replace_program(ROOM);
}
