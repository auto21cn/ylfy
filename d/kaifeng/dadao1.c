// /kaifeng/dadao1.c
// Last modified by winder 2003.10.20

inherit ROOM;

void create()
{
	set ("short", "��·��");
	set ("long", @LONG
��·���˷�Ϊ��·��һ��·�򱱾��ǿ���ǣ��������������֡���
��������С���������������·ͨ��Ұ����,���ϱ�ͨ����ٹȡ�
LONG);

	set("outdoors", "kaifeng");
	set("exits", ([
		"north" : __DIR__"dadao0",
		"southwest" : __DIR__"dadao2",
		"south" : "d/wanjiegu/road4",
		"southeast" : __DIR__"shulin",
	]));
	set("objects", ([
         "quest/skills2/wunon/yu/yutan" : 2	,
	]));
	setup();
	replace_program(ROOM);
}