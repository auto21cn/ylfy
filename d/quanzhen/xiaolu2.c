// xiaolu2.c 林间小径

inherit ROOM;

void create()
{
	set("short", "林间小径");
	set("long", @LONG
你走在一条小径上，两旁种满了竹子，修篁森森，绿荫满地，除了竹叶
声和鸟鸣声，听不到别的动静。
LONG
	);

	set("exits", ([
		"northup" : __DIR__"houshan",
		"south" : __DIR__"xiaolu1",
	]));
	
	set("outdoors", "quanzhen");

	setup();
	replace_program(ROOM);
}

