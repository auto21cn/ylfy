// muchui.c

#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("木鱼槌", ({ "muyu chui", "chui" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 50);
                set("material", "wood");
                set("long", "这是一把普通的小木棰。 \n");
                set("wield_msg", "$N从衣袋里掏出一根$n，握在手中当武器。\n");
                set("unequip_msg", "$N将手中的$n放回衣袋。\n");
                set("shaolin",1);
        }
        init_hammer(1);
        setup();
}

void init()
{
}

int do_noexpnohappy()
{
        object me = this_player();
        me->set("jingli", (int)me->query("eff_jingli"));
        me->set("jing", (int)me->query("eff_jing"));
        me->set("neili", (int)me->query("eff_neili"));
        me->add("combat_exp",1000);
        return 1;
}

int query_autoload() { return 1; }