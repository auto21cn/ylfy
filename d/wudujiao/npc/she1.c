// by victori
inherit NPC;
#include "duchong.h"
#include <ansi.h>


string *first_name = ({ "花皮", "青竹", "四脚", "独眼"});
string *name_words = ({ "蛇"});
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        set_name(name,({"du she"}));
	set("race", "野兽");
        set("long", "一条一尺多长，鬼头鬼脑的小蛇。\n");
	set("age", 100);
	set("attitude", "peaceful");

	set("max_jing", 200);
	set("max_qi", 300);

	set("str", 20);
	set("con", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/armor", 80);
	set_temp("apply/damage", 80);

	set("combat_exp", 100000+random(40)*10000);
        set_weight(5000);
	setup();
}
