// 朔雪套装：护手

#include <armor.h>
#include <ansi.h>
#define ITEM_LEVEL 1

inherit HANDS;
inherit F_ITEM_MAKE;
//#include <item_sx.h>

void create()
{
	string *item;
	int i, max;

	item = keys(armor_shuxing);
	max = sizeof(item);
	for ( i=0; i < max; i++ )
	{
		set("armor_prop/"+item[i], ITEM_LEVEL * 100);   // 设置常规属性
	}
	set_name(HIB"朔雪护手"NOR, ({ "shuoxue shou","hushou", "hands" }) );
	set("long", "这是一双做工非常精细的护腕，属于传说中的朔雪套装中的一件。\n");
	set_weight(300 + (random(max) * 100) + (random(ITEM_LEVEL) * 100));
	set("value", 5000000 + (random(max + ITEM_LEVEL) * 1000000));
	set("armor_prop/level", ITEM_LEVEL);	
	set("material", "steel");
	set("xyzx_item/pinji", 1);
	set("owner_id",1);
	set("max_level", 30);
	set("xyzx_save_item", 1);
	set("xyzx_sys/bind_type", 0);
	set("unit", "双");
	set("icon", "10072");
 //---------------------------------------------------------------
              //套装参数
    set("suit",HIB"朔雪套装"NOR);  //套装名称
    set("suit_lvl", 1);             //套装等级
    set("suit_count",10);           //套装部件数量
              //套装各部件
    set("suit_mod/armor","朔雪铠甲");
    set("suit_mod/boots","朔雪长靴");
    set("suit_mod/pants","朔雪长裤");
    set("suit_mod/hand","朔雪护手");
    set("suit_mod/head","朔雪头盔");
    set("suit_mod/neck","朔雪项链");
    set("suit_mod/cloth","朔雪长衫");
    set("suit_mod/ring","朔雪戒指");
    set("suit_mod/shield","朔雪盾牌");
    set("suit_mod/surcoat","朔雪披风");
    set("suit_mod/waist","朔雪腰带");
	set("suit_mod/wrists","朔雪护腕");
	//套装全部附加天赋效果  
    set("suit_eff/dexerity", 20000);      
    set("suit_eff/intelligence", 20000);  
    set("suit_eff/constitution", 60000);    
    set("suit_eff/strength", 20000);   
    //套装全部附加技能效果     
    set("suit_eff_skill/huagong-dafa", 1000);
    set("suit_eff_skill/beiming-shengong", 1000);
	set("suit_eff_skill/xixing-dafa", 1000);
	
 //---------------------------------------------------------------
	setup(1);
}
