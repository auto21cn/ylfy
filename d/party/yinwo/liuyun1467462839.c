inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
��һ����֪����ʮ�־����ĸ��ݵ����������Ǵ���һ����Ц����Կ�������������ææµµ�Ĺ������ſڹ���һ����

LONG
);
	set("exits", ([
"west" : "/d/party/yinwo/beidajie2.c",
		]));
	
	set("objects", ([
		"/clone/room/npc/peilian" : 1,
       ]) );
	
	set("owner", "bigtie7001");
	set("banghui", "yinwo");
	
	setup();
}
