//Npc: /u/lots/npc/mahan.c
// Date: LOTS 98/10/14

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("马汉", ({
		"ma han",
		"ma",
		"han",
	}));
	set("long",
		"这是一个高大威猛的汉子,因为久在官场做事,脸上已磨练的毫无表情.\n"+
		"他正在开封府前等你来告状\n"
	);


	set("nickname", "御前四品带刀侍卫");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "officer");

	set("age", 30);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 3500);
	set("max_qi", 3500);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 150);
	set("combat_exp", 5000000);
	set("score", 1000000);

// before the modification, all the skills are 120
	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("hunyuan-yiqi", 300);
	set_skill("shaolin-shenfa", 300);
	set_skill("unarmed", 300);
	set_skill("hanbing-mianzhang", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("xiuluo-dao", 300);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "hanbing-mianzhang");
	map_skill("unarmed", "hanbing-mianzhang");
	map_skill("blade", "xiuluo-dao");

	set("chat_chance_combat", 95);

	setup();

	carry_object("d/kaifeng/obj/silverblade")->wield();
	carry_object("clone/cloth/yayifu")->wear();
}

