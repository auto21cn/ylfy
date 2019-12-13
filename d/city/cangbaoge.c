// Room: /city/dangpu.c
// YZC 1995/12/04 
inherit ROOM;
void create()
{
	set("short", "藏宝阁");
	set("long", @LONG
	这是一家以卖各种极品宝物的商店，一个五尺高的柜台挡在你的面前，柜台
上摆着一个牌子(paizi)，柜台后坐着老板，一双精明的眼睛上上下下打量着你。
LONG
	);
	set("no_fight", 1);
	set("no_beg",1);
	set("item_desc", ([
		"paizi": @TEXT
    绑定石：可以把未绑定的装备，变成装备绑定，穿之后绑定ID。
    高级优化符：用来提升30级和30以上的装备，但是失败之后，装备会消失
    解绑符：可以用来解绑已绑定的装备，把它变成未绑定状态	
TEXT
	]) );
	set("objects", ([
		__DIR__"npc/shenmiren" : 1,
	]));
	set("exits", ([
		"down" : __DIR__"dangpu",
	]));
	setup();
	replace_program(ROOM);
}
