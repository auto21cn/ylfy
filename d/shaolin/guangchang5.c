// guangchang5.c
inherit ROOM;
void create()
{
    set("short", "�㳡");
    set("long", @LONG
����ǧ���ǰ��һ���㳡����������̨�׾��ǹ����������
��ǧ�������ǹ���ز��������ĵزص�����ǹ�����¹�
����ʿ�İ��µ����ÿ�궼�в�����;ۼ��ٰ�ˮ½�󷨻ᡣ
LONG
    );
    set("exits", ([
        "east" : __DIR__"bydian",
        "west" : __DIR__"dzdian",
        "south" : __DIR__"wuchang3",
        "northup" : __DIR__"qfdian",
        "southup" : __DIR__"dmyuan",
    ]));
    set("outdoors", "shaolin");	
    setup();
}
int valid_leave(object me, string dir)
{
    int skill;
    skill = me->query_skill("hunyuan-yiqi", 1);
    if (!wizardp(me) && skill < 80)
    {
        if (dir == "southup")
        {
            return notify_fail("�㼶�𲻹������ܽ����ĦԺ��\n");
        }
    }
    return ::valid_leave(me, dir);
}