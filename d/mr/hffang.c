#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short","���ʷ�");
         set ("long",@long
ʯ�ݺڶ�����, ֻ��һ���˱�����һ����������, ���������˶���, ����
������, ȴ˵�����������ٿ�����ʱ, ֻ��һ������������������������
��һ��ѩ���ĳ���, ����һ����ˮ, ���ֱð������
long);
         set("exits",([
         "east" : __DIR__"hhyuan",
         "west" : __DIR__"c13-3",
]));
         set("objects",([
             __DIR__"npc/yan" : 1,
]));
        setup();
        replace_program(ROOM);
}
