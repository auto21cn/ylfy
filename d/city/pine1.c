// Room: /d/city/pine1.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "大榕树上");
	set("long", @LONG
这里离地面已经有七、八丈高，如果不小心跌了下去，不断条腿也得去半
条命，榕树上结了许多球果，不过大部分都离树干很远，你够不到。
LONG
);

	setup();
	replace_program(ROOM);
}
