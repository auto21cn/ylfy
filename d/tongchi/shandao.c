inherit ROOM;
void create()
{
    set("short", "石阶");
    set("long", @LONG
石级到这里似乎变得宽阔了些。清新的山风扑面而来，令人
精神顿为一爽。远处传来淙淙水声，渐行渐远。山壁上挂满
了厚密的藤萝，随风轻轻摇弋。
LONG
    );
    set("objects", ([ /* sizeof() == 1 */
 ]));
    set("no_clean_up", 0);
    set("outdoors", "shaolin");
    set("exits", ([ /* sizeof() == 2 */
  "southdown" : "/d/xingxiu/jiayuguan",
  "northup" : __DIR__"shandao2",
]));
    setup();
    replace_program(ROOM);
}
