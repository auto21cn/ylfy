// NPC:/d/shushan/npc/lingyunzi.c
//yushu 2001.2
//lilong 改于2002.01.08
inherit NPC;
inherit F_MASTER;
void create()
{
       set_name("凌云子", ({"ling yunzi", "yunzi", "zi"}));
       set("title", "蜀山派第三代弟子");   
       set("gender", "男性");
       set("age", 32);
       set("attitude", "peaceful");
       set("class", "xiake");
       set("str", 30);
       set("int", 30);
       set("per", 30);
       set("con", 30);
       set("combat_exp", 2100000000);
       set("max_jing", 1000000);
	   set("eff_jing", 1000000);
	   set("jing", 1000000);
	   set("max_qi", 1000000);
	   set("eff_qi", 1000000);
	   set("qi", 1000000);
       set("neili", 1000000);
       set("max_neili", 10000);
		set("max_jingli", 5000);
        set("jingli", 1000000);
        set("jiali", 3000);
        set_skill("shushan-force", 500);
        set_skill("songhe-sword", 500);
       set_skill("dodge", 500);
       set_skill("literate", 500);
       set_skill("sword", 500);
       set_skill("force", 500);
       set_skill("parry", 500);
       set_skill("zuixian-steps", 500);
       map_skill("dodge", "zuixian-steps");
       map_skill("parry", "songhe-sword");
       map_skill("sword", "songhe-sword");
       map_skill("force", "shushan-force");
       create_family("蜀山派", 3, "弟子");
       setup();
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
		command("say 是你自己要拜的，可别怪我啊!。\n");
		command("recruit " + ob->query("id") );
}
}
                                 else
{
		command("say 好，我蜀山派一门人才辈出，"+RANK_D->query_respect(ob)+"可得给师父争气。\n");
		command("recruit " + ob->query("id") );
	}

	return;
}
int recruit_apprentice(object ob)
{
               if( ::recruit_apprentice(ob) )
{
                ob->set("class", "xiake");
                ob->set("title", "蜀山派第四代弟子");
                            }

        return 0;
}


