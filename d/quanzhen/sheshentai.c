// sheshentai.c 舍身台

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "舍身台");
	set("long", @LONG
眼前是个极大的圆坪，四周群山环抱，往下有座大池，水波映月，银光
闪闪。池四周种着几株杨柳树，倒映在水中。西边山侧有几十幢房舍，有几
座构筑特别宏伟，那就是全真教的所在地。
LONG
	);
        set("outdoors", "quanzhen");

	set("exits", ([
		"eastdown" : __DIR__"chexiangtan",
		"westdown" : __DIR__"yuqingchi",
        ]));
	setup();
	replace_program(ROOM);
}



