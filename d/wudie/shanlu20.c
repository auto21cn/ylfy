// Room: /d/wudie/shanlu20.c
// This is a room made by roommaker. write by Xyx.

inherit ROOM;

void create()
{
        set("short", "ɽ��С·");
        set("long", @LONG
����������������ͷ�����Ƽ�ɽ�塣
LONG
);
        set("exits", ([ /* sizeof() == 2 */
  "southwest" : __DIR__"shanlu19",
  "northup" : __DIR__"shanlu21",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}