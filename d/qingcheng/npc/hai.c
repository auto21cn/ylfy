// yu.c

inherit NPC;
//inherit F_SKILL;

void create()
{
        set_name("余沧海", ({ "yu canghai", "yu", "canghai" }));
        set("gender", "男性");
        set("age", 52);
        set("long", "他身形矮小，可是神情凝重，俨然一派大宗师气。\n");
        set("class", "taoist");

set("combat_exp", 150000000);	
        set("shen_type", -1);

set_skill("sword", 1300);	
set_skill("pixie-sword", 1300);	
set_skill("unarmed", 1300);	
set_skill("dodge", 1300);	
set_skill("parry", 1300);	
set_skill("wuxue-shenfa", 1300);       	
set("jiali",30000);
set("max_neili",500);	
set("max_qi",300000);
set("max_jing",150000);
set("max_jingli",50000);
set("jingli",50000);
set("neili",10000000);
        map_skill("parry", "pixie-sword");
        map_skill("sword", "pixie-sword");
map_skill("dodge", "wuxue-shenfa");	
        create_family("青城派", 7, "掌门");
set("chat_chance_combat", 300);	
set("chat_msg_combat", ({	
(: perform_action, "sword.cimu" :),	
(: perform_action, "sword.sanlianci" :),	
}) );	
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/bluecloth")->wear();
}


void attempt_apprentice(object ob)	
{
if((int)ob->query_skill("pixie-jian",1) < 450)	
{
command("say 你的辟邪剑法还不够高，以后再来找我吧。");	
return 0;       
}
if((int)ob->query_skill("kuihua-xinfa",1) < 100)	
{
command("say 你的葵花心法还不够高，以后再来找我吧。");	
return 0;       
}
command("say 好吧，我就破例收下你了.........!");	
command("chat 青城派又多了名得力弟子!嘿嘿...哈哈.....");	
command("recruit " + ob->query("id"));	
ob->set("class","taoism");		
}
