// cai by -wyz
inherit ITEM;
inherit F_FOOD;
void create()
{
        set_name( "蟹粉獅子頭" , ({"saddle"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "这是一碟香喷喷的淮揚名菜。\n" NOR);
                set("unit", "碟");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
        }
                set("eat_msg", "$N用银勺勺起一堆$n，放入口中,细嚼慢咽起来。\n");
}

