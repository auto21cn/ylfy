// Room: /d/shaolin/zoulang5.c
// Date: YZC 96/01/19
inherit ROOM;
void create()
{
    set("short", "����");
    set("long", @LONG
�������������ȡ������ϲ�ķ�����������ĸ�ǽ����һ��
��ռ��ڼ���ϸϸ��ʯ���ϣ����������ϣ�������һ��Ƭ���֣�
ܰ����������Ӱҡҷ��ʫ�������ͷ������һ����Ȥ��
LONG
    );
    set("exits", ([
        "east" : __DIR__"zoulang6",
        "north" : __DIR__"zhulin4",
        "southdown" : __DIR__"banruo9",
    ]));
    setup();
    replace_program(ROOM);
}