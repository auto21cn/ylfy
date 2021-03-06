// liang.c 轩辕亮
// marry 99.8

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_me();
void create()
{
        set_name("轩辕亮", ({ "xuanyuan liang", "liang" }));
        set("nickname", HIY "过江猛龙" NOR);
        create_family("痴心妄想门", 2,"护凤使");
        set("jihao",1);
        set("long","他就是痴心妄想门开山始祖的大弟子“过江猛龙”轩辕亮。");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("per", 30);
        set("dex", 30);
        
        set("max_qi", 400000);
        set("max_jing", 43000);
        set("neili", 300000);
        set("max_neili", 500000);
        set("jiali", 150);
        set("combat_exp", 90000000);
        set("score", 500000);

        set_skill("force", 810);
        set_skill("dodge", 820);
        set_skill("unarmed",740);
        set_skill("parry", 825);
        set_skill("axe", 860);
        set_skill("literate", 900);
        set_skill("wangxiang-fufa", 850);
        set_skill("shuiyue", 830);
        set_skill("wangran-xinfa", 840);
        set_skill("cxwx-quan", 760);
    
        map_skill("force", "wangran-xinfa");
        map_skill("axe", "wangxiang-fufa");
        map_skill("dodge", "shuiyue");
        map_skill("unarmed", "cxwx-quan");
        map_skill("parry", "wangxiang-fufa");
        map_skill("dodge", "shuiyue");
               
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "axe.jifeng" :),
                (: perform_action, "axe.wang" :),
                (: exert_function, "recover" :),
                (: perform_action, "unarmed.tian" :) ,
          }) );
        set("inquiry", ([
                "神兵利器" : (: ask_me :),
        ]));
        setup();
        carry_object("/d/cxwxm/obj/shenfu.c")->wield();
        carry_object("/d/cxwxm/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
        if (!ob->query("chuhuan")) {
                command("say 你先去找我的徒弟吧！");
                return;
}
        if ((int)ob->query_skill("wangran-xinfa", 1) < 400) {
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
                command("say 你还是去美容后在来吧!");
                return;
        }
 
        if (ob->query_int() < 80) {
                command("say 本门武功全凭痴心妄想。");
                command("say 要想修到最高境界，你的悟性还不够");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
   if ((string)ob->query("gender")=="男性")
   {
                message_vision("轩辕亮仔细的望了你片刻, 说道：“好吧, 我就收下你了。”\n",ob);
       command("recruit " + ob->query("id"));
       command("chat 哈哈！终于我后继有人了！");
       command("chat 好！记住我的弟子以后凡是找老婆一定要找痴心的女子哟！");
                return;}
   else
      {
                message_vision("你不是男人，滚吧！\n",ob);
       return;}
        

}

int ask_me()
{
        object me,ob;
        object wuqi;
        me = this_player();
       ob = this_object(); 
      if (((me->query ("family/family_name"))!="痴心妄想门")||       (me->query("shen",1) < 5000000) || (ob->query_temp("没有")))
      {
       command("say 这兵器杀气太重，不适合你用！");
      }
      else
      {
       command("say 看到你对本门忠心耿耿，你就拿去试试！");
       wuqi=new("/d/cxwxm/obj/guifu");
       wuqi->move(me);     
       add_temp("没有",1);
      }
      return 1;
}


