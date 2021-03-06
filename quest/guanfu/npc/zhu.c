//  zhu 朱安国
 
inherit NPC;
string random_name();
 
void create()
{
	set_name("朱安国", ({"zhu anguo"}));
//	set("nickname", "");
	set("long", 
        "朝廷追捕的要犯，一直反对朝廷。\n");
	set("gender", "男性");
	set("age", 37);
	set("attitude", "peaceful");
	set("shen", 1000);
	set("str", 25);
	set("int", 20);
	set("con", 25);
	set("dex", 27);
	
	set("max_qi", 500);
	set("max_jing", 400);
	set("neili", 700);
	set("max_neili", 700);
	set("jiali", 10);
	set("combat_exp", 75000 + random(40000)); 
	 
         set_skill("force", 60);
         set_skill("hunyuan-yiqi", 70);
         set_skill("dodge", 60);
  

        set_skill("shaolin-shenfa", 30 + random(50));
        set_skill("strike", 90 + random(50));
        set_skill("sword", 50 + random(50));
        set_skill("parry", 50 + random(50));
        set_skill("damo-jian", 30 + random(50));
        set_skill("literate", 70);
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shnfa");
//        map_skill("strike", "kunlun-zhang");
  	map_skill("parry", "damo-jian");
  	 
 
        setup(); 
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
  	add_money("silver", 50);
}
#include "/quest/guanfu/npc/npc.h"
