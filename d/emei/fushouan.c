// Room: /d/emei/fushouan.c 峨嵋派 福寿庵

inherit ROOM;

void create()
{
	 set("short","福寿庵");
      set("long",@LONG
福寿庵在神水庵南，是一个名叫天性的僧人建造的。庵前有九曲渠、流杯
池，古人曾据在此饮酒流杯，观景赋诗，歌咏兴叹，不知夕日。庵旁有株大海
棠树，数百苍龄，高达十余丈。
LONG);

	set("exits", ([
		"northdown" : __DIR__"shenshuige",
		"east" : __DIR__"lingwenge",
	]));

	set("objects",([		
		"d/emei/npc/girldizi" : 1,
	]));
	
	setup();
	replace_program(ROOM);	
}
