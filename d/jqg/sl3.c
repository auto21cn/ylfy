
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
����һ�����͵�ɽ·�����ɽ���Ѷ�ȥ��
LONG
	);

	set("exits", ([
                "northup" : __DIR__"dcy",
                "eastdown" : __DIR__"sl2",
	]));
 

        set("outdoors", "����");
	setup();
	replace_program(ROOM); 
}
