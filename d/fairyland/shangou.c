
inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
ɽ��֮�µ�һ��Сɽ���������̲ݴ�����������ѩ����û�����С�������
Ϊ��������������������С�ݣ�����������ҩ��
LONG	);
	set("exits", ([
		"westup" : __DIR__"shanbi",
	]));
	set("objects",([
		__DIR__"npc/xueji" : 1,
                //MEDICINE_D("yaocao") : 3,
	]));

	set("outdoors", "���ش��");
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}