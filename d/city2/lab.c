// Room: /d/city2/lab.c
inherit ROOM;
void create()
{
	set("short", "实验室");
	set("long", @LONG
这里灯火通明，每天都有虫子在熬夜。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
"up" : __DIR__"tian_anm",	
]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
