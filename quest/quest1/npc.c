#include <ansi.h>
#define QUEST_SHA "/quest/quest1/quest"
inherit NPC;
inherit F_MASTER;
int time_period(int timep, object me);

void create()
{
        set_name("信差",({"postman"}));
        set("long",
                "这是一个年轻的信差，正被大堆信件包围着，看起来愁眉苦脸的样子。\n"
        );

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");
        set("age", 20);
        set("shen_type", 0);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 50);
        set("combat_exp", 30000000);
        set("score", 10000);
        set("env/wimpy", 10000);
        set("inquiry", ([
                "任务": "我正在发愁怎么处理这些信件，你来的正好! \n",
        ]) );
        set("no_get", 1);
/*
        set("chat_msg", ({
                (: random_move :)
        }) );
*/
        set_skill("force", 170);
        set_skill("dodge", 170);
//         set_skill("cuff", 175)
        set_skill("parry", 170);
        setup();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}

void init()
{
        add_action("give_quest", "quest");

}


int give_quest()
{
        mapping quest ;
        object me,letter;
        int combatexp, timep, factor;

        me = this_player();
        combatexp = (int)(me->query("combat_exp"));

if(combatexp > 150000000)
        {
                message_vision("信差对$N说：您已是武林高手了，这种小事怎敢劳您大驾？！\n",me);
                return 0;
        }
 
// Let's see if this player still carries an un-expired task
        if((quest =  me->query("quest")))
        {
                if( ((int)me->query("task_time")) >  time() ){
                message_vision("信差对$N说： 你得把信帮我送到呀。\n", me);
                        return 0;
                }
        }
                if (((int)time() - (int)me->query("last_task_time")) < 1)
                 {
                   message_vision("信差对$N说：现在连我都闲得发慌，你还是等会再来吧。\n",me);

                   return 0;
                 }
                else
                {
                   message_vision("信差对$N说：你来得正好，我这儿刚好有一批信件要送出去。\n",me);
}
        quest = QUEST_SHA->query_quest();
        timep = random(100) + 300;
        time_period(timep, me);

        tell_object(me, "把信送给『" + quest["quest"] + "』你的任务就完成了。\n" NOR);
        message_vision("$N给了$n一封信。\n",this_object(),me);
        letter = new("/quest/quest1/letter");
        letter->move(me);
        quest["quest_type"] = "把信送给";
        quest["exp_bonus"] = random(200) + 50;
        quest["pot_bonus"] = random(20) + 20;
        quest["score"] = random(10)+8;

        me->set("quest", quest);
        me->set("task_time", (int)time() + timep);
        me->set("quest_factor", factor);
        me->set("last_task_time", time());
        return 1;
}

int time_period(int timep, object me)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d)
                time = chinese_number(d) + "天";
        else
                time = "";
        if(h)
                time += chinese_number(h) + "小时";
        if(m)
                time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        tell_object(me, HIW "信差说道：\n在" + time + "内");

                return 1;
}

