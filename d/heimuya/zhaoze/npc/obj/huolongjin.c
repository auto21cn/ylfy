#include <weapon.h>
inherit ITEM;

void create()
{
        set_name("火龙筋", ({ "huolong jin", "jin" }) );
        set_weight(80000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "条");
                set("long", "这是一条火龙筋，看上去似乎十分坚韧。\n");
                set("value", 3);
                set("material", "leather");
        }
}

int query_autoload() { return 1; }