#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void greeting(object);
void init();
void create()
{
        set_name("欧阳不空", ({ "ouyang bukong", "ouyang"}));
        set("long",
            "通吃帮的首席长老,一身武功\n"+
            "紧次于帮主杨小邪.\n");
        set("gender", "男性");
        set("age", 58);
        set("nickname", HIY "邪云" NOR);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("qi", 30000);
        set("max_qi", 30000);
          set("jing", 6000);
          set("max_jing", 6000);
          set("neili", 8000);
          set("max_neili", 8500);
    set("shen", 100000);
        set("jiali", 500);

        set("combat_exp", 60000000);
        set("score", 10000);
        set_skill("force", 1000);
        set_skill("dodge", 1000);
        set_skill("parry", 1000);
        set_skill("sword",1000);
        set_skill("unarmed",1000);

        set_skill("dabei-zhang",1000);
        set_skill("fanyun-force",1000);
        set_skill("guxing-sword",1000);
       set_skill("damo-force",1000);
          set_skill("literate",1000);
        set_skill("piaomiao-shenfa",1000);

        map_skill("unarmed", "dabei-zhang");
        map_skill("force", "damo-force");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("parry", "dabei-zhang");
        map_skill("sword", "guxing-sword");

        prepare_skill("sword","guxing-sword");
        create_family("通吃帮",2,"首席长老");
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
        if ((int)ob->query_skill("damo-force", 1) < 800) {
                command("say 你的达摩神功还学的不够啊。");
                return;
}

             command("recruit " + ob->query("id"));
               return;
}
