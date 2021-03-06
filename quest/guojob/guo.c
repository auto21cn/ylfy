// guojing.c 郭靖
inherit NPC;

#include <ansi.h>
//#include "zzzjob.c"
//#include "teamjob.c"

string *random_item = ({
	"/clone/map/weapon/axe",
	"/clone/map/weapon/blade",
	"/clone/map/weapon/club",
	"/clone/map/weapon/dagger",
	"/clone/map/weapon/fork",
	"/clone/map/weapon/hammer",
	"/clone/map/weapon/ring",
	"/clone/map/weapon/spear",
	"/clone/map/weapon/staff",
	"/clone/map/weapon/whip",
	"/clone/map/weapon/sword",
	});

string ask_newjob();
string ask_newover();
int job_over(string arg);

void create()
{
	set_name("郭靖", ({"guo jing", "guo", "jing"}));
	set("nickname", HIY"北侠"NOR);
	set("gender", "男性");
	set("age", 41);
	set("long", 
		"他就是人称北侠的郭靖，既是蒙古成吉思汗的金刀驸马，又是\n"
		"江南七怪、全真派马钰道长、「北丐」洪七公和「老顽童」周\n"
		"伯通等人的徒弟，身兼数门武功。他身着一件灰色长袍，体态\n"
		"魁梧，敦厚的面目中透出一股威严。\n");
	set("attitude", "friendly");
	set_max_encumbrance(100000000);
	set("xy_shoucheng",1);
	set("no_suck", 1);
	set("end_boss", 1);
	set("per", 20);
	set("str", 30000);
	set("int", 20);
	set("con", 30000);
	set("dex", 30000);
	set("no_get", 1);
	set("no_put", 1);
        set_temp("no_get",1);
        set_temp("no_kill",1);
	set("chat_chance", 1);
	set("chat_msg", ({
		"郭靖叹了口气道：“蒙古兵久攻襄阳不下，一定会再出诡计，蓉儿又不在身边，这....\n",
		"郭靖说道：“华筝公主近来不知可好，抽空一定要回大漠去看看她。\n",
//		(: random_move :),
	}));

	set("inquiry", ([
/*		"周伯通" : "你见到我周大哥了？他现在可好？\n",
		"老顽童" : "周大哥一贯这样，没点正经！\n",
		"洪七公" : "师父除了吃，就是喜欢玩。到处玩，还是为了找吃的。\n",
		"黄药师" : "那是我泰山大人。他云游四海，神龙见首不见尾的。\n",
		"一灯大师" : "在下对大师好生感激。\n",
		"欧阳锋" : "这个老毒物，害死我六位师父，一待襄阳事了，决不与他干休。\n",
		"黄蓉"   : "蓉儿是我的爱妻，你问她做甚？\n",
		"蓉儿"   : "蓉儿就是蓉儿了。你问这么多干嘛？\n",
		"郭芙"   : "这个女儿，又笨又不听话。\n",
		"郭襄"   : "襄儿生于乱世，这辈子又多艰厄。但愿她能快乐一世。\n",
		"郭破虏" : "那是我的小儿子。\n",
		"杨过"   : "过儿确实有出息。\n",
		"马钰"   : "马道长于我有半师之谊。\n",
		"丘处机" : "邱道长义薄云天，是真豪杰。\n",
		"柯镇恶" : "那是我大师父。\n",
		"朱聪"   : "那是我二师父。\n",
		"韩宝驹" : "那是我三师父。\n",
		"南希仁" : "那是我四师父。\n",
		"张阿生" : "那是我五师父。\n",
		"全金发" : "那是我六师父。\n",
		"韩小莹" : "那是我七师父。\n",
		"丐帮"   : "丐帮英雄几百年了，守卫襄阳多亏了他们。\n",
		"拜师"   : "现在蒙古人围攻襄阳，我哪有心情收徒啊！\n",
		*/
      //"job"   : (: ask_job :),
      //"功劳"  : (: ask_gonglao :),
      //"fangqi": (: ask_fangqi :),
      //"放弃"  : (: ask_fangqi :),
      //"奸细"  : (: ask_jianxi :),
           "守城" : (: ask_newjob :),
		   "功劳" : (: job_over :),
//                "job2"  : (: ask_newjob :),
     //           "撤退"  : (: ask_newover :),
		]));

	set("qi", 3000000);
	set("eff_qi", 3000000);
	set("max_qi", 3000000);
	set("jing", 3000000);
	set("eff_jing", 3000000);
	set("max_jing", 3000000);
	set("neili", 300000000);
	set("max_neili", 24000);
	set("max_jingli", 50000);
	set("jingli", 300000);
	set("jiali", 30000);
	
	set("combat_exp", 2100000000);
	set("score", 200000);
	 
	set_skill("force", 30000);		// 基本内功
	set_skill("huntian-qigong", 30000);	// 混天气功
	set_skill("unarmed", 30000);		// 基本拳脚
	set_skill("xianglong-zhang", 30000);	// 降龙十八掌
	set_skill("dodge", 30000);		// 基本躲闪
	set_skill("xiaoyaoyou", 30000);		// 逍遥游
	set_skill("parry", 30000);		// 基本招架
	
	map_skill("force", "huntian-qigong");
	map_skill("unarmed", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "xianglong-zhang");
	prepare_skill("unarmed","xianglong-zhang");
	setup();
	
	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("job_over","task");
}

string ask_newjob()
{
        object *ene;
        object me = this_player();

        if(is_fighting()) 
        {
                ene=query_enemy();
                
                if(sizeof(ene)>1) return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和这"+sizeof(ene)+"位高手切磋几下！”\n";
                if(sizeof(ene)==1) return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和"+ene[0]->name()+"切磋几下！”\n";
        }

        if(me->query_temp("mark/job_shadi")>0 ) return "“"+RANK_D->query_respect(me)+"不是已有任务了吗！”\n";

/*        if((int)me->query("shen") < 0) return "“"+RANK_D->query_respect(me)+"心术不正，我们不欢迎！”\n";
*/     
        //if ((int)me->query("combat_exp")<100000) return "“"+RANK_D->query_respect(me)+"手无缚鸡之力，还是别领任务的为好！”\n";

    if ( (int)me->query_skill("force",1) < 100 )
       return "守城是件危险工作，我看"+RANK_D->query_respect(me)+"的基本内功不足！\n";

    //if ( (int)me->query("combat_exp") < 100000 )
      // return "守城是件危险工作，我看"+RANK_D->query_respect(me)+"的经验不足！\n";

      if ((int)me->query_condition("jobshadi_failed"))
{
     message_vision("$N对着$n摇了摇头说：逃跑失败了还来见我??\n", this_object(), me);
return "“"+RANK_D->query_respect(me)+"你还是别领任务的为好！”\n";
//return;
}

      if ((int)me->query_condition("jobshadi_limit")>1)
{
     message_vision("$N对着$n摇了摇头说：你不是正做着吗??\n", this_object(), me);
	 me->set_temp("mark/job_shadi",2);
return "“"+RANK_D->query_respect(me)+"你快点回你的岗位上去！”\n";
//return;
}

if ( me->query("xyzx_sys/level") >= 500 )
		return (HIR"你已经不能再从守城任务中积累更多的经验，雾中楼那里可能需要人手你可以去试试。\n"NOR);
	/*if ( (me->query("combat_exp")+me->query("xyzx_sys/levup_exp"))/LEVUP_EXP+me->query("xyzx_sys/level") < 7 )
		return (HIR"以你目前的能力还无法担任守城重任，你还是先去通过运镖磨练下再来吧。\n"NOR);*/
   /*if ((int)me->query_condition("guojob2_busy"))
{
     message_vision("$N对着$n摇了摇头说：现在蒙古人正在攻城！！\n", this_object(), me);
return "“"+RANK_D->query_respect(me)+"你等会再来！”\n";
//return;
}*/
message("channel:chat", HIB"【朝廷急报】"GRN + "有消息说：蒙古靼子马上要侵犯襄阳了!\n"NOR,users() );
        switch( random(4) ) {
                case 0:
			me->set_temp("mark/job_shadi",1);
        	        me->set_temp("carry_location","northgate1");		
                me->apply_condition("guojob2_busy",5);
                return "“现在蒙古靼子侵犯中原，这位"+RANK_D->query_respect(me)+"去玄武内门帮助宋军守城吧。";

	               break;
                case 1:
			me->set_temp("mark/job_shadi",2);
                	me->set_temp("carry_location","northgate1");		
                me->apply_condition("guojob2_busy",5);
                return "“现在蒙古靼子侵犯中原，这位"+RANK_D->query_respect(me)+"去青龙内门帮助宋军守城吧。";

	               break;
                case 2:
                	me->set_temp("mark/job_shadi",3);
                	me->set_temp("carry_location","southgate1");
                me->apply_condition("guojob2_busy",5);
                return "“现在蒙古靼子侵犯中原，这位"+RANK_D->query_respect(me)+"去朱雀内门帮助宋军守城吧。";

	               break;
                case 3:
                	me->set_temp("mark/job_shadi",4);
                	me->set_temp("carry_location","southgate1");
                me->apply_condition("guojob2_busy",5);
                return "“现在蒙古靼子侵犯中原，这位"+RANK_D->query_respect(me)+"去白虎内门帮助宋军守城吧。";

	               break;
        	}
}

int job_over(string arg)
{
        int job_pot,job_exp, m;
        object me = this_player();
		object badguy;
		object room, baoshi;

        /*if(!arg) return 1;

        if(arg!="over") return 1;*/
	if(me->query_temp("help_killed")>0)
	{
        	message_vision(CYN "$N拍了拍$n的肩膀说道：“"+RANK_D->query_respect(me)+"，为国杀敌，不错不错！”\n" NOR, this_object(), me);
	        job_exp=((int)me->query_temp("killed_mgb"))*(100+random(100));
                  job_pot=job_exp/3;
                  job_exp=job_exp;
	        me->add("combat_exp", job_exp);
	        me->add("potential",job_pot);
tell_object(me, "你被奖励了"+chinese_number(job_exp)+"点经验值！\n"+chinese_number(job_pot)+"点潜能\n");
	        me->delete_temp("killed_mgb");        
                me->delete_temp("job_over");
                me->delete_temp("mark/job_shadi");
                me->delete_temp("help_killed");
                me->delete_temp("start_job");
        receive_wound("jing",me->query("max_jing")/10);
        receive_wound("qi",me->query("max_qi")/10);
        me->start_busy(3);
                me->apply_condition("guojob2_busy",1);
        	return 1;
        }
        	
        if(me->query_temp("mark/job_shadi")==0)
        {
                message_vision(CYN"$N瞧了$n一眼:“没任务还什么完成不完成。”\n",this_object(),me);
				me->delete_temp("killed_mgb");
				me->delete_temp("start_job");
                return 1;
        }
        
        if(me->query_temp("job_over")==0)
        {
                message_vision(CYN"$N瞧了$n一眼:“任务还没完成，还不赶快回到你的岗位上去。”\n"NOR,this_object(),me);
				me->delete_temp("killed_mgb");
				me->delete_temp("start_job");
                return 1;
        }

       if(me->query_temp("killed_mgb")<2)
       {
                  message_vision(CYN"$N瞧了$n一眼:“你杀了几个敌人，你还来领赏？还不赶快回到你的岗位上去。”\n"NOR,this_object(),me);
			me->delete_temp("killed_mgb");
         me->delete_temp("job_over");
         //me->delete_temp("mark/job_shadi");
		 me->delete_temp("start_job");
                  return 1;
          }

        message_vision(CYN "$N对$n说道：“"+RANK_D->query_respect(me)+"辛苦了，去休息一下吧！”\n" NOR, this_object(), me);
        me->delete_temp("job_over");
        me->delete_temp("mark/job_shadi");
		me->delete_temp("start_job");
        job_exp=((int)me->query_temp("killed_mgb"))*(555+random(300));
        job_pot=job_exp/3;
		if (job_exp >100000) job_exp=100000;
		if (job_pot >33333) job_pot=33333;
tell_object(me, "你被奖励了"+chinese_number(job_exp*me->query_exp_times())+"点经验值！\n"+chinese_number(job_pot)+"点潜能和50点江湖阅历。\n");
        me->apply_condition("guojob2_busy",1);
        me->add("combat_exp", job_exp);
        me->add("potential",job_pot);
        me->delete_temp("killed_mgb");        
        me->receive_wound("jing",me->query("max_jing")/10);
        me->receive_wound("qi",me->query("max_qi")/10);
        me->add("score",50);
        me->start_busy(3);
		// 物品奖励
		if ( random(100) < 5 )
		{
			m = random(sizeof(random_item));
			baoshi = new(random_item[m]);
			//if ( m < 2 )
				message("party", HIR"【任务精灵】:"+HIG"听说 "HIC+me->name(1)+HIW" 成功守御了襄阳，被奖励了"HIM" 一"+baoshi->query("unit")+baoshi->name(1)+HIW"。\n"NOR, users());	
			tell_object(me, "你获得了一"+baoshi->query("unit")+baoshi->name(1)+NOR"。\n");	
			baoshi->set("xyzx_sys/bind_type", 0);
			baoshi->move(me);
		} 
		else if ( random(100) > 85 )
		{
			baoshi = new("/quest/baoshi/baoshis/baoshi");
			tell_object(me, "你获得了一"+baoshi->query("unit")+baoshi->name(1)+NOR"。\n");	
			baoshi->set("xyzx_sys/bind_type", 0);
			baoshi->move(me);
		}
        if (random(4) == 0)
        {
message("channel:chat", HIB"【襄阳战报】"HIW + "一队宋军伤兵，退到了襄阳城中心附近!\n"NOR,users() );
		if(objectp(room=load_object("/d/xiangyang/eastjie1")) && 
		objectp(badguy = new("/quest/guojob/menggu/songbing")))
		badguy->move(room);
                room=load_object("/d/xiangyang/westjie1");
                badguy = new("/quest/guojob/menggu/songbing");
                badguy->move(room);
                room=load_object("/d/xiangyang/southjie1");
                badguy = new("/quest/guojob/menggu/songbing");
                badguy->move(room);
	}
        if (random(4) == 1)
        {
message("channel:chat", HIB"【襄阳战报】"HIW + "一队蒙古精兵，冲进了襄阳城北门附近!\n"NOR,users() );
		if(objectp(room=load_object("/d/xiangyang/dingzi")) && 
		objectp(badguy = new("/quest/guojob/menggu/mengu2")))
		badguy->move(room);
                room=load_object("/d/xiangyang/northroad1");
                badguy = new("/quest/guojob/menggu/mengu2");
                badguy->move(room);
                room=load_object("/d/xiangyang/jiekou2");
                badguy = new("/quest/guojob/menggu/mengu2");
                badguy->move(room);
                room=load_object("/d/xiangyang/dingzi");
                badguy = new("/quest/guojob/menggu/mengu3");
                badguy->move(room);
  	}
        if (random(4) == 2)
        {
message("channel:chat", HIB"【襄阳战报】"HIW + "一大队蒙古兵，冲进了襄阳城西门附近!\n"NOR,users() );
		if(objectp(room=load_object("/d/xiangyang/westjie1")) && 
		objectp(badguy = new("/quest/guojob/menggu/mengu1")))
		badguy->move(room);
                room=load_object("/d/xiangyang/westjie2");
                badguy = new("/quest/guojob/menggu/mengu1");
                badguy->move(room);
                room=load_object("/d/xiangyang/juyiyuan");
                badguy = new("/quest/guojob/menggu/mengu1");
                badguy->move(room);
                room=load_object("/d/xiangyang/westjie2");
                badguy = new("/quest/guojob/menggu/mengu1");
                badguy->move(room);
                room=load_object("/d/xiangyang/westjie2");
                badguy = new("/quest/guojob/menggu/mengu1");
                badguy->move(room);
                room=load_object("/d/xiangyang/westjie2");
                badguy = new("/quest/guojob/menggu/mengu1");
                badguy->move(room);
 	}
        if (random(4) == 3)
        {
message("channel:chat", HIB"【襄阳战报】"HIW + "有几名蒙古奸细，混进了襄阳城南门附近!\n"NOR,users() );
		if(objectp(room=load_object("/d/xiangyang/southjie2")) && 
		objectp(badguy = new("/quest/guojob/menggu/mengu4")))
		badguy->move(room);
                room=load_object("/d/xiangyang/southjie2");
                badguy = new("/quest/guojob/menggu/mengu4");
                badguy->move(room);
	}

        return 1;

}

string ask_newover()
{
         object me;
         me = this_player();
          if(me->query_condition("jobshadi_limit")<=1)
         return "你没有领任务,跑这里瞎嚷嚷什麽?";
         me->clear_condition("jobshadi_limit");
         me->add("combat_exp",-100+random(20));
         me->apply_condition("jobshadi_failed",10);
         me->delete_temp("mark/job_shadi");
	 me->delete_temp("carry_location");
         me->delete_temp("job_over");
         me->delete_temp("start_job");
	 return "没关系,下次继续努力 。";
}