//by enter
// modified by wind

inherit ROOM;

void create()
{
        set("short", "侧房");
	set("long", @LONG
这里就是温家老大温方达平时起居生活的住处，由于他是
温家五老中最有生意头脑的人物，所以平时一般都没在家，在
外面打理生意去了。
LONG
	);
	set("exits", ([ 
            "east" : __DIR__"zoulang1",
            ]));
	setup();
	replace_program(ROOM);
}
