// jinfeng-xiapi.c
#include <armor.h>
inherit CLOTH;
void create()
{
        set_name(MAG "金凤霞披" NOR, ({ "jinfeng xiapi", "cloth", "xiapi" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一件绣满金色凤凰和牡丹的披风，闻起来还有一股淡淡的幽香。\n");
                set("unit", "件");
                set("value", 600);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/personality", 3);
                set("female_only", 1);
        }
        setup();
}
int query_autoload() { return 1; }
