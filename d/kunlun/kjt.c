// Room: /d/kunlun/kjt.c// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
	set("short", "观景台");
	set("long", @LONG
这里是昆仑绝顶，俯视四周，只见众山峰被雪覆盖着，白云围涌，十分壮
观，令人心旷神怡。
LONG
	);
    set("objects", ([ 
        CLASS_D("kunlun")+"/banshuxian"  : 1,
    ]));
	set("outdoors", "kjt");
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"dt",
]));

	setup();
	replace_program(ROOM);
}
