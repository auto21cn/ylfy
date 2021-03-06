// shanjiao.c 终南山脚

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "终南山脚");
	set("long", @LONG
你的面前是一座林木繁茂的高山，几座山峰在云雾中隐约可见，
一条石阶向山上延伸，走着几个进香客。石壁上刻着“终南山”
三个大字，原来这就是天下闻名的全真教所在地终南山了。
LONG
	);
        set("outdoors", "quanzhen");

	set("exits", ([
		"east" : __DIR__"gangding",
		"northup" : __DIR__"shijie1",
	]));
	setup();
	replace_program(ROOM);
}
