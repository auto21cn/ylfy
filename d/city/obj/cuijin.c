//wuchangdan.c
#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIR"摧精魔丹"NOR, ({"cuijing dan", "dan"}));
	if ( clonep() )
		set_default_object(__FILE__);
	else 
	{
		set("unit", "颗");
		set("long", "这是一颗晶莹火红的摧精魔丹，那是害人之物!\n");
		set("value", 500000);
	}
	setup();
}

int do_eat(string arg)
{
	object me = this_player();
	
	if ( !id(arg) )
		return notify_fail("你要吃什么？\n");
	/*if (me->query("age") > 14)
		return notify_fail("这么大了还想吃这个不好吧？\n");*/
	if ( me->query("max_jingli") < 1000 )
		message_vision(HIR"$N吃下一颗摧精魔丹半天没有反应，似乎没有起到任何作用。\n"NOR,me);
	else 
	{
		me->add("max_jingli", -1000);
		message_vision(HIR"$N吃下一颗摧精魔丹，顿时全身精力大损！\n"NOR,me);
	}
	destruct(this_object());
	return 1;
}

