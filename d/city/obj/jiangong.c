//wuchangdan.c
#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIY"消攻忘情丹"NOR, ({"xiaogong dan", "dan"}));
	if ( clonep() )
		set_default_object(__FILE__);
	else 
	{
		set("unit", "颗");
		set("long", "这是一颗金黄色丹药，似乎可以消减攻击力，小心使用哦！\n");
		set("value", 10000000);
	}
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if ( !objectp(me) ) return 0;
	if ( !id(arg) ) return notify_fail("你要吃什么？\n");
	if ( me->query_temp("apply/damage") < -500000 )
		message_vision(HIY"$N吃下一颗消攻忘情丹半天没有反应，似乎没有起到任何作用。\n"NOR,me);
	else 
	{
		me->add_temp("apply/damage", -50000);
		message_vision(HIG"$N吃下一颗消攻忘情丹，似乎觉得攻击力有所下降！\n"NOR,me);
	}
	destruct(this_object());
	return 1;
}

