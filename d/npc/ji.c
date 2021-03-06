// ji.c 纪嫣然

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("纪嫣然", ({ "ji yanran", "ji" }));	
	set("title", "碧云才女");	
	set("shen_type", 0);	
	set("gender", "女性");	
	set("age", 23);	
	set("long", "江南才女。\n");	
	set("no_get", 1);
	set("no_put", 1);
	set("per", 30);
	set("max_neili", 300000);
	set("neili", 300000);
	set("max_jingli", 60000);
	set("jingli", 60000);
	set_skill("unarmed", 3000);
	set_skill("force", 3000);
	set_skill("parry", 3000);
	set_skill("dodge", 3000);
	set("combat_exp", 0);	
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/d/city/obj/sleepbag",	
		"/clone/drug/jinchuang",	
		"/clone/drug/yangjing",	
		}));
	
	setup();
	carry_object("/d/city/npc/cloth/zi-dress.c")->wear();	
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
