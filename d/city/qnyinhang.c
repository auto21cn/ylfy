// Room: /city/dangpu.c
// YZC 1995/12/04 
inherit ROOM;
void create()
{
	set("short", "潜能银行");
	set("long", @LONG
	这是炎龙大陆唯一一家可以存放潜能的店铺，惊奇吧？潜能既然也有银行
可存。当然这都是老板“钱济世”的功劳，所以人如其名，闻名不如见面，他和
他那几个视钱如命的钱庄老板兄弟可不同，他可是抱着“济世为怀”的胸襟做生
意的，你看他正忙碌着认真招呼着各位光顾客人，旁边还特意竖了个大
牌子(paizi)，上面写着他的招牌字样。
LONG
	);
	set("no_fight", 1);
	set("no_beg",1);
	set("item_desc", ([
		"paizi": @TEXT
    本银行代人保管潜能，你们各位有需要的欢迎光顾，绝对分文不收
查询存有潜能点数(check)、储存潜能(cun)、取出潜能(qu)。	
TEXT
	]) );
	set("objects", ([
		__DIR__"npc/qianjs" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"shijian",
	]));
	setup();
	replace_program(ROOM);
}
