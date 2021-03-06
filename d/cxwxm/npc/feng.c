#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("上官飞凤", ({ "shangguan feifeng", "feng","feifeng" }));
        set("nickname", HIG "痴心女" NOR);
        create_family("痴心妄想门", 2,"门主");
        set("jihao",1);
        set("long","她就是痴心妄想门第二代门主、痴心女上官飞凤。");
        set("gender", "女性");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("per", 30);
        set("dex", 30);
        
        set("max_qi", 400000);
        set("max_jing", 200000);
        set("neili", 300000);
        set("max_neili", 300000);
        set("jiali", 150);
        set("combat_exp", 300000000);
        set("score", 500000);

        set_skill("force", 1450);
        set_skill("dodge", 1420);
        set_skill("unarmed",1500);
        set_skill("parry", 1440);
        set_skill("whip", 1500);
        set_skill("literate", 2000);
        set_skill("chixin-bianfa", 1500);
        set_skill("shuiyue", 1420);
        set_skill("wangran-xinfa", 1440);
        set_skill("cxwx-quan", 1400);
    
        map_skill("force", "wangran-xinfa");
        map_skill("whip", "chixin-bianfa");
        map_skill("dodge", "shuiyue");
        map_skill("unarmed", "cxwx-quan");
        map_skill("parry", "chixin-bianfa");
        map_skill("dodge", "shuiyue");
             
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "whip.juan" :),
                (: perform_action, "whip.mi" :),
                (: exert_function, "recover" :),
                (: perform_action, "unarmed.tian" :) ,
          }) );


        setup();
        carry_object("/d/cxwxm/obj/whip.c")->wield();
        carry_object("/d/cxwxm/obj/siyi.c")->wear();
}

void attempt_apprentice(object ob)
{
        if (!ob->query("mengsha")) {
                command("say 你先去找我的徒弟吧！");
                return;
}
        if ((int)ob->query_skill("wangran-xinfa", 1) < 400) {
                command("say 本门的武功若无心法根基，如何能提高？"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "是否还应该在妄然心法上多下点功夫？");
                return;
        }
        if ((int)ob->query("betrayer") != 0) {
                command("say 尔等忘恩负义的无耻之徒，快滚！");
                command("say 你这个败类，" + RANK_D->query_respect(ob) +
                        "快滚吧！");
                return;
        }
        if ((int)ob->query("per") < 30) {
                command("say 哎！可惜你的容貌……！");
                command("say 你还是早死早投胎算了!");
                return;
        }
 
        if (ob->query_int() < 80) {
                command("say 本门武功全凭痴心妄想。");
                command("say 要想修到最高境界，你的悟性还不够");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
   if ((string)ob->query("gender")=="女性")
   {
                message_vision("上官飞凤垂目沉思片刻, 说道：“好吧, 我就收下你了。”\n",ob);
       command("recruit " + ob->query("id"));
       command("chat 哈哈哈哈！！！！");
       command("chat 好！我就收下你这个弟子，以后要好好妄想！");
                ob->set("cxwxmt",1);
                return;}
   else
      {
                message_vision("你那里长得象女人？去做手术吧！\n",ob);
       return;}
        

}
