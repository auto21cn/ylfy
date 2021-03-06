#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_me();
void create()
{
        set_name("琼雅蝶", ( {"qiong yadie","qiong"} ) );
        set("long","舞蝶仙传人，由于琼山与世隔绝已无从得知其来历。\n" );
        create_family("舞蝶仙", 47 , "掌门人");
        set("title",HIG"舞"HIM"蝶"HIR"仙"NOR);
        set("attitude", "peaceful");
        set("age", 35);
        set("gender", "女性");
        set("shen_type", 1);
        set("chat_chance", 1);
        set("no_drop",1);
        set("con", 30);
        set("dex", 30);
        set("int", 30);
        set("str", 30);
        set("per", 40);
        set("ker", 40);
        set("qi", 400000);
        set("max_qi", 400000);
        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("max_jingli", 10000);
        set("neili", 300000);
        set("max_neili", 300000);
        set("jiali", 100);

        set("combat_exp", 100000000);

        set_skill("dodge", 1250);
        set_skill("force", 1240);
		set_skill("taoism", 1200);
        set_skill("meinv-shenquan",1000);
        set_skill("literate",1100);
        set_skill("parry", 1050);
        set_skill("unarmed", 1050);
        set_skill("sword", 1200);
        set_skill("dieyi-jianfa", 1280);
        set_skill("wudie-xinjing", 1250);
        set_skill("wudie-bu", 1090);
        map_skill("force", "wudie-xinjing");
        map_skill("dodge", "wudie-bu");
        map_skill("parry", "dieyi-jianfa");
        map_skill("sword", "dieyi-jianfa");

        set("inquiry", ([
                "蝶翼剑法" : "蝶翼剑法唯女性弟子才能学，弟子中当数蝶青剑法最好！\n",
                "蝶青" : (: ask_me :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: command("perform wudie") :),
                (: command("exert duan") :),
        }) );


        setup();

        carry_object("d/wudie/obj/dieyi")->wear();
        carry_object("d/wudie/obj/jian")->wield();

}
void attempt_apprentice(object who)
{
        if (who->query("gender") != "女性"){
                command("say 臭男人！想上来送死吗？");
                return 0;
        }

        if ((int)who->query("per") < 25 ){         //原来的判断是!=30
                command("say 我舞碟琼山只收容色超群的女子！\n");
                return 0;
        }


        command("say 好吧！孩子，就收下你了！\n");
        command("say 舞碟琼山与世隔绝！我如果我发现你和俗世有什么瓜葛就要严处。。。\n");
        command("recruit " + who->query("id"));

}
void init()
{
   
        ::init();
        add_action("do_learn", "learn");
        add_action("do_learn", "xuexi");
}

int do_learn()
{
        object who;
        who = this_player();
        if( who->query("shen") > 1000 || who->query("shen") < -1000){
        command("say 你的神似乎不对！先自己检点一下！");
        return 1;
        }
}

int ask_me()
{
    if (this_player()->query_temp("book_4") == 2){
        if(random(1) == 0 ){
        command("sigh " + this_player()->query("id"));
        command("tell " + this_player()->query("id") + " 你是说蝶青？。。。\n
        哎！她是几年前我派的逆徒。。。打着我山庄的旗号到处为非作歹！\n
        如果你能把杀了，我一定重谢！\n
        听说他和邪派高手混在一起。");
        this_player()->set_temp("book_4",30);
        }else{
        command("tell " + this_player()->query("id") + " 你是说蝶青？。。。\n
        哎！她是我爱徒弟！几年前为师派他下山追查天书下落。。。\n
        可是她一去无归，不知生死。");
        this_player()->set_temp("book_4",31);
        }
    }else{
        command("say 你找死！");
        this_object()->kill_ob(this_player());
    }
}

int accept_object(object who, object ob)
{
        object book;
        if ((int)who->query_temp("book_4") == 44 ){
        if ( (string) ob->query("name") =="蝶青的尸体") 
        {
                message_vision("琼雅蝶仔细辨认了一下$N送来的尸体苦笑道：\n"
                               "呵！呵！呵！多谢你为本庄除去叛徒，这本书是感谢你的。\n", who);
                destruct(ob);
                book = new("/clone/book/unarmedbook");
                book -> move(this_player());
                command("rumor " + this_player()->query("name") + "得到一本无字天书！");
                return 0;

        }
        }
}




