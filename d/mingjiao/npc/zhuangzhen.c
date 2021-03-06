// zhuangzhen.c 庄铮
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

object ob = this_object();
void create()
{
        set_name("庄铮",({"zhuang zhen","zhuang","zhen"}));
        set("title","锐金旗使");
         set("title",YEL"锐金旗使"NOR);
        set("long", 
                "他就是明教的洪水旗使。\n"
                "他身才魁梧,满脸横肉.武艺甚精\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 24);
        set("int", 16);
        set("con", 16);
        set("dex", 24);
        
        set("max_qi",1000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 40);
        set("combat_exp", 200000);
        
        set_skill("sword",100);
        set_skill("dodge",100);
        set_skill("unarmed",100); 
        set_skill("literate",100);
        set_skill("force",100);
        set_skill("shenghuo-shengong",100);
        set_skill("qingyunwu", 100);
        set_skill("liehuo-jian",100);
        set_skill("parry", 100);
        
        map_skill("dodge", "qingyunwu");
        map_skill("force","shenghuo-shengong");
        map_skill("sword","liehuo-jian");
        map_skill("parry","liehuo-jian");
        
        create_family("明教",35,"五行旗使");
        
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        
}


void init()
{
       object ob;

       ::init();

        ob = this_player();
        if((int)ob->query("score") < -10 && ob->query("family/master_id")=="zhuang zhen")
        {
                    command("chat "+ob->query("name")+"！你为人不忠不义，我明教岂能留你？\n");
                    command("expell "+ ob->query("id"));
                    this_player()->set("title","明教" + RED + "弃徒" NOR);   
        }

}


void attempt_apprentice(object ob)
{
       if ((string)ob->query("family/family_name")!="明教" || (string)ob->query("class")!="shizhe") {
                command("say " + RANK_D->query_respect(ob) + "若想拜入我派，你可以先去拜徐达。");
                return;
        }        

        command("say 哈哈！ 我明教又得一良材，望你日后康扶正义，把我明教发扬光大。");
        command("recruit " + ob->query("id"));
        if((string)ob->query("class") != "shizhe")
        ob->set("class", "shizhe");
        ob->set("title","明教锐金旗下教众");
}

