// Room: /d/shaolin/luohan5.c
// Date: YZC 96/01/19
inherit ROOM;
void create()
{
    set("short", "�޺����岿");
    set("long", @LONG
����һ�伫Ϊ��ª���������������ܣ����˼�������⣬��
�ڿյ����ر��������������İڷ��ż��������ҷ��ڵĻƲ�
���ţ���λ�뷢���׵���ɮ�������������Ŀ�붨�������Ǳ���
ʮ���޺��������еĵط������پ����书�����ڴ������һλС
ɳ����һ�ߴ���վ����
LONG
    );
    set("exits", ([
        "west" : __DIR__"wuchang2",
        "south" : __DIR__"luohan4",
        "north" : __DIR__"luohan6",
    ]));
    set("objects",([
        CLASS_D("shaolin") + "/xuan-ku" : 1,
        CLASS_D("shaolin") + "/cheng-jian" : 1,
        __DIR__"npc/xiao-ku" : 1
    ]));
    setup();
    replace_program(ROOM);
}