// Room: /d/dali/huanggong6.c
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月18日，北京时间：21时27分26秒。

inherit ROOM;

void create()
{
	set("short", "[1;33m承德殿[2;37;0m");
	set("long", @LONG
这里就是大理国的金鸾宝殿，大理国中的朝政要事全是在这里
处理。殿内陈设华丽，镌镂龙凤飞镶之状，雄伟壮丽，金碧生辉。
正中朝南的龙椅上坐着大理国当今皇帝保定帝。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "southdown" : __DIR__"huanggong5",
]));

	setup();
}

