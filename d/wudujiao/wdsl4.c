// by mayue

inherit ROOM;

void create()
{
	set("short", "�嶾ɽ·");
	set("long", @LONG
�������嶾ɽ�е�ɽ��С·�����������������ϡ�ɽ·�ϼž�
������������һ˿���޵ĺۼ�����˳�ֲ�������·�е�֦������֦
��Ȼһ�������˻�ȥ������...����Ȼ��һ�����ƿ�֦�Ķ��ߡ� 
LONG
	);
        set("outdoors", "wudujiao");

	set("exits", ([
		"eastup" : __DIR__"wdsl5",
		"south" : __DIR__"baidu1",
		"westdown" : __DIR__"wdsl3",
		"north" : __DIR__"qiandu1",
	]));

	setup();
	replace_program(ROOM);
}
