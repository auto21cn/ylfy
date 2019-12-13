
inherit ITEM;
#include <ansi.h>
void owner_is_killed() { destruct(this_object()); }   

void create()
{
        set_name(HIW"银矿石"NOR, ({"silver ore","ore","silver"}));
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long",HIW"这是一大块难得一见的银矿石，入手颇有些沉重，炼制后似乎可以用来锻造兵器。\n"NOR);
                set("value", 100);
                set("rate", 2); //设置材料等级
                set("can_make", "all");
                set("material_attrib", "silver");
                set("rigidity",90+random(30)); //设置材料硬度，也即武器硬度
                set("power_point", 90+random(30)); //做成后的jiali大小
              }
}
