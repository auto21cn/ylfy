// zhao.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
	set_name("���", ({ "zhao yi", "yi", "zhao" }) );
	set("long", "����һ����С���ߡ���ɽ�������˵�ʦ�ܡ�\n");
	set("gender", "����");
	set("class", "swordsman");
	set("age", 58);
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 30);
	set("max_qi",2000);
	set("max_jing",1200);
	set("combat_exp", 700000);
	set("shen_type", -1);

	set_skill("literate", 50);
	set_skill("unarmed", 100);
	set_skill("sword", 100);
	set_skill("force", 100);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	set_skill("songshan-jian", 150);
	set_skill("songyang-zhang", 150);
	set_skill("hanbing-zhenqi", 100);
	set_skill("lingxu-bu", 150);
	map_skill("unarmed", "songyang-zhang");
	map_skill("sword", "songshan-jian");
	map_skill("parry", "songshan-jian");
	map_skill("dodge", "lingxu-bu");
	map_skill("force", "hanbing-zhenqi");

	set("chat_chance_combat", 60);
	
	create_family("��ɽ��", 13, "����");
	setup();

carry_object("d/songshan/obj/kuojian")->wield();
	carry_object("d/songshan/obj/yellow-cloth")->wear();
}
