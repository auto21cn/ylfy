// xiangfang1.c 厢房

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "厢房");
	set("long", @LONG
你站在一间不大的厢房中，房间打扫的很干净。靠左墙是一排书架，摆着百
十部经籍，三书五典，琳琅满目。书架前，是一张书案，文房四宝琴鼎具备。室
的右侧，有一张矮床，床上放着一个以狼尾草编成的蒲团。
LONG
	);
        
	set("exits", ([
		"east" : __DIR__"neiyuan",
	   ]));
	setup();
	replace_program(ROOM);
}



