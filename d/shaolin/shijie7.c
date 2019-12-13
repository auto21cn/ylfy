// Room: /d/nanyang/shijie7.c
// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
    set("short", "石阶");
    set("long", @LONG
石级继续向上延伸，瀑布在脚下越来越小，水声也渐行远去
几位身着灰黄色僧衣的僧人擦肩而过，看他们下山的时後脚步沉
稳，好象是个会家子。往上远眺，似乎可以看到石檐一角。
LONG
    );
    set("no_clean_up", 0);
    set("outdoors", "shaolin");
    set("exits", ([ /* sizeof() == 2 */
  "southdown" : __DIR__"shijie6",
  "east" : __DIR__"shanmen",
]));
    setup();
    replace_program(ROOM);
}
