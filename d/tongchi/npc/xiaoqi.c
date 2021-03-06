#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void greeting(object);
void init();
void create()
{
        set_name("小七", ({ "xiao qi", "xiao"}));
        set("long", "通吃帮黄金打手猛男阿七。\n");
        set("gender", "男性");
        set("age", 18); 
        set("nickname", HIC "狂男" NOR);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("qi", 30000);
        set("max_qi", 30000);
        set("jing", 6000);
        set("max_jing", 8000);
        set("neili", 9000);
        set("max_neili", 6000);
        set("jiali", 500);
        set("shen", 100000);

        set("combat_exp", 60000000);
        set("score", 10000);
        set_skill("force", 800);
        set_skill("dodge", 850);
        set_skill("parry", 840);
        set_skill("sword",840);
        set_skill("unarmed",850);

        set_skill("dabei-zhang",850);
        set_skill("damo-force",850);
        set_skill("guxing-sword",840);
          set_skill("literate",50);
        set_skill("piaomiao-shenfa",850);

        map_skill("unarmed", "dabei-zhang");
        map_skill("force", "damo-force");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("parry", "dabei-zhang");
        map_skill("sword", "guxing-sword");

        prepare_skill("sword","guxing-sword");
        create_family("通吃帮",2,"黄金打手");
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
}

void attempt_apprentice(object ob)
{

                  if ((string)ob->query("gender") == "无性") {
                                 command("say 这位公公不要开玩笑了。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是快去伺候皇上吧！");
                return;
                  } 
        if ((int)ob->query_skill("damo-force", 1) < 600) {
                command("say 你的达摩神功还学的不够啊。");
                return;
}

             command("recruit " + ob->query("id"));
               return;
}
