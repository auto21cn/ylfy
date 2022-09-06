// shijie2.c 石阶

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "石阶");
	set("long", @LONG
你走在一条坚实的石阶上，不时地有进香客从你的身边走过。一边是峭壁，
一边是悬崖，抬头隐约可见笼罩在云雾中的山峰，听着流水淙淙，令人心
旷神怡。往上是太乙湖。
LONG
	);
        set("outdoors", "quanzhen");

	set("exits", ([
		"eastdown" : __DIR__"shijie1",
		"northup" : __DIR__"taiyihu",
	]));
	setup();
	replace_program(ROOM);
}
