// cai by -wyz
inherit ITEM;
inherit F_FOOD;
void create()
{
        set_name( "蘭度鴿脯" , ({"bird"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "这是一碟香喷喷的粵菜。\n" NOR);
                set("unit", "碟");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
                set("eat_msg", "$N夹起一块$n，放入口中洗嚼起来,不仅赞不绝口。\n");
        }
}

