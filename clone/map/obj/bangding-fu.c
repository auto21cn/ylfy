//绑定符，绑定装备
#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

void create()
    {
    set_name( MAG"绑定符"NOR, ({"bangding fu"}));
	set_weight(5);
	set("long", "这是一张精灵族以魔力幻化而成的符纸，你可以把它粘贴(bang)在装备上绑定装备。\n" NOR);
	set("unit", "张");		
	set("value", 1);
	set("owner_id",1);
	set("xyzx_save_item", 1);
    set("value", 100000000);	
    setup();	
}

void init()
{
    if ( environment() == this_player() )
		add_action("do_bang", "bang");
}

int do_bang(string arg)
{
	object me, ob, obj;
	string str, item;

	me = this_player();
	ob = this_object();	
	if ( environment(ob) != me )
		return 0;
	
	if ( !arg )
		return notify_fail("你要用绑定符绑什么？\n");
	
	if ( sscanf(arg, "%s to %s", str, item) != 2 )
		return notify_fail("指令格式：bang 符纸英文名 to 装备英文名\n");
	
	if ( !objectp(ob = present(str, me)) || !function_exists("do_bang", ob) )
		return notify_fail("指令格式：bang 符纸英文名 to 装备英文名\n");
	
	if ( !objectp(obj = present(item, me)) && !objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这样东西。\n");
	
	if ( !obj->query("armor_prop/armor") && !obj->query("weapon_prop/damage") )
		return notify_fail("你只能用绑定符绑定武器或防具。\n");	
	
    if ( obj->query("equipped") )
      return notify_fail("你必须解除对这件物品的装备才能粘贴绑定符。\n");

    if ( obj->query("xyzx_sys/bind_type",1) && obj->query("xyzx_sys/bind_type",2) )
      return notify_fail("这件装备已经被绑定了，还绑定什么。\n");
  
	if ( obj->is_character() )
      return notify_fail("你要用绑定符绑什么？？\n");
	
	if ( obj->query("armor_prop/armor") || obj->query("weapon_prop/damage") && !obj->query("xyzx_sys/bind_type",1) && !obj->query("xyzx_sys/bind_type",2))
	{
	message_vision(HIM"$N把绑定符粘贴到" + obj->query("name") + HIM"上，" + obj->query("name") + HIM"被绑定了。\n"NOR, me);	
	obj->set("owner_id", 1);
	obj->set("xyzx_sys/bind_type", 1);
	obj->set("xyzx_save_item", 1);
	destruct(ob);
	return 1; 
	}	
}	  	  