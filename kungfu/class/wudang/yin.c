// yin.c 殷梨亭
inherit NPC;
inherit F_MASTER;
void create()
{
    set_name("殷梨亭", ({ "yin litin", "yin" }));
    set("nickname", "武当六侠");
    set("long", 
        "他就是张三丰的六弟子殷梨亭。\n"
             "只见他满脸风尘之色，两鬓微见斑白。\n");
    set("gender", "男性");
    set("age", 30);
    set("attitude", "heroism");
    set("shen_type", 1);
    set("str", 26);
    set("int", 30);
    set("con", 26);
    set("dex", 28);
    
    set("max_qi", 1200);
    set("max_jing", 800);
    set("neili", 1500);
    set("max_neili", 1500);
    set("jiali", 100);
    set("combat_exp", 1025000);
    set("score", 60000);
    set_skill("force", 180);
    set_skill("taiji-shengong", 160);
    set_skill("dodge", 180);
    set_skill("tiyunzong", 160);
    set_skill("unarmed", 180);
    set_skill("taiji-quan", 160);
    set_skill("parry", 180);
    set_skill("sword", 100);
    set_skill("taiji-jian", 100);
    set_skill("taoism", 180);
    set_skill("literate", 180);
    map_skill("force", "taiji-shengong");
    map_skill("dodge", "tiyunzong");
    map_skill("unarmed", "taiji-quan");
    map_skill("parry", "taiji-jian");
    map_skill("sword", "taiji-jian");
    create_family("武当派", 2, "弟子");
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: perform_action, "sword.chan" :),
        (: perform_action, "sword.lian" :),
        (: perform_action, "sword.sui" :),
        (: exert_function, "recover" :),
    }) );
    setup();
    carry_object("/clone/weapon/changjian")->wield();
    carry_object("/d/wudang/obj/yelcloth")->wear();
}
void init()
{
::init();
remove_call_out("greeting");
call_out("greeting", 1, this_player());
}

void greeting(object ob)
{
    mapping fam;
        int i ;
    object me;
    object* obj;
    me = this_object();
	if( !ob || environment(ob) != environment() ) return;
    if (interactive(ob) 
    && !environment(ob)->query("no_fight"))
    {
         if (!(fam = ob->query("family")) || fam["family_name"] != "武当派")
        {
                   if (ob->query("shen")>-1000)      
            {
            command("say 这里是武当重地，你在这里瞎逛什么？");
            obj = all_inventory(environment(me));
            for(i=0; i<sizeof(obj); i++) 
            {
            if(obj[i]==this_player()) continue;
            if(obj[i]==me) continue;
            if((obj[i]->query("title")=="盗贼")||(obj[i]->query("shen")<-1000)) 
            {
                command("say 大胆蟊贼,敢在此胡作非为,看招!!");
                me->kill_ob(obj[i]);
                obj[i]->kill_ob(me);
            }
            }
            }   
       else{
            command("say 一定要杀了你这江湖败类！");
            me->set_leader(ob);
            remove_call_out("kill_ob");
            call_out("kill_ob", 1, ob); 
        
            }
        }    
    }       
}
void attempt_apprentice(object ob)
{
    if ((int)ob->query("shen") < 100) {
        command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
        command("say " + RANK_D->query_respect(ob) + "若能做出" +
            "几件侠义之事，我一定收你。");
        return;
    }
    command("say 好吧，既然" + RANK_D->query_respect(ob) + "也是" +
        "我辈中人，今天就收下你吧。");
    command("recruit " + ob->query("id"));
}
