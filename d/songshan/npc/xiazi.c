// xiazi.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
	set_name("瞎子", ({ "xia zi", "xia", "zi" }) );
	set("long", "这就是被令狐冲刺瞎的瞎子。");
	set("gender", "男性");
	set("class", "swordsman");
	set("age", 25);
	set("attitude", "aggressive");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 30);
	set("max_qi",1000);
	set("max_jing",800);
	set("combat_exp", 100000);
	set("shen_type", -1);

	set_skill("literate", 50);
	set_skill("unarmed", 50);
	set_skill("sword", 50);
	set_skill("force", 50);
	set_skill("parry", 50);
	set_skill("dodge", 50);
	set_skill("songshan-jian", 50);
	set_skill("songyang-zhang", 50);
	set_skill("hanbing-zhenqi", 50);
	set_skill("lingxu-bu", 50);
	map_skill("unarmed", "songyang-zhang");
	map_skill("sword", "songshan-jian");
	map_skill("parry", "songshan-jian");
	map_skill("dodge", "lingxu-bu");
	map_skill("force", "hanbing-zhenqi");
	create_family("嵩山派", 14, "弟子");
	setup();

	carry_object("d/songshan/obj/kuojian")->wield();
	carry_object("d/songshan/obj/yellow-cloth")->wear();
}

