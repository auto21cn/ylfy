inherit ROOM;
void create()
{
          set("short", "赌怪居");
        set("long", @LONG
通吃帮六怪之一赌怪段克输的住处，平时无所事事，最喜欢
赌，屋子四处都放着赌博的用具，每天都不赌不快。
LONG
        );
        set("exits", ([
                   "west" : __DIR__"yishi",
                   "north" : __DIR__"qinjv",
        ]));
        set("objects", ([
        "/d/tongchi/npc/duguai":1,
        ]));
        setup();
        replace_program(ROOM);
}
