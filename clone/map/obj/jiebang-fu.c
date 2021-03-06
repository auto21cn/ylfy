//解绑符 解除装备绑定
#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

void create()
    {
    set_name( HIG"解绑符"NOR, ({"jiebang fu"}));
	set_weight(5);
	set("long",
		"这是一张精灵族以魔力幻化而成的魔法石，你可以把它粘贴(jie)在绑定装备，解除装备的绑定。\n" NOR);
	set("unit", "张");		
	set("value", 1);
	set("owner_id",1);
	set("xyzx_save_item", 1);
    set("value", 2000000000);	
    setup();	
}

void init()
{
    if ( environment() == this_player() )
		add_action("do_jie", "jie");
}

int do_jie(string arg)
{
	object me, ob, obj;
	string str, item;

	me = this_player();
	ob = this_object();	

	if ( environment(ob) != me )
		return 0;
	
	if ( sscanf(arg, "%s to %s", str, item) != 2 )
		return notify_fail("指令格式：jie 符纸英文名 to 装备英文名\n");
	
	if ( !objectp(ob = present(str, me)) || !function_exists("do_jie", ob) )
		return notify_fail("指令格式：jie 符纸英文名 to 装备英文名\n");
	
	if ( !objectp(obj = present(item, me)) && !objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这样东西。\n");
	
	if ( !obj->query("armor_prop/armor") && !obj->query("weapon_prop/damage") )
		return notify_fail("你只能用解绑符解绑武器或防具。\n");	
	
    if ( obj->query("equipped") )
      return notify_fail("你必须解除对这件物品的装备才能粘贴解绑符。\n");
  
    if ( !obj->query("xyzx_sys/bind_type", 2) && !obj->query("xyzx_sys/bind_type", 1))
      return notify_fail("这件装备已经解除绑定了，还解除什么。\n");
  
	if ( obj->is_character() )
      return notify_fail("你要用解绑符解绑什么？？\n");
	
	if ( obj->query("armor_prop/armor") || obj->query("weapon_prop/damage") && obj->query("xyzx_sys/bind_type", 1) && obj->query("xyzx_sys/bind_type", 2) )
	{
	message_vision(HIM"$N把解绑符粘贴到" + obj->query("name") + HIM"上，" + obj->query("name") + HIM"解除了绑定。\n"NOR, me);	
	obj->set("owner_id", 1);
	obj->delete("bind_master_level");
	obj->set("xyzx_sys/bind_type", 0);
	obj->set("xyzx_save_item", 1);
	destruct(ob);
	return 1; 
	}	
}	  	  