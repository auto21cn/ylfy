inherit ITEM;
void create()
{
    set_name(HIG "翡翠" NOR, ({ "feicui" }) );
    set("unit", "块");
    set("value",1000000);
    set("long","这是一块罕见的翡翠，看来值不少钱。\n");
    set_weight(100);
}
int query_autoload() { return 1; }