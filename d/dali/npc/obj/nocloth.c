// cloth.c
//
// This is the basic equip for players just login.
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIR "带血纱衣" NOR, ({ "shayi" }) ); 
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "一件薄带血的纱衣\n");
                set("material", "cloth");
                set("value", 100);
                set("armor_prop/armor", 1);
        }
        setup();
}

int query_autoload() { return 1; }