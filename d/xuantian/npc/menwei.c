//han.c  by:pipip
inherit NPC;
void create()
{
    set_name("玄天弟子", ({ "men wei","men","wei"}) );
    set("gender", "男性" );
    set("age", 15);
    set("long", "无名老人收养的乞儿，寒真视为养子。\n");
    set("attitude", "peaceful");
    set("shen_type", -1);
    set("nickname", HIC "铁手"HIW"童子" NOR);
    set("str", 110);
    set("int", 90);
    set("con", 90);
    set("dex", 90);
    set("per", 25);
    set("max_qi", 6500000);
    set("max_jing", 150000);
    set("jing",15000);
    set("neili", 2000000);
    set("max_neili", 100000);
    set("jiali",1900);
    set("combat_exp", 30000000);
	set("score", 20); 
    set_skill("force", 500);
    set_skill("dodge", 600);
    set_skill("unarmed", 500);
    set_skill("parry", 500);
    set_skill("blade",500);
    set_skill("yijing-force",500);
    set_skill("lingyunbu", 600);
    set_skill("cuixin-zhang", 500);
    set_skill("tianxin-blade", 500);
    map_skill("force", "yijing-force");
    map_skill("dodge", "lingyunbu");
    map_skill("parry", "cuixin-zhang");
    map_skill("unarmed", "cuixin-zhang");
    map_skill("blade", "tianxin-blade");
    create_family("玄天派",3,"弟子");
	setup();

    carry_object("/d/xuantian/obj/cloth")->wear();
    carry_object("/d/xuantian/obj/xblade")->wield();
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query("kar") < 28) {
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"看上去不像福缘深厚之人。");
                return;
                  } 
        if ((int)ob->query("per") < 28) {
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"的长相似乎....");
                return;
                  } 
     command("recruit "+ob->query("id"));
     return;
}