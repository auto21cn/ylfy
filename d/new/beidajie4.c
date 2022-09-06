// Room: /new/beidajie4.c
inherit ROOM;
void create()
{
	set("short", "北大街");
	set("long", @LONG
	你走在练功场的大街上，看着操着南腔北调的各色江湖人物摩拳擦掌、
兴致高然，谈论着江湖上发生的奇文轨事，禁不住热血沸腾、意气高扬，暗自下
定决心要在江湖上好好作为一番，以光大门庭，宏扬本门至高绝学。
LONG
	);
	set("exits", ([
		"east" : __DIR__"liangong7",
		"south" : __DIR__"beidajie3",
		"west" : __DIR__"liangong8",
		"north" : __DIR__"beidajie5",
	]));
	
 setup();
 replace_program(ROOM);
}
