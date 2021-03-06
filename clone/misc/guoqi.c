// /clone/misc/gift.c	
// 注意：礼物发放Add的调用格式务必使用 add(string prop, mixed data, 1)

#include <ansi.h>
#define GIFT_NAME "五星红旗"

inherit ITEM;

void create()
{
	set_name(HIR + GIFT_NAME + NOR, ({"wuxing hongqi", "hongqi"}));
	set_weight(200);
	if ( clonep() )
		set_default_object(__FILE__);
	else 
	{
		set("unit", "面");
		set("long", "一面五星红旗，可以拿来摇一摇(yao)。\n");
		set("value", 0);
		set("no_give", 1);
		set("no_get", 1);
		set("no_put", 1);
		set("no_drop", 1);
		set("no_sell", 1);
	}
	setup();
}

void init()
{
	add_action("do_yao", "yao");
}

int do_yao(string arg)
{
	object me;
	int i;

	me = this_player();
	
	if ( !id(arg) ) return notify_fail("你要摇什么？\n");
	if ( me->query("07_国庆") )                	
	{
		tell_object(me, HIY "你拿起五星红旗摇了摇，似乎并没有发生任何事。\n"NOR);	
		destruct(this_object());
		return 1;
	}
	
	tell_object(me,HIG "你拿起五星红旗摇了摇，突然旗面上发出一道金光笼罩在你身上，你感觉变得更强大了。\n" NOR);
	for ( i=0; i<20; i++ )
	{
		me->add("combat_exp", 5000000, 1);
	}
	// 删除上次派礼物生成的参数，增加本次参数，确保每位玩家只能用一次。
	me->delete("07_中秋");              	
	me->set("07_国庆", 1);              	
	destruct(this_object());
	return 1;
}

void owner_is_killed()
{ 
	destruct(this_object());
}