//wuchangdan.c
#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIR"а��"NOR, ({"xieshen dan", "dan"}));
	if ( clonep() )
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("long", "����һ�����ɫ���ƺ������������а����С��ʹ��Ŷ��\n");
		set("value", 10000000);
	}
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if ( !objectp(me) ) return 0;
	if ( !id(arg) ) return notify_fail("��Ҫ��ʲô��\n");
	if ( me->query("shen") < -2100000000 )
		message_vision(HIY"$N����һ��а�񵤰���û�з�Ӧ���ƺ�û�����κ����á�\n"NOR, me);
	else 
	{
		me->add("shen", -500000);
		message_vision(HIR"$N����һ��а�񵤣�����а�����أ�\n"NOR,me);
	}
	destruct(this_object());
	return 1;
}
