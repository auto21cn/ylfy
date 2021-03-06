// guanjia.c
#include "/quest/quest.h"
#include <ansi.h>

inherit NPC;
void create()
{
        set_name("臣飒亟", ({ "chen sahan","chen" }) );
        set("title", "红花会总管");
        set("gender", "男性" );
        set("age", 30);
        set("str", 22);
        set("int", 26);
        set("per", 23);
        set("kar", 25);
        set("con", 23);
        set("dex", 23);
        set("long",
            "他看上去一副极为精明能干的模样，\n"
            "红花会中大大小小的琐碎事务全归他管。\n");
        create_family("红花会",2, "弟子");
        set("combat_exp", 300000);
        set("attitude", "friendly");
        set("env/wimpy", 30);
        set("max_neili", 1000);  
        set("neili", 1000);             
        set("jiali", 70);

    set_skill("force", 100);
    set_skill("honghua-shengong",100);
    set_skill("dodge", 100);
    set_skill("youlong-shenfa", 100);
    set_skill("unarmed", 100);
    set_skill("parry",100);
    set_skill("sword",100);
    set_skill("luohua-jian",100);
    set_skill("literate",170);

    map_skill("force", "honghua-shengong");
    map_skill("dodge", "youlong-shenfa");
    map_skill("parry", "luohua-jian");
    map_skill("sword", "luohua-jian");

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("gold", 10);

}