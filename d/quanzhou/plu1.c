// Room: /d/quanzhou/plu1.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "庭院");
	set("long", @LONG
用青竹搭成的篱笆，在海风的拂动下发出沙沙的声响，几只海鸥在篱笆上
小酣。白白的沙滩上横行着几只螃蟹，一张很别致的吊床绑在两颗椰树间，一
栋海边小屋出现在你眼前。
LONG
);

	setup();
	replace_program(ROOM);
}
