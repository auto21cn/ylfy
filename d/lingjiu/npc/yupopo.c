// NPC yupopo.c
#include <ansi.h>
inherit NPC;
void create()
{
    set_name("余婆婆", ({ "yu popo", "yu", "popo" }));
    set("long",
        "她是「灵鹫宫」九天九部中昊天部的首领.\n"+
        "她跟随童姥多年, 出生入死,饱经风霜.\n");
    set("title", "昊天部首领");
    set("gender", "女性");
    set("age", 60);
    set("attitude", "peaceful");
    set("str", 20);
    set("int", 125);
    set("con", 30);
    set("dex", 150);
    set("qi", 2000);
    set("max_qi", 2000);
    set("jing", 1500);
    set("max_jing", 1500);
    set("neili", 1000);
    set("max_neili", 1000);
    set("jiali", 50);
    set("combat_exp", 100000);

    set_skill("force", 100);
    set_skill("unarmed", 100);
    set_skill("dodge", 100);
    set_skill("parry", 100);
    set_skill("sword",100);
    set_skill("tianyu-qijian",100);
    set_skill("zhemei-shou",100);
    set_skill("liuyang-zhang",100);
    set_skill("yueying-wubu",100);
    set_skill("bahuang-gong", 100);
    map_skill("force", "bahuang-gong");
    map_skill("dodge", "yueying-wubu");
    map_skill("unarmed", "liuyang-zhang");
    map_skill("parry", "liuyang-zhang");
    map_skill("sword", "tianyu-qijian");
    
    set("chat_chance_combat", 30);  
    set("chat_msg_combat", ({
    (: command("enable unarmed zhemei-shou") :),
    (: command("enable unarmed liuyang-zhang") :),
}));

    create_family("灵鹫宫",2,"弟子");
    setup();
        carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
    carry_object("/clone/weapon/changjian")->wield();
    add_money("silver",40);
}
