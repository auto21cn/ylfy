#define BOOK   3
#define FILE   "/doc/doc/00"+BOOK
inherit ITEM;
void create()
{
    set_name("(第"+chinese_number(BOOK)+"回) "+BOLD+"封神演义"+NOR, ({ "book" }));
    set_weight(50);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "本");
        set("long", CYN "\n                      封  神  演  义\n______________________________________________________\n"+NOR);
        set("value", 500);
        set("no_sell",1);
        set("material", "silk");
    }
}

string long()
{
      return query("long")+read_file(FILE);
}
int query_autoload() { return 1; }
