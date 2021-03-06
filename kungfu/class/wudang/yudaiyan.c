// yudaiyan.c 俞岱岩 
inherit NPC;
void create()
{
set_name("俞岱岩", ({ "yu daiyan", "yu" }));  
set("nickname","武当三侠");
    set("long", 
        "他就是张三丰的三弟子俞岱岩。\n"
        "身穿一件干干净净的灰色道袍。\n"
        "一副英爽豪迈．龙精虎猛的模样。\n");
    set("gender", "男性");
    set("age",43);
    set("attitude", "peaceful");
    set("shen_type", 1);
    set("str", 18);
    set("int", 18);
    set("con", 18);
    set("dex", 18);
    
    set("max_qi", 20);
    set("max_jing", 1000);
    set("neili", 1000);
    set("max_neili", 1000);
    set("jiali", 50);
    set("combat_exp", 2000000);
    set("score", 60000);
    set_skill("force", 200);
    set_skill("taiji-shengong", 180);
    set_skill("dodge", 180);
    set_skill("tiyunzong", 160);
    set_skill("unarmed", 200);
    set_skill("taiji-quan", 200);
    set_skill("parry", 180);
    set_skill("sword", 180);
    set_skill("taiji-jian", 160);
    set_skill("literate", 150);
    map_skill("force", "taiji-shengong");
    map_skill("dodge", "tiyunzong");
    map_skill("unarmed", "taiji-quan");
    map_skill("parry", "taiji-quan");
    map_skill("sword", "taiji-jian");
    create_family("武当派", 2, "弟子");
    setup();
    carry_object("/d/wudang/obj/greyrobe")->wear();
    carry_object("/d/kunlun/obj/sandals")->wear();
}

void attempt_apprentice(object ob)
{
    if ((int)ob->query("shen") < 100) {
        command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
        return;
    }
    command("say 我已经是废人一个，不能教你什么，你还是拜我的其他师兄吧！");
}
