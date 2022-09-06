// gangzhang.c 钢杖

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("钢叉", ({ "gangcha" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "根");
		set("long", "这是一根明晃晃的三翅钢叉，是专门用做捉鱼的工具。\n");
		set("value", 1500);
		set("rigidity",100);
               set("material", "steel");
		set("wield_msg", "$N抽出一根$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回腰间。\n");
	}
  	init_sword(25);
	setup();
}
int query_autoload() { return 1; }