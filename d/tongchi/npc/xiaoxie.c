#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void greeting(object);
void init();
void create()
{
        set_name("杨小邪", ({ "yang xiaoxie", "yang"}));
        set("long", "他就是通吃帮帮主,小邪神-杨小邪\n");
        set("gender", "男性");
        set("age", 19); 
         set("nickname", HIG "通吃小霸王" NOR);
          set("shen",0);
        set("attitude", "peaceful");

        set("str", 65);
        set("int", 65);
        set("con", 65);
        set("dex", 65);
        set("kar", 65);

        set("qi", 40000);
        set("max_qi", 40000);
          set("neili", 8000);
         set("max_jing", 8000);
          set("neili", 9000);
          set("max_neili", 9000);
		set("shen", 50000);
        set("jiali", 1000);

        set("combat_exp", 500000000);
        set("score", 10000);
        set_skill("force", 1500);
        set_skill("dodge", 1500);
        set_skill("parry", 1500);
        set_skill("sword",1500);
        set_skill("unarmed",1500);

        set_skill("dabei-zhang",1500);
        set_skill("damo-force",1500);
        set_skill("guxing-sword",1500); 
          set_skill("literate",1500);
        set_skill("langzi-sword",1500);
        set_skill("piaomiao-shenfa",1500);

        map_skill("unarmed", "dabei-zhang");
        map_skill("force", "damo-force");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("parry", "dabei-zhang");
        map_skill("sword", "langzi-sword");

        prepare_skill("sword","langzi-sword");
        create_family("通吃帮",1,"帮主");
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
        if ((int)ob->query_skill("damo-force", 1) < 1000) {
                command("say 你的达摩神功还学的不够啊。");
                return;
                  } 
        if ((int)ob->query_skill("fanyun-force", 1) < 1000) {
                command("say 你的翻云神功还学的不够啊。");
                return;
                  } 
         message("vision",HIM"〖英雄传闻〗"NOR+":"+HIR" 听说"HIW+ob->short()+NOR HIB"拜入通吃帮帮主杨小邪门下!\n"NOR,users());
     command("recruit " + ob->query("id"));
               return;
}
