// Room: /d/nanyang/yidao.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "大驿道");
	set("long", @LONG
你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的
行商，赶着大车的马夫，上京赶考的书生，熙熙攘攘，非常热闹。
不时还有两三骑快马从身边飞驰而过，扬起一路尘埃。马上的人
个个身着劲装，衣甲鲜明，有的还随身佩带着刀剑。看来都是些
些习武的江湖人。道路两旁是整整齐齐的杨树林。
LONG
);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"yidao1",
  "south" : "/d/village/hsroad1",
]));
	set("objects", ([ /* sizeof() == 1 */
  "/d/mengpai/kddizi" : 3,
]));

	setup();
	replace_program(ROOM);
}
