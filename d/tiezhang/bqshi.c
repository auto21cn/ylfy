// Room: /u/zqb/tiezhang/bqshi.c

inherit ROOM;

void create()
{
	set("short", "兵器室");
	set("long", @LONG
    铁掌帮虽是以掌法、轻功著称，但帮中仍存有大量的兵器。以供武
功不够的帮众使用。屋内两侧排列的都是兵器架，上面刀、枪、剑、戟、斧
、钺、钩、叉应有尽有。
LONG	);
	set("exits", ([ /* sizeof() == 1 */
    "south" : __DIR__"zoulang-1",
            ]));
  set("objects", ([ /* sizeof() == 4 */
	        "/clone/weapon/gangdao" : 1,
	        "/clone/weapon/gangjian" : 1,
	        "/clone/weapon/gangzhang" : 1,
	        "/clone/weapon/changbian" : 1,
	        "/clone/weapon/hammer" : 3,
	                ]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
