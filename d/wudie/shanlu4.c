// Room: /d/wudie/shanlu4.c
// This is a room made by roommaker. write by Xyx.

inherit ROOM;

void create()
{
        set("short", "山间小路");
        set("long", @LONG
小路上人烟很少，周围景色秀美，犹如人间仙景。
LONG
);
        set("exits", ([ /* sizeof() == 2 */
  "northdown" : __DIR__"shanlu5",
  "south" : __DIR__"shanlu3",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
