// mao18.c éʮ��
#include <ansi.h>
inherit NPC;
int ask_weiwang();
void create()
{
	set_name("éʮ��", ({ "mao shiba", "mao", "shiba" }));
	set("gender", "����");
	set("age", 30);
	set("str", 25);
	set("dex", 16);
	set("long", "��������Ҳݣ�����Ѫ�ۣ��������ܹ����ص��ˣ����Կ��ü�\n"
            "��������Ѫ��δ�ɡ�����˫Ŀ������ȴ������˵���������硣\n");
	set("combat_exp", 35000);
	set("shen_type", 1);
	set("score", 4000);
	set("attitude", "peaceful");
        set("startroom","/d/city/lichunyuan");
	set_skill("unarmed", 50);
	set_skill("force", 60);
	set_skill("blade", 80);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set_skill("wuhu-duanmendao", 70);
	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set_temp("apply/armor", 5);
	set_temp("apply/damage", 10);
	map_skill("blade", "wuhu-duanmendao");
	set("neili", 200); 
	set("max_neili", 200);
	set("jiali", 20);
        set("inquiry", ([
		"ʷ��" : "ɱ��ʷ�ɿ�����߽���������\n",
		"����" : "ɱ���ݾ��˿�����߽���������\n",
                "����" : (: ask_weiwang :),
                "��������" : (: ask_weiwang :),
      ]) );
	set("chat_chance", 5);
	set("chat_msg", ({
		"\néʮ��˵��: �����̵ģ��ҾͲ����������������,\n"
                "����Ҫ�ϱ���ȥ����һ����\n" ,
		"\néʮ��̾��: �������廢���ŵ����Ը����ɿ��Ǵ´�����,ֻ��֪�Ը������в��С�\n",
		"\néʮ��˵��: ������������Ҫ�������ߴ��кô���...\n",
		"\néʮ��˵��: �����̵ģ�˭����ɱ��ʷ�ɣ��ֵ���лл���ˣ�\n",
		"\néʮ��˵��: ������˵�������������޵�һ��ʿ�������,\n"
                "������˵�������µ�һ��ʿ���ҿɲ�������Ҫ�ϱ���ȥ�����Ȼ��Ȼ���\n" ,
		"\néʮ������˵�����������ԣ���Ϊ�˲�ʶ�½��ϣ��ͳ�Ӣ��Ҳ��Ȼ����\n",
		(: random_move :)
	}) );
	setup();
	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}
int ask_weiwang()
{
command("tell "+this_player()->query("id")+" �����ڵĽ��������� " +(string)(this_player()->query("weiwang")));
say("\néʮ��˵�����������ֵ�ܸߣ���Щ�˼����㲻������ɱ�㣬��������书�����㱦����\n"
+"�����㻹���Լ����ᣬ�������ȥ����Ŀ�꣬����ȥǮׯȡǮҲ������Ϣ ����������\n");
say("\néʮ����˵��ɱĳЩ���˻��ĳЩ���˿�����߽���������\n");
return 1;
}
void init()
{       
	object ob; 
	ob = this_player();
	::init();
	remove_call_out("greeting");
	call_out("greeting", 1, ob);
}
void greeting(object ob)
{
if( !ob || environment(ob) != environment() ) return;
message_vision(	"\n$N���ֵ����ֵ����ϲ����㣬��������������.\n",
		this_object());
}
void die()
{
        say("\néʮ�˹�����Ц������Τ�ֵܵĸ����Ҽ����˳½����ܶ����������޺�����\n");        	 
        message_vision("$N��Ц���������ˣ�\n", this_object());
        ::die();
}
int accept_object(object me, object ob)
{
	int i;	
  	if( !me || environment(me) != environment() ) return 0;
	if ( !objectp(ob) ) return 0; 
	if ( !present(ob, me) ) return notify_fail("��û�����������");
	if ( (string)ob->query("name") == "������") 
        {
        i=(int)me->query("weiwang");
        if(i<20) 
	{
	i=i+10;
	me->set("weiwang",i);
	message_vision(HIC "\n$N�Ľ�����������ˣ�\n" NOR,this_player());
	}
	command("tell "+this_player()->query("id")+" �����ڵĽ��������� " +(string)(i));
	}
	else 
	{
		 command("shake ");
		 command("say ���ֶ�������Ҫ ! ���������� !");
		 remove_call_out("kill_ob");
		 call_out("kill_ob", 1, this_player());
	}   
     return 1;
}