// yumi4.c
// marry 99 .8
inherit ROOM;

void create()
{
        set("short", "���׵�");
        set("long", @LONG
����һƬïʢ�����׵أ���������ײ�֪��ʲô����Ʒ�֣��������˶�ߣ���
�������ߣ���������·��
LONG
        );

       set("exits", ([
               "north" : __DIR__"yumi4",
               "south" : __DIR__"yumi2",
               "east" : __DIR__"tianye",
               "west" : __DIR__"yumi2",
       ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}