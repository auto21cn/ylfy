// chuanfu.c �ϴ���
#include <ansi.h>
inherit NPC;
void goto_matou1(object ob);
void create()
{
	set_name("�ϴ���", ({ "lao chuanfu","chuanfu" }));
	set("gender", "����");
	set("age", 56);
	set("long",
		"����һ���ϴ��򡣱�����˪������ʲôҲ����������\n",
	);
	set("combat_exp", 1000000);
	set("shen_type", 1);
	set("str",800);
	set("max_neili", 100);
	set("neili", 100);
	set("jiali", 500);
	set_skill("force", 100);
	set_skill("unarmed", 300);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	setup();
	carry_object("/clone/cloth/cloth")->wear();
}
int accept_object(object who, object ob)
{
	int time;
	object room;
	if (!room=find_object("/d/city/duchuan"))
                room=load_object("/d/city/duchuan");
	if (!room->do_check()){
		message_vision("�ϴ�����ü��$N˵���ð����Ϲ�ͷЪ��ɣ�\n", who);
		return 0;
	}
    if (ob->query("money_id") && ob->value() >= 2000)
	{
	time = ob->value() / 100;
	time = 500 / time;
	if(time < 6)
		time = 6;
        message_vision("�ϴ����$N˵���ã���λ" + RANK_D->query_respect(who) + "���ϴ��ɡ�\n" , who);
        who->move (room);
		call_out("goto_matou1", time, who) ;
       	return 1;
	}
    else  
		message_vision("�ϴ�����ü��$N˵��������Ҳ̫���˰ɣ�\n", who);
	return 0;
}
void goto_matou1(object ob)
{
   tell_object(ob, "�ɴ����ڵ����ˡ������´�����\n" ) ;
   ob->move ("/d/nanyang/matou2.c") ;
}