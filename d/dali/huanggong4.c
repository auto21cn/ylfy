// Room: /d/dali/huanggong4.c
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月18日，北京时间：21时27分26秒。

inherit ROOM;

void create()
{
	set("short", "[1;33m正德殿[2;37;0m");
	set("long", @LONG
这里是承德殿前的一个大殿，这里是给大臣上朝时休息用的。现在
已经散朝了，只有几个卫士在殿上执勤。经过前面的正殿，就到了皇宫
的中心承德殿。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "southdown" : __DIR__"huanggong3",
  "north" : __DIR__"huanggong5",
]));
                 set("objects", ([
                __DIR__"npc/shiwei" : 2,
        ]));


	setup();
}

