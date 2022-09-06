// Room: /d/heimuya/zhaoze/shimao1.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "寺庙");
	set("long", @LONG
这庙宇看来虽小，里边却甚进深。走过一条青石铺的小径，又穿过一座竹
林，只觉绿荫森森，幽静无比，令人烦俗尽消。竹林中隐着三间石屋。
LONG
);
	set("exits", ([ /* sizeof() == 2 */
  "enter" : __DIR__"shimao2",
  "out" : __DIR__"shimao",
]));

	setup();
	replace_program(ROOM);
}
