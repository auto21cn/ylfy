// cai by -wyz
inherit ITEM;
inherit F_FOOD;
void create()
{
        set_name(  "櫻橘蛤士蟆" , ({"clam"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "这是一碟香喷喷的安徽名菜。\n" NOR);
                set("unit", "碟");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
                set("eat_msg", "$N用筷子夹起一些$n，迷着眼睛慢慢的放入口中。\n");
        }
}

