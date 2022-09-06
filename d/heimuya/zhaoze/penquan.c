// Room: /d/heimuya/zhaoze/penquan.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "喷泉");
	set("long", @LONG
一条巨大的水柱从石孔中直喷上来，飞入半空，高达二丈有余，奔雪
溅玉，只见水柱在太阳照耀下映出一条眩目奇丽的彩虹。当此美景，纵有
百般赞美之意，却也不知说甚么话好。
LONG
);
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"shanbian",
  "west" : __DIR__"shandian",
]));
	set("outdoors", "penquan");

	setup();
	replace_program(ROOM);
}
