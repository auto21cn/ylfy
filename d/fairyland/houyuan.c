
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIG"��Ժ"NOR);
	set("long", @LONG
������ɽׯ�ĺ�Ժ����ׯ�ųơ���÷�����������Դ��Ժ����ͳ�������
÷����ÿ�괺��÷��ʢ��֮ʱ������һƬ��죬����������÷��Ʈ���������
�Ŀ������������ǡ����Ṭ����
LONG	);
	set("exits", ([
                "north" : __DIR__"lggong",
		"west" : __DIR__"dating",
	]));
	set("outdoors", "����ɽ");
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}