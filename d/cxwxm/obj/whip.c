#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(BLU"痴心鞭"NOR, ({ "whip" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 200);
                set("material", "iron");
                set("long", "这是痴心妄想门特制的短鞭。\n");
                set("wield_msg", "$N抽出一根黝黑的$n握在手中　\n");
                set("unequip_msg", "$N将手中的$n卷入腰间。　\n");
        }

         init_whip(200);
        setup();
}
