// Room: liehuoqi.c

inherit ROOM;

void create()
{
        set("short", "烈火旗");
        set("long", @LONG
这里是明教的烈火旗，许多教众在忙着把山下采集到的黑黝黝的
稠油提炼成火油，然后小心翼翼地装进一个个喷筒中。据说这就是最
厉害的火焰枪，只可惜稠油采集不易，所以一般不轻易使用。南面是
洪水旗，西边通向练武场。

LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"hongshuiqi",
  "west" : __DIR__"lianwu-chang2",
  "east" : __DIR__"shandao0",
]));
        set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/xinran" : 1,
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

