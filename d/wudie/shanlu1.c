// Room: /d/wudie/shanlu1.c
// This is a room made by roommaker. write by Xyx.

inherit ROOM;

void create()
{
        set("short", "山间小路");
        set("long", @LONG
小路上人烟很少，周围景色秀美，犹如人间仙景。
LONG
);
        set("no_clean_up", 0);
     set("exits", ([ /* sizeof() == 3 */
"northup" : __DIR__"shanlu2",
]));

        setup();
        replace_program(ROOM);
}
