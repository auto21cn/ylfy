//marry 8.13
#include <weapon.h>

#include <ansi.h>

inherit AXE;

void create()
{
        set_name(HIB"猛龙神斧"NOR, ({ "axe" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 200);
                set("material", "iron");
                set("long", "这是痴心妄想门宝斧，是开山门主用上古玄铁做成。\n");
                set("wield_msg", "$N从背后拔出一亮晃晃$n握在手中　\n");
                set("unequip_msg", "$N将手中的$n插在背后。　\n");
        }
{       set("no_get",1);
        set("no_drop",1);
        set("no_give",1);
}
        init_axe(900);
        setup();
}
