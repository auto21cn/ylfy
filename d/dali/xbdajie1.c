// Room: /d/dali/xbdajie1
// Data: ����˹(hades)
// Time: ��Ԫ��1999��4��21�գ�����ʱ�䣺17ʱ28��57�롣

inherit ROOM;

void create()
{
        set("short", "Ϧ��·");
        set("long", @LONG
����һ������ʯ�̳ɵĴ���������ϼ���һ����Ⱦ��ʮ�ֵĸɾ�����
˵ÿ��Ϧ�����µ�ʱ������ͻ����ڴ���ʯ�ķ��ն����ֹ�â�������
��������׳�ۡ������������˴Ҵҵ����ţ�����æ�Ÿ��Ե����飬һ����
�͵����գ�΢�紵����·�ߵ���������ʱҲҡҷ�������������˶���һ��
�����ˬ֮�⡣����򱱱������ţ�������[1;32m����[2;37;0m�����ߺ����Ǳ�ֱ�Ľ�
�������Ͼ��Ǵ�����[1;32m�����[2;37;0m�ˣ����·�ɣ�
LONG
        );
        set("outdoors", "dali");
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"xbdajie2",
  "west" : __DIR__"yamen",
  "east" : __DIR__"duan1",
  "south" : __DIR__"xidajie1",
]));

        setup();
}
