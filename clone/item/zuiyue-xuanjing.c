//xuanjing.c
inherit ITEM;
void create()
{
        set_name(HIY "醉月玄晶"NOR, ({"zuiyue xuanjing"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long","这是一块非常罕见的材料，蕴含着超凡的力量，似乎是重新制造兵器的必备材料。\n");
                set("value", 10000000);
                set("material", "bamboo");
              }
}
int query_autoload() { return 1; }