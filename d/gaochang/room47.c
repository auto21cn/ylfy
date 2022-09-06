// Room: /d/gaochang/room47.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "湖边");
	set("long", @LONG
只见湖边红花树下，坐着一个全身黄衣的少女，长发垂肩，正拿着一把梳子慢
慢梳理。她赤了双脚，脸上发上都是水珠。只见她舒雅自在的坐在湖边，明艳圣洁，
仪态不可方物，黄衣倒映水中，落花一瓣一瓣的掉在她头上、衣上、影子上。任尔
平时如何潇洒自如，此时竟呐呐的说不出话来。
LONG
);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"room48",
  "east" : __DIR__"room46",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/huoqingtong" : 1,
]));
	set("outdoors", "room47");
	set("no_new_clean_up", 0);

	setup();
	replace_program(ROOM);
}
