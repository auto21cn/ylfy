// ruanwei jia
#include <armor.h>
#include <ansi.h>
inherit ARMOR;
void create()
{
    set_name(HIW "婚纱" NOR,({ "huen sha","sha", }) );
    set_weight(1000);
    if( clonep() )
        set_default_object(__FILE__);
    else
    {
        set("unit", "件");
            set("long", "一件经过名师剪裁的、轻飘飘的、雪白的婚纱。\n");
        set("material", "copper");
            set("value",20000);
            set("armor_prop/armor", 5);
                set("female_only", 1);
    }
    setup();
}

int query_autoload() { return 1; }