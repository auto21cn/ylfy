//by yushu �޸�2001/2
// lilong alter 2002.01.17
#include <ansi.h>
inherit NPC;
string test_player();
mapping *poisons = ({
	([	"name": "double_ice_poison",
		"base_amount": 100
	]),
       ([	"name": "shenzhen_poison",
		"base_amount": 50
	]),
       ([	"name": "hedinghong_poison",
		"base_amount": 20
	]),
       ([	"name": "xiangsi",
		"base_amount": 20
	]),
	([	"name": "ice_poison",
		"base_amount": 50
	]),
	([	"name": "jjf_poison",
		"base_amount": 10
	]),
	([	"name": "snake_poison",
		"base_amount": 10
	]),
	([	"name": "moon_poison",
		"base_amount": 100
	]),
});

void create()
{
        set_name("��Ԩ����", ({"wuyuan daozhang", "wuyuan", "daozhang","taoist"}));
        set("age", 62);
        set("gender", "����");
        set("long",
"����۵����֣��������ɷ���ǣ�\n");
        set("attitude", "peaceful");
	 set("class", "taoist");
        set("combat_exp", 180000);
        set("shen_type", 1);
        set_skill("unarmed", 90);
        set_skill("dodge", 90);
        set_skill("parry", 90);
        set_skill("force", 90);
	
        set("neli", 400);
        set("max_neili", 400);
        set("jiali", 100);
        set("max_qi", 800);
        set("max_jing", 700);


        set("chat_chance_combat", 1);
        set("chat_msg_combat", ({
                (: cast_spell, "light" :),
                (: cast_spell, "thunder" :)
        }) );

	set("inquiry", ([
		"name": "ƶ����Ԩ���������־���ƶ����",
		"here": "ƶ����ͨҽ����Ҫ�β�(cure)Ҳ��ƶ���������Կ���",
		"cure": (: test_player :),
		"�β�": (: test_player :),
	]));

	set("chat_chance", 2);
	set("chat_msg", ({
"��Ԩ����̾���������ѣ���������Ī�ѽ������У�\n",
}) );
        setup();

        carry_object("/clone/cloth/dao-cloth")->wear();
}

string test_player()
{
	object me=this_player(), npc=this_object();
	mapping poison;
	int i;
	int amount, duration, total;

	total=0;
	message_vision(CYN "$n������֣�����$N�����ϡ�\n"NOR, me, npc);
	message_vision(CYN "����Ƭ�̣�$n����˵����\n" NOR, me, npc);
	for(i=0;i<sizeof(poisons);i++) {
		poison=poisons[i];
		duration=me->query_condition(poison["name"]);
		if(duration>0) {
			amount=poison["base_amount"]*duration;
			message_vision(CYN ""+poison["name"]+"��"+chinese_number(amount)+"������,\n" NOR, me, npc);
			total+=amount;
		}
	}
	if(me->query("eff_qi")<me->query("max_qi")) {
		duration=me->query("max_qi")-me->query("eff_qi");
		amount=duration;
		message_vision(CYN "��Ѫ��"+chinese_number(amount)+"������,\n" NOR, me, npc);
		total+=amount;
	}
	if(me->query("eff_jing")<me->query("max_jing")) {
                duration=me->query("max_jing")-me->query("eff_jing");
                amount=duration;
                message_vision(CYN "����"+chinese_number(amount)+"������,\n" NOR, me, npc);
		total+=amount;
        }
	me->set_temp("cure_payment", total);
	if(total>0) {
		message_vision(CYN "һ����Ҫ"+chinese_number(total)+"��������\n" NOR, me, npc);
		return "��ҽҩ�Ѱɣ�";
	}
	message_vision(CYN ""+RANK_D->query_respect(me)+"��û������ô�Σ�\n" NOR, me, npc);
	return "һ����ȥ��";
}

int accept_object(object who, object ob)
{
	object me = this_object();
	mapping poison;
	int total = who->query_temp("cure_payment");
	int value=ob->value();
	int duration,i;

	if(total==0) {
		command("say "+RANK_D->query_respect(who)+"���Ǹ�ʲô��");
		return 0;
	}
	if(total*100>value) {
		command("say ҽҩ��һ����Ҫ"+chinese_number(total)+"��������");
		return 0;
	}
	message_vision(CYN "$N�ͳ���֧���룬����$n���У�ӡ�ã������͹�����ϥ�������Ѩ����\n" NOR, me, who);
	message_vision(CYN "Ƭ��֮��$N������һһ���£�\n$nֻ����ɤ���۷��̣������³�һ����ʰ�쵵���Ѫ��\n" NOR, me, who);
	command("pat "+who->query("id"));
	command("say ����ˡ�");
	for(i=0;i<sizeof(poisons);i++) {
                poison=poisons[i];
                duration=who->query_condition(poison["name"]);
                if(duration>0) {
			who->apply_condition(poison["name"], 0);
                }
        }
	who->set("eff_qi", who->query("max_qi"));
	who->set("eff_jing", who->query("max_jing"));
	return 1;
}

�