// shenmiren.c 神秘人
inherit NPC;
//inherit F_VENDOR;
inherit F_DEALER;
void create()
{
        set_name("神秘人", ({ "shenmi ren"}));
        set("title", "藏宝阁老板");
        set("nickname", "大奸商");
        set("shen_type", 1);       
		set("per", 30);
        set("gender", "女性");
        set("age", 25);
        set("long",
                "藏宝阁的老板，没有人知道他到底是谁，从哪里来，\n"
                "但是他所卖的物品，全部都是各种宝物。\n");
        set("combat_exp", 2100000000);
        set("attitude", "friendly");
		set("str", 300);
        set("con", 300);
        set("int", 300);
        set("dex", 300);
        set("max_qi", 300000000);
	    set("eff_qi", 300000000);
	    set("qi", 300000000);
        set("max_jing", 300000000);
	    set("eff_jing", 300000000);
	    set("jing", 300000000);
	    set("neili", 300000000);
	    set("max_neili", 3000000);
	    set("jingli", 300000000);
	    set("max_jingli", 3000000);
	    set("no_suck", 1);
	    set("jiali", 7000);
	    set("shen", 0);
	    set("end_boss", 1);
	    set("env/wimpy", 50);
	    set_temp("apply/attack",  150);
	    set_temp("apply/defense", 130);
	    set("combat_exp", 2100000000);
	    set("xyzx_sys/level", 50000);
	    set("xyzx_sys/fanying", 70000);
	    set("xyzx_sys/jingzhun", 70000);
	    set("xyzx_sys/minjie", 70000);
	    set("xyzx_sys/lingxing", 70000);
	    set_skill("force", 5000); 
	    set_skill("unarmed", 5000);
	    set_skill("dodge", 5000);
	    set_skill("parry", 5000);
	    set_skill("sword", 5000);
	    set_skill("douzhuan-xingyi", 5000);
	    set_skill("guiyuan-tunafa", 5000); 
	    set_skill("tiezhang-zhangfa", 5500+random(1500)); 
	    set_skill("taiji-jian", 5500+random(1500)); 
	    set_skill("shaolin-shenfa", 5000);
	    map_skill("force", "guiyuan-tunafa");
	    map_skill("unarmed","tiezhang-zhangfa");
	    map_skill("parry", "douzhuan-xingyi");
	    map_skill("sword", "taiji-jian");
	    map_skill("dodge", "shaolin-shenfa");
        /*set("inquiry", ([
                "阿庆" : "我们家阿庆去北边做生意去了耶。\n",
                "生意" : "这个么……。\n",
        ]));*/
        
        set("vendor_goods", ({
                "clone/map/obj/bangding-fu.c",
				"clone/map/obj/jiebang-fu.c",
				"clone/map/obj/jingang-shi.c",
                "clone/tzbox/new-box.c",				
        }));
        setup();
        carry_object("/clone/cloth/hiw_cloth")->wear();
}
void init()
{
        object ob,owner;
        string nature;
        nature=NATURE_D->room_event_fun();
        owner=this_object();
        ::init();
        if (base_name(environment())!=query("startroom")) return;
        if (interactive(ob = this_player()) && !is_fighting()) {
        	if(nature!="event_dawn"
		&& nature!="event_night"
		&& nature!="event_midnight"){
                remove_call_out("greeting");
                call_out("greeting", 1, ob);}
                else owner->command("zzz "+owner->query("id"));
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
void greeting(object ob)
{
        if (!ob || environment(ob) != environment())
                return;
        switch(random(2)) {
        case 0 :
                say("神秘人笑眯眯地说道：这位" + RANK_D->query_respect(ob) +
                        "，快请进来看看有什么需要。\n");
                break;
        case 1 :
                say("神秘人说道：哟！这位" + RANK_D->query_respect(ob) + 
                        "您来了啊！本店有各种极品宝物出售。\n");
                break;
        }
}

