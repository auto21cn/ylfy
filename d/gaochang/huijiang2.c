// Room: /d/xingxiu/xxroad7.c
inherit ROOM;
void create()
{
        set("short", "帕米尔草原");
        set("long", @LONG
这里已是南疆了。独特的地势和气候, 竟形成了南疆难得一见的小片草
原。因天山挡住了北方寒风, 这儿物产丰富, 聚居了不少哈萨克族人。波斯
商人也常来此地贩卖土产。
LONG
        );
        set("exits", ([
            "northup" : __DIR__"huijiang1",
			"southwest" : "/d/xingxiu/luzhou",
            "southdown" : __DIR__"huijiang3",
            "eastdown" : __DIR__"huijiang5",
        ]));
        set("objects", ([
                __DIR__"npc/hasake"  : 1,
                __DIR__"npc/yang"  : 3,
        ]) );
        set("no_clean_up", 0);
        set("outdoors", "xingxiuhai");
        setup();
        replace_program(ROOM);
}
