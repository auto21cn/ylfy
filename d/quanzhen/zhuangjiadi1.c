// zhuangjiadi1.c 庄稼地

inherit ROOM;

void create()
{
        set("short", "庄稼地");
        set("long", @LONG
一块绿油油的麦田。田中半人高的麦杆儿随风而动，正如江湖中的
你，随著江湖之中汹涌的波涛，四处飘摇。你想到江湖中的无奈,
不仅沧然泪下。 
LONG
        );
        set("outdoors", "quanzhen");
         set("no_drop", 1);

        set("exits", ([
                "east" : "/d/village/square",
                "north" : __DIR__"zhuangjiadi2",
//             "west" : __DIR__"zhuangjiadi1",
             "south" : __DIR__"zhuangjiadi2",
        ]));
        setup();
        replace_program(ROOM);
}

