#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
		set("short", BLU"ɽ��"NOR);
	set("long", BLU @LONG
 ��Խ��Խ���Χ��ǽ���ƺ���Щ�����ˡ� 
LONG NOR);
	set("exits", ([
		"north" : __DIR__"dong19",
		"south" : __DIR__"dong42",
                	]));
               set("objects", ([
               __DIR__"npc/lev" : 1,
              __DIR__"npc/lev" : 1,
                ]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}