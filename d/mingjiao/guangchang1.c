// Room: guangchang1.c

inherit ROOM;

void create()
{
        set("short", "演武场");
        set("long", @LONG
这是明教的演武场，教中武风极盛，每月总要进行演武大会，各
旗教众到时纷纷献技，比武切磋。以期能得教中法王长老亲睐，收为
门徒。是日人头簇拥、热闹非凡，景况甚为壮观。东西各为练武场。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/mingjiaodizi" : 3,
]));
        set("outdoors", "none");
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"shiwangdian",
  "west" : __DIR__"lianwu-chang4",
  "south" : __DIR__"houtuqi",
  "east" : __DIR__"lianwu-chang2",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

