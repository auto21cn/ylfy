inherit ROOM;
 
void create()
{
        set("short", "�յ�");
        set("long",@LONG
����һƬ�յ�,���ܶ�����ʯ,�Ӳݴ�����������һ��С��.������
����Ĺ�ľ��.������һ�������Ĵ��,������һƬ��ƺ.
LONG);
        set("exits", ([
        "west" : __DIR__"caoping",
        "east" : __DIR__"road",
        "north" : __DIR__"xiaowu",
        "south" : __DIR__"lin2",
    ]) );
        set("objects", ([
        "/d/city2/npc/dizi": random(3),
    ]) );
        set("outdoors", "shenlong");
        setup();
    replace_program(ROOM);
}