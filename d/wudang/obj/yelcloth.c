// yelcloth.c 白色道袍
// By wyz
#include <armor.h>
inherit CLOTH;
void create()
{
    set_name( YEL "黄色布袍" NOR, ({"pao"}) );
    set_weight(4500);
    if( clonep() )
       set_default_object(__FILE__);
    else {
        set("unit", "件");
        set("long", "这是件黄色布袍。\n");
        set("material", "cloth");
        set("armor_prop/armor", 3);
    }
    setup();
}

int query_autoload() { return 1; }