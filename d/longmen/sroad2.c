
inherit ROOM;
void create()
{
        set("short", "蜿蜒小路");
        set("long", @LONG
你走在蜿蜒的小路上，两边是稀硫的树林和连片的田野。一条条清澈
的小溪和路平行，溪流清澈见底，水流甚急。你很明显的可以听到水流的
哗哗做响声。一块一块的田野散发出诱人的泥土清香。
LONG );
        set("valid_startroom",1);
        set("outdoors","龙门");
        set("class","血河派");
        set("exits", ([
                "west"  : __DIR__"sroad1",
                "southeast"  : __DIR__"sroad3",
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}


