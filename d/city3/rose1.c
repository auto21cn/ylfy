// This is a room made by roommaker.

inherit ROOM;

void create()
{
    set("short", HIY"玫瑰园"NOR);
    set("long", ""HIY"一阵淡淡的玫瑰清香扑面而来，你放眼一看“哇”这里\n"
      "种的全是玫瑰花。往西面还有一条被人踩出来的小路。几只\n"
    "美丽的花蝴蝶在花丛中翩翩飞舞。"NOR"\n");
        set("exits", ([
                "west" : __DIR__"rose2",
            ]));
     set("no_fight",1);
    setup();
    replace_program(ROOM);
}
