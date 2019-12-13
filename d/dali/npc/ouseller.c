// waiter.c

inherit NPC;
inherit F_DEALER;
#include <ansi.h>
void create()
{
        set_name("����Ů", ({ "cailing" }) );
        set("gender", "Ů��" );
        set("age", 11);
        set("long",
                "��λ�߾��ſ�ţ�Ц����ؿ����㣮\n");
        set("combat_exp", 500);
        set("attitude", "friendly");
        set("per",30);
        set("vendor_goods", ({
                 __DIR__"obj/ou",
        }) );
        set_skill("unarmed",50);
        set_skill("dodge",50);
        setup();
        carry_object("clone/cloth/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
/*
        if( this_player()->query_temp("dalikill") )
        {
                 kill_ob(this_player());
        }
*/
        add_action("do_kill","kill");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(10) ) {
                case 0:
message_vision("$NЦ������Ĺ��ﶼ������ź����һ�飿\n",this_object(),ob);
                        break;
        }
}
int accept_object(object me, object obj)
{
        command("smile");
        command("say ��л��λ" + RANK_D->query_respect(me) +
"����һ�����������Ŀ��ĵģ�");
        return 1;
}

int do_kill(string arg)
{
        this_player()->set_temp("dalikill", 1);
        return 0;
}