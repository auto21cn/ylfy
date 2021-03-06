// qian.c 上官云倩
// marry 99.8

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("上官云倩", ({ "shangguan yunqian", "qian","shangguan","yunqian" }));
        set("nickname", HIM "桃花女" NOR);
        create_family("痴心妄想门", 3,"弟子");
        set("jihao",1);
        set("long","她就是痴心妄想门门主的养女“桃花女”上官云倩。");
        set("gender", "女性");
        set("age", 17);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("per", 30);
        set("dex", 30);
        
        set("max_qi", 40000);
        set("max_jing", 9000);
        set("neili", 100000 + random(50000));
        set("max_neili", 100000);
        set("jiali", 300);
        set("combat_exp", 60000000);
        set("score", 500000);

        set_skill("force", 380);
        set_skill("dodge", 370);
        set_skill("unarmed",320);
        set_skill("parry", 390);
        set_skill("whip", 390);
        set_skill("literate", 450);
        set_skill("chixin-bianfa", 350);
        set_skill("shuiyue", 320);
        set_skill("wangran-xinfa", 390);
        set_skill("cxwx-quan", 380);
    
        map_skill("force", "wangran-xinfa");
        map_skill("whip", "chixin-bianfa");
        map_skill("dodge", "shuiyue");
        map_skill("unarmed", "cxwx-quan");
        map_skill("parry", "chixin-bianfa");
        map_skill("dodge", "shuiyue");
               
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "whip.mi" :),
        }) );

        setup();
        carry_object("/d/cxwxm/obj/whip.c")->wield();
        carry_object("/d/cxwxm/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
        if (!ob->query("yujiao")) {
                command("say 你先去找我师妹吧！");
                return;
        }
        if ((int)ob->query_skill("wangran-xinfa", 1) < 100) {
                command("say 本门的武功若无心法根基，如何能提高？"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "是否还应该在妄然心法上多下点功夫？");
                return;
        }
        if ((int)ob->query("shen") < 0) {
                command("say 本门最忌无耻之徒，快滚吧！");
                command("say 你这种败类，" + RANK_D->query_respect(ob) +
                        "快滚吧！");
                return;
        }
        if ((int)ob->query("per") < 30) {
                command("say 本门武功非绝世容貌不可习得！");
                command("say 你还是去美容后再来吧!");
                return;
        }
 
        if (ob->query_int() < 50) {
                command("say 本门武功全凭痴心妄想。");
                command("say 要想修到最高境界，你的悟性还不够");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
   if ((string)ob->query("gender")=="女性")
   {
                message_vision("上官云倩仔细的望了你片刻, 说道：“好吧, 我就收下你了。”\n",ob);
       command("recruit " + ob->query("id"));
                ob->set("yunqian",1);
                       return;}  
   else
      {
                message_vision("对不起！我只收女徒。\n",ob);
       return;}
        

}
