// 儒风套装：披风

#include <armor.h>
#include <ansi.h>
#define ITEM_LEVEL 1

inherit SURCOAT;
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
		set("armor_prop/"+item[i], ITEM_LEVEL * 100);  // 设置常规属性
	}
	set_name(HIR"儒风披风"NOR, ({ "qinfeng pifeng","pifeng", "surcoat" }) );
	set("long", "这是一件做工非常精细的披风，属于传说中的儒风套装中的一件。\n");
	set_weight(300 + (random(max) * 100) + (random(ITEM_LEVEL) * 100));
	set("value", 5000000 + (random(max + ITEM_LEVEL) * 1000000));
	set("armor_prop/level", ITEM_LEVEL);	
	set("material", "steel");
	set("owner_id",1);
	set("xyzx_save_item", 1);
	set("xyzx_sys/bind_type", 0);
	set("xyzx_item/pinji", 1);
	set("unit", "件");
	set("icon", "10080");
 //---------------------------------------------------------------
              //套装参数
    set("suit",HIR"儒风套装"NOR);  //套装名称
    set("suit_lvl", 1);             //套装等级
    set("suit_count",10);           //套装部件数量
              //套装各部件
    set("suit_mod/armor","儒风铠甲");
    set("suit_mod/boots","儒风长靴");
    set("suit_mod/pants","儒风长裤");
    set("suit_mod/hand","儒风护手");
    set("suit_mod/head","儒风头盔");
    set("suit_mod/neck","儒风项链");
    set("suit_mod/cloth","儒风长衫");
    set("suit_mod/ring","儒风戒指");
    set("suit_mod/shield","儒风盾牌");
    set("suit_mod/surcoat","儒风披风");
    set("suit_mod/waist","儒风腰带");
	set("suit_mod/wrists","儒风护腕");
	//套装全部附加天赋效果  
    set("suit_eff/dexerity", 20000); 
    set("suit_eff/intelligence", 60000);  
    set("suit_eff/constitution", 60000);  
    set("suit_eff/strength", 20000); 
    //套装全部附加技能效果     
    set("suit_eff_skill/literate", 3000);  
	set("suit_eff_skill/dodge", 5000);
	set("suit_eff_skill/parry", 5000);
	set("suit_eff_skill/force", 5000);
                
 //---------------------------------------------------------------
	setup(1);
}
