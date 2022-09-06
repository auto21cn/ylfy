// Room: /d/city3/shudao2.c
// This is a room made by roommaker. write by zhm/silversand.

inherit ROOM;

void create()
{
	set("short", "蜀道");
	set("long", @LONG
这是一条较难行的崎岖山道，周围都是峭壁，一不小心就会掉下去，尸骨无存，
难怪俗话说“蜀道之难，难于上青天”，你不得不小心翼翼地前进。
LONG
);
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"shudao3",
  "southeast" : __DIR__"shudao1",
]));

	setup();
	replace_program(ROOM);
}
