// Room: /d/city2/yihongyu.c
// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
	set("short", "怡红院");
	set("long", @LONG
你一走进来，一眼就看到大厅的墙上挂着一幅幅春宫图(tu)，一下子就
明白了这是什么地方。厅内到处张灯结彩，香气扑鼻。几名打扮得妖里妖气
的女人分站两旁对你发出媚笑。一个老鸨婆连忙上前招呼客人。从楼上传来
了阵阵打情骂俏的声音。
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/laobaopo" : 1,
]));
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"dongcha2",
]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
