#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
		set("short", WHT"����ʯ��"NOR);
	set("long", WHT @LONG
 �������Ǽ�������ʯ�����ܲ�ͣ����ˮ����¡� 
LONG NOR);
	set("exits", ([
		"east" : __DIR__"dong93",
		"west" : __DIR__"dong01",
                	]));
         set("objects", ([
               __DIR__"npc/lev" : 1,
              __DIR__"npc/lev" : 1,
                ]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}