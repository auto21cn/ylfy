// Room: /d/dali/huanggong13.c
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月18日，北京时间：21时27分26秒。

inherit ROOM;

void create()
{
	set("short", "[1;33m勤政殿[2;37;0m");
	set("long", @LONG
勤政殿是保定帝的寝宫所在地，殿内珠帘低垂，红烛高照，几
个宫装少女正在收拾房间。穿过大殿，后进就是几间小殿，那就是
皇帝休息的地方了。
LONG
	);
	set("outdoors", "dali");
	set("exits", ([ /* sizeof() == 3 */
  "east" : __DIR__"huanggong11",
  "southdown" : __DIR__"huanggong15",
  "west" : __DIR__"huanggong14",
]));

	setup();
}

