//����ɽ�ɡ�mhxy-yushu 2001/2
#include <room.h>
inherit HOCKSHOP;
void create ()
{
  set ("short","�����˵���");
  set ("long", @LONG

�ؽֵ��������š�����������,����������ƽ���ơ�������һ���߸ߵĹ�̨,
���̵��ϰ��վ�ڹ�̨����,����С�ۿ������Ŀ��ˡ������Ǵ���С·����
�̵�ǽ����һ����(bian)��
LONG);
  set("item_desc", ([ 
  "bian" : "
�����̲����ۺ�ͯ�����ۣ���ӭ�ݹˣ����Ա��ܡ�
�͹ٿ��������
    ������������������������������
    ��	����(sell)		��
    ��	����(buy) ��list�鿴��  ��
    ������������������������������
���ֻ��ͭǮ���������ƽ���Ʊһ��ͨ�á�
"]));
  set("objects", ([ /* sizeof() == 2 */
   __DIR__"npc/laoban" : 1,
 ]));
  set("exits", ([ 
     "east" : __DIR__"road2",
 ]));
 set("no_clean_up", 1);
set("no_fight",1);
 setup();
}
int clean_up()
{
      return 0;
}






