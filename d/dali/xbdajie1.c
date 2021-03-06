// Room: /d/dali/xbdajie1
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月21日，北京时间：17时28分57秒。

inherit ROOM;

void create()
{
        set("short", "夕照路");
        set("long", @LONG
这是一条大理石铺成的大道，街面上几乎一尘不染，十分的干净，据
说每当夕阳西下的时候，这里就会由于大理石的反照而出现光芒四射的美
景，甚是壮观。来来往往的人匆匆的走着，都在忙着各自的事情，一副祥
和的气氛，微风吹动着路边的柳树，顿时也摇曳多姿起来，让人顿生一种
心神俱爽之意。大道向北边延伸着，西边是[1;32m衙门[2;37;0m，东边好象还是笔直的街
道，向南就是大理的[1;32m西大街[2;37;0m了，快赶路吧！
LONG
        );
        set("outdoors", "dali");
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"xbdajie2",
  "west" : __DIR__"yamen",
  "east" : __DIR__"duan1",
  "south" : __DIR__"xidajie1",
]));

        setup();
}

