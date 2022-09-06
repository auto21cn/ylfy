// Room: /d/lingjiu/xianchou.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "仙愁门");
	set("long", @LONG
这里就快到缥缈峰绝顶了，越往上走，山势越高，缭绕在你身边的白
雾愈来愈浓，往南则是下山的路。沿着山道没走几步，在你眼前出现一个
石坊，上书『仙愁门』三个大字，概因上山之艰辛吧。
LONG
);
	set("objects", ([ /* sizeof() == 1 */
  "/d/mengpai/ljdizi" : 3,
]));
	set("outdoors", "lingjiu");
	set("exits", ([ /* sizeof() == 2 */
  "southdown" : __DIR__"jian",
  "eastup" : __DIR__"dadao1",
]));

	setup();
	replace_program(ROOM);
}
