// Room: /d/dali/huanggong14.c
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月18日，北京时间：21时27分26秒。

inherit ROOM;

void create()
{
	set("short", "[1;33m寝宫[2;37;0m");
	set("long", @LONG
这里是皇帝的寝宫。室内一只香炉里熏着一束檀香，整个室内
香烟缭绕，让人昏昏欲睡。龙床上纱帐轻垂，锦被收拾得纤尘不染。
几个太监和宫女正不停地收拾房间。
LONG
	);
	set("outdoors", "dali");
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"huanggong13",
]));

                 set("objects", ([
                __DIR__"npc/gongnu" : 2,

                __DIR__"npc/taijian" : 2,
        ]));

         
	setup();
}

