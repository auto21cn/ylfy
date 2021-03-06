
/*
 * create by evilgod@xbtxii
 * Last change by rongg@xbtxIII 2001/1/15
 * 更改了关于队伍做quest的奖励办法
 */
#include <ansi.h>
#include <dbase.h>
int time_period(int timep, object me);

void fail_quest(object me)
{
        return;
}
void questbonus(object me)
{
        me->set("quest/fealty",1);
}

int cancel_quest(object who,object ob)
{         
        if(ob->value()>random(who->query("per")*100)+100)
        {
        	who->set_temp("quest/exp",0);
                who->set_temp("quest/pot",0);
                who->set_temp("quest/score",0);
                who->set("quest",0);
                message_vision("$N向$n一甩袍袖，说道：真没用！这都干不了\n",this_object() ,who);
                return 1;
        }
        else message_vision("$N大怒喝道：你就算想贿赂也要多一点"+
                             "才行啊!这点钱算什么意思？\n",this_object());
        return 0;
}

string * choice_quest(string tag)
{
        string *quest,ext;
        
        if(!stringp(ext=query("quest_ext"))) ext="";
                
        if(random(2)<1)
        {
            quest = ({"杀"});
            if(file_size("/quest/qlist"+tag+"kill"+ext+".c") >= 0)
                 quest+= ({ "/quest/qlist"+tag+"kill"+ext});
            else quest+= ({ "/quest/qlist"+tag+"kill"});
        }
        else if(random(2)==3)
        {
            quest = ({"胜"});
            if(file_size("/quest/qlist"+tag+"npc"+ext+".c") >= 0)
                 quest+= ({"/quest/qlist"+tag+"npc"+ext});
            else quest+= ({ "/quest/qlist"+tag+"npc"});
        }
        else 
        {
            quest = ({"寻"});
            if(file_size("/quest/qlist"+tag+"obj"+ext+".c") >= 0)
                 quest+= ({"/quest/qlist"+tag+"obj"+ext});
            else quest+= ({ "/quest/qlist"+tag+"obj"});
        }
        return quest;

}
int give_quest()
{
        string quest_type;
        string quest,* quest_file;
        object me,ob;
        int j, combatexp, timep,factor,num;
        string tag = "1000000";
        string *levels = ({
                        "0",
                        "1",
                        "2",
                        "4",
                        "8",
                        "16",
                        "32",
                        "64",
                        "128",
                        "256",
                        "512",
                        "1024",
        });
        me = this_player();
        ob = this_object();
// Let's see if this player still carries an un-expired task

        if(me->query("family/family_name")!=ob->query("family/family_name"))
        {
                message_vision("$N拱手作揖,很有礼貌的对$n说：「 欢迎大侠光临，还请多多指教! 」\n", ob,me);
                command("say 怎敢劳动大侠出手，大侠别开玩笑了");
                return 1 ;
        }
        if((quest =  me->query("quest")))
        {
                if( ((int) me->query("task_time")) >  time() )
                       return 0;
                else
                {
                       message_vision("$N向$n一甩袍袖，说道："
                               "真没用！不过看在你还回来见我的份上，就在给你一次机会．\n", ob,me);
                       me->set("kee", me->query("kee")/2+1);
                       me->set_temp("quest/score",0);
                       me->set_temp("quest/exp",0);
                       me->set_temp("quest/pot",0);
                }
        }
        combatexp = (int) me->query("combat_exp")/1000;

        for(j= sizeof(levels) - 1 ; j>=0; j--)
        {
                if( atoi(levels[j])  <= combatexp )
                        {
//                              tag = levels[j];
                                num=j;
                                factor=10;
                                break;
                        }
        }
        if (num>0)
        {
                if (random(50+me->query_kar())>65)
                {
                        num=num-1;
                }
        }
        else 
        {
                if ((num<sizeof(levels)-1)&&(random(100)>95))
                {
                        num=num+1;
                        factor=15;
                }
        }
        tag=levels[num];
        quest_file=choice_quest(tag);
        quest_type=quest_file[0];
        quest=quest_file[1]->query_quest();
    	while (quest_type == "杀")
	{
		if(quest==this_object()->name()||quest==me->query("family/master_name"))
		{
        		quest_file=choice_quest(tag);
        		quest_type=quest_file[0];
                        quest=quest_file[1]->query_quest();
		}
		else
			break;
	}	        
        
        timep = random(me->query_kar()*6)+random(me->query_int()*2)
                +random(me->query_spi()*5)+random(me->query_per()*5)
                +400-random(me->query_skill("force",1));
        time_period(timep, me);
        if (quest_type == "寻")
        {
                tell_object(me,"找回『"+quest+"』给我。\n" NOR);
        }
        if (quest_type == "杀")
        {
                tell_object(me,"替我杀了『"+quest+"』。\n" NOR);
        }
        if (quest_type == "胜")
        {
        	tell_object(me,"替我教训『"+quest+"』一下。\n" NOR);
        }
        questbonus(me);
        me->set("quest/name", quest);
        me->set("quest/type", quest_type);
        me->set("task_time", (int) time()+timep);
        me->set("quest_factor",factor);
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

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        tell_object(me,HIW +this_object()->name()+"沉思了一会儿，说道：\n请在" + time + "内");
        return 1;
}
int accept_object(object who, object ob)
{
        int exp, pot, score,factor,i;
        object me,*member;
        string quest;
        me=this_object();
        if(! who->query("quest")||!(quest =  who->query("quest")["name"])||userp(ob))
        {
                tell_object(who,me->name()+"说道：这不是我想要的。\n");
                return 0;
        }

        //if(me->query("family/family_name")!=who->query("family/family_name"))
        //        return 0;
        if (ob->query("money_id")&&ob->name(1) != quest)
        {
                return cancel_quest(who,ob);
        }

        if( ob->name(1) != quest)
        {
                tell_object(who,me->name()+"说道：这不是我想要的。\n");
                return 0;
        }
        if (!ob->query("money_id")) call_out("todest",3,ob);
        if ((int) who->query("task_time") < time() )
        {
                fail_quest(who);
                tell_object(who,me->name()+
                        "说道：真可惜！你没有在指定的时间内完成！\n");
                who->set_temp("quest/score",0);
                who->set_temp("quest/exp",0);
                who->set_temp("quest/pot",0);
                return 1;
        }
        else
        {
                
                exp = random(who->query_skill("parry")/4)
                      +random(who->query_skill("dodge")/4)
                      +random(40)
                      +random(who->query_skill("force")/4)+2;
                pot = random(who->query_con()/2)+random(who->query_kar()/2)+random(20)+1;
                score = random(exp+pot*2);
                factor=who->query("quest_factor");
                if (exp>120) exp= 120;
                if (exp<12) exp= 12;
                if (pot>18) pot = 18;
                if (pot<3) pot = 3;
                // zjun


		if(pointerp(member=who->query_team()))//关于队伍完成quest之后获得奖励
        	{				//关于教训和战胜对手的队伍奖励参见/adm/daemons/reward.c
                	who->set("quest", 0 );
                	for(i=0;i<sizeof(member);i++)
                	{
                        	if(member[i]->query("combat_exp")>=3000000)
                        	{//叫who的队员做的quest,那么其他队员可以获得的奖励=队员(who)的本次奖励
                                	member[i]->add_temp("quest/exp",exp);
                                	member[i]->add_temp("quest/pot",pot);
                                	if( member[i]->query_temp("quest/exp")> 720) 
  	                        		member[i]->set_temp("quest/exp",720);
                        		if( member[i]->query_temp("quest/pot")> 81) 
	                                	member[i]->set_temp("quest/pot",81);

        	                }
                	        else
                        	{
                                	member[i]->add_temp("quest/exp",exp);
                                	member[i]->add_temp("quest/pot",pot);
                                	if( member[i]->query_temp("quest/exp")> 1500) 
	  	                        	member[i]->set_temp("quest/exp",1500);
        	                	if( member[i]->query_temp("quest/pot")> 150) 
                	                	member[i]->set_temp("quest/pot",150);
                        	}
                		
                        	member[i]->add("combat_exp",member[i]->query_temp("quest/exp"));
                        	member[i]->add("potential",member[i]->query_temp("quest/pot"));
                        	member[i]->add("fealty",member[i]->query("quest/fealty"));
                        	//me->delete("quest");
                        	//为了鼓励玩家的合作态度,这里不删除成员的人物标记
                        	//就是说当任何一个成员完成quest之后,大家都获得相同的奖励,并且允许所有的成员
                        	//同时做任务
	                        tell_object(member[i],"恭喜你！你的队伍又完成了一项任务！\n");
        	                tell_object(member[i],HIW"你被奖励了：\n" 
                                  +chinese_number(member[i]->query_temp("quest/exp")) + "点实战经验\n"
                                  +chinese_number(member[i]->query_temp("quest/pot")) + "点潜能\n"NOR);
        	
                	}	
        		return 1;
        	}
        

		tell_object(who,me->name()+"说：恭喜你！你又完成了一项任务！\n");
                who->add_temp("quest/exp", exp);
                who->add_temp("quest/pot",pot);
                if(who->query("combat_exp")>=3000000)
                {
                        if( who->query_temp("quest/exp")> 720) 
  	                       who->set_temp("quest/exp",720);
                        if( who->query_temp("quest/pot")> 81) 
                               who->set_temp("quest/pot",81);
                }
                else 
                {
                        if( who->query_temp("quest/exp")> 1500) 
  	                       who->set_temp("quest/exp",1500);
                        if( who->query_temp("quest/pot")> 150) 
                               who->set_temp("quest/pot",150);
                }     
                who->add("combat_exp", (int) who->query_temp("quest/exp"));
                who->add("potential",(int) who->query_temp("quest/pot"));
                who->add_temp("quest/score",score);
                who->add("score", (int) who->query_temp("quest/score"));
                who->add("fealty",(int)who->query("quest/fealty"));
                tell_object(who,HIW"你被奖励了：\n" +
                chinese_number(who->query_temp("quest/exp")) + "点实战经验\n"+
                chinese_number(who->query_temp("quest/pot")) + "点潜能\n" +
                chinese_number(who->query("quest/fealty"))+"点师门忠诚度。\n"NOR);
                who->set("quest", 0 );
        }
        
        return 1;
}
void todest(object ob)
{
	destruct(ob);
}


