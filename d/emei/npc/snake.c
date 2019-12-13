//snake.c

inherit NPC;

void create()
{
	set_name("巨蟒", ({ "snake", "she" }) );
	set("race", "野兽");
	set("age", 20);
	set("long", "一只庞然大物，它眼中喷火,好象要一口把你吞下。\n");
	set("attitude", "aggressive");
	set("qi", 350);
	set("max_qi", 350);
	set("jing", 200);
	set("max_jing", 200);

	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "bite" }) );

	set("combat_exp", 10000);

	setup();
}