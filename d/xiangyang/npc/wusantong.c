// wusantong.c

#include <ansi.h>

inherit NPC;
void create()
{
	set_name("武三通", ({"wu santong", "wu", "santong"}));
	set("gender", "男性");
	set("age", 55);
	set("long", "一灯大师的四大弟子之一，现在襄阳协助郭靖、黄蓉守城。\n");
 	set("attitude", "peaceful");
	
	set("per", 17);
	set("str", 40);
	set("int", 20);
	set("con", 30);
	set("dex", 25);

	set("qi", 1500);
	set("max_qi", 1500);
	set("jing", 500);
	set("max_jing", 500);
	set("neili", 1500);
	set("max_neili", 1500);
	
	set("combat_exp", 300000);
	set("score", 20000);
	 
	set_skill("force", 150);
	set_skill("kurong-changong", 150);
	set_skill("finger", 150);
	set_skill("yiyang-zhi", 150);
	set_skill("cuff", 150);
	set_skill("jinyu-quan", 150);
	set_skill("dodge", 150);
	set_skill("tiannan-step", 150);
	set_skill("parry", 150);
	
	map_skill("force", "kurong-changong");
	map_skill("finger", "yiyang-zhi");
	map_skill("cuff", "jinyu-quan");
	map_skill("dodge", "tiannan-step");
	map_skill("parry", "yiyang-zhi");
	prepare_skill("cuff", "jinyu-quan");
	
	setup();
	
	carry_object("/clone/cloth/cloth")->wear();
}
