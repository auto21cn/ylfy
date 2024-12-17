#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name("铁锤", ({ "hammer" }) );
        set_weight(8500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把普通的锤子。\n");
                set("value", 0);
                set("no_drop",1 );
                set("material", "copper");
                set("wield_msg", "$N拿出一把$n，试了试重量，然后握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(25);
        setup();
}

