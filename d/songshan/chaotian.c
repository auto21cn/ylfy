// Room: /d/songshan/chaotian.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����˫���жϣ���Ȼ����һ���Ż�������ӶϾ����������������
���������������ǳ������ˡ�������ȥ�������ɽ��·�˵��ˣ�����
ɽ����ˬ���಻�á��������(jing)֮���ˡ�
LONG );
	set("item_desc", ([
		"jing" : "
    ��ɽ�������ϣ�����ï�ܣ�����Ũ����̶Ȫ����ɽ���������
ʯ���罣��ʯ���������࣬����̦����̺��Ϫˮ�������١���������֮
ʱ���˴��������ţ���ɫ����������ʪ����ˬ�ޱȡ���������ǳ���
�Ƽ��ڴ˾�ʤ�����ɽ֮����ɽ���±��ϣ�Ħ��������������ǣ���
���Ĺȡ�����Ǳ��̶������ϪϪ���䡱��������������ȡ��ִ��綷��
����עĿ���ഫ�Ϲ�ʱ������ʿ���ɲ���Ң�õ�λ�������ڴˡ����ɡ�
�����ڻ�ɽ���ӣ�����֮�࣬���������������
    ����Ԫ��Ԫ�꣬����������������ڻ�ɽ���������Ŀ���ڣ���
����ʱ������չ�������䤱�����֮������������������ʤ�أ���ϢƬ
�̣�������������֮�С���۲���������Ц���˴�Ի�����������ӣ�����
����������ÿ�����ģ��������˵������ı���ʳơ���������ʤ�ء���
    ʱ��÷���������ʫ�գ�
                  �������־����ģ�������մ�⸡��
                  ���������ŷ��ȣ�ϴ��Ϫ����ϸ����
                  ÿ�����������ף����޳��µ���ͷ��
                  ���ɳ�������ڣ�ǧ�Ż�ɽ�����
",
	]));
	set("exits", ([
		"northup"   : __DIR__"shandao6",
		"southdown" : __DIR__"shandao5",
	]));
	set("objects", ([
		__DIR__"npc/wan" : 1,
	]));
	set("outdoors", "songshan");
	set("no_clean_up", 0);
	set("coor/x", -20);
	set("coor/y", 830);
	set("coor/z", 60);
	setup();
	replace_program(ROOM);
}