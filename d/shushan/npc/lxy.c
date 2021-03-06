//【蜀山剑派】dhxy-evil 2000.7.5
//yushu修改 2001.2
// lilong alter 2002.01.19
inherit NPC;
void create()
{
        set_name("李逍遥", ({ "li xiaoyao", "li", "xiaoyao" }));
        set("title","蜀山剑派入门弟子");
        set("long", 
"李逍遥身材较瘦，长的浓眉阔眼，气宇暄昂。\n");
        set("gender", "男性");
        set("age", 18);
	 set("class", "xiake");
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("per", 30);
		set("no_suck", 1);
        set("qi", 3000000);
        set("max_qi", 3000000);
        set("jing", 3000000);
        set("max_jing", 3000000);
        set("neili", 30000000);
        set("max_neili", 3000000);
        set("combat_exp", 2100000000);
        set("max_jingli", 3000000);
        set("jingli", 3000000);
		set("jiali", 15000);
        set_skill("force", 1500);
        set_skill("dodge", 1500);
        set_skill("unarmed", 1500);
         set_skill("fumozhang", 1500);
        set_skill("parry", 1500);
        set_skill("sword", 1500);
        set_skill("canxin-jian", 1500);
        set_skill("shushan-force", 1500);
        set_skill("zuixian-steps",1500);
        set_skill("literate",1500);
        map_skill("unarmed", "fumozhang");
        map_skill("force", "shushan-force");
        map_skill("dodge", "zuixian-steps");
        map_skill("parry", "canxin-jian");
        map_skill("sword", "canxin-jian");
        setup();
        create_family("蜀山剑派", 3, "弟子");
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="蜀山派" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师叔见笑了。\n");
			else command("say 师姑见笑了。\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师兄太客气了。\n");
			else command("say 师妹太客气了。\n");
		}
		else 
		{
			command("consider");
			command("say 看在你诚心诚意的份上,我收你为徒!\n");
			command("recruit " + ob->query("id") );
		}
	}
            else
	{
		command("say 看在你诚心诚意的份上,我收你为徒!\n");
		command("recruit " + ob->query("id") );
	}

	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "蜀山派李逍遥弟子");
              }
              return 0;
}

