// Room: /d/emei/lingwenge.c 峨嵋派 灵文阁


inherit ROOM;


void create()
{
	 set("short","灵文阁");
      set("long",@LONG
这里是福寿庵的灵文阁，是主持静照师太传授佛法的地方。两名青衣小尼
随侍在旁，似乎在聆听师太的教晦。阁内布置简陋，靠墙放着几把竹椅，地上
放着几个蒲团。东首有一禅房。西面是一个斋厅。
LONG);

	set("exits", ([
               "west":__DIR__"fushouan",
		
	]));

	set("objects",([
		"d/emei/npc/girldizi" : 1,
	]));

	setup();
	replace_program(ROOM);
}
