// wukill 

// CLEAN_UP_TIMES 次心跳后清除怪物
#define CLEAN_UP_TIMES 300

#include <ansi.h>;

inherit NPC;

#include "/quest/name.h";
#include "/quest/location.h";

mapping userskills;
string username;

int give_quests();
int accountguaiexp(int turn,object who);
int guaif(int turn,object who);
int guaim(int turn,object who);
int set_guai_qi_jing(int turn,object guai);
int getexp(int turn,int level,object who);
string setguaititle(int number,object guaiob);
string randomlocation(int i1);
object load_guai_place(string file_dir);

void create()
{
	
	set_name("雾中楼", ({ "wu zhonglou", "wu","lou" }));
	set("title", HIR"杀手楼主"NOR);
	set("long", "他是杀手楼的雾中楼，据说一身修为已经达到了神的境界,你看他两眼湛然若神， 精光内敛，显然已经天人合一，返朴归真了。\n");
	set("gender", "男性");
	set("age", 800);
	set("attitude", "friendly");
	set_temp("username","fyue");
	
    set("no_suck",1);
	set("per", 100);
	set("str", 3000);
	set("int", 40);
	set("dex",500);
	set("con",500);
	set("no_accept", 1);
    set("max_qi", 30000000);
	set("max_jing", 3000000);
	set("neili", 88888888);
	set("max_neili", 40000000);
	set("max_jingli", 4000);
	set("jingli", 800000);
	set("jiali", 800000);
	set("xyzx_sys/level", 4000000);
	set("combat_exp", 50000000);
	set_skill("unarmed", 1000);
	set_skill("dodge", 1000);
	set_skill("sword", 300);
	set_skill("blade", 300);
	set_skill("parry", 300);
	set_skill("force", 300);
	set_skill("zixia-shengong", 450);
	set_skill("anranxiaohun-zhang", 1000);
	set_skill("fanliangyi-dao", 480);
	set_skill("huashan-jianfa", 400);
	set_skill("xianglong-zhang", 470);
	set_skill("dugu-jiujian", 400);
	set_skill("huashan-shenfa",460);
	set_skill("literate", 200);
	map_skill("force", "zixia-shengong");
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "dugu-jiujian");
	map_skill("sword", "dugu-jiujian");
	map_skill("blade", "fanliangyi-dao");
	map_skill("unarmed", "anranxiaohun-zhang");
	set("inquiry",([ 
		"kill":(:give_quests():),
		"放弃":"赔偿给我10两黄金，我还可以考虑考虑。\n",
		]));
	set("chat_chance", 10);
	set("chat_msg", ({
		"雾中楼抬头看了你一眼，露出一副高深莫测的样子\n",
		"雾中楼长叹一声，世上再也不会有人记得我了！。\n",
		(: command("sigh") :),
		(: command("unwield dao"):),
		(: command("unwield jian"):),
		(: command("wield dao"):),
		(: command("wield jian"):),
		(: command("exercise 100"):),
		}) );
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.poqi" :),
		(: perform_action, "sword.pozhang" :),
		(: perform_action, "sword.pojian" :),
		(: exert_function, "recover" :),
		(: exert_function, "refresh" :),
		}) );
	
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/gaochang/obj/feituoarmor")->wear();
}

void init()
{
	object who;

	::init();

	if ( interactive(who = this_player()) && !who->is_fighting() ) 
	{
		remove_call_out("greeting");
		call_out("greeting", 1, who);
	}
}

void greeting(object who)
{
	if( !who || environment(who) != environment() ) return;
	if ( (int)who->query("combat_exp") < 1000 )
	{
		switch(random(3))
		{
			case 0:command("hi "+(string)who->query("id"));break;
			case 1:command("welcome "+(string)who->query("id"));break;
			case 2:command("bow "+(string)who->query("id"));break;
			case 3:command("whisper "+(string)who->query("id")+" 要领任务? 向我打听kill的消息就可以了!");break;
		}
     
	}
	else
		say("雾中楼对"+who->query("name")+"说道:这位"+RANK_D->query_respect(who)+",别来无恙啊。\n");
	if ( random(40) > 20 )
		command("heihei "+(string)who->query("id"));
	return;
}

// 取得技能平均等级
int max_skill_level(object ob)
{  
	int s, i, maxlevel;
	string *str;
	
	userskills = ob->query_skills();
	if ( !mapp(userskills) ) 
	{
		maxlevel=3;
		return maxlevel;
	}
	str = keys(userskills);
	s = sizeof(str);
	if ( !s )
	{
		maxlevel=3;
		return maxlevel;
	}
	maxlevel = 0;
	for ( i=0; i<s; i++ )
	{
		maxlevel += userskills[str[i]];
	}
	maxlevel /= s;
	/*while ( s>0 )
	{
		s -= 1;
		i = userskills[str[s]];
		if (i>maxlevel) maxlevel=i;
	}*/
	return maxlevel;
}

int accountlevel(int turn,object ob)
{
	int level;
	
	level = max_skill_level(ob);
	level=(int)level*(70+turn*10)/100;
	return level;
}

string randomlocation(int i1)
{
   string *str1,*str2,loca;
   int i2,temp;
   str1=keys(allloca);
   str2=allloca[str1[i1]];
   i2=sizeof(str2);
   temp=random(i2);
   if (temp==0 || temp==i2) temp=1;
   loca=str2[0]+str2[temp];
   return loca;
}
      
int give_quests()
{
	object guaiob;
	object me,who,tempob;
	int chooseguai,rewardpot,rewardexp,turn;
	int giveuptime,guailevel;
	int temp,i1;
	string *strtemp, locastr, exit;

	me=this_object();
	who=this_player();

	giveuptime=who->query_temp("questtime2");
	//questbusytime=who->query_temp("questtime1");
	turn=who->query_temp("turn");
	if ( who->query_temp("kill") )
	{
		if ( time() < giveuptime )
        {      
			message_vision ("$N对$n说道：这位"+RANK_D->query_respect(who) 
				+ "，老夫不是请您去杀掉"+who->query_temp("guainame")+"吗？\n", me, who);
			return 1;
		}
        else 
			turn -= 2;
	}
	/*else
	{
		if ( time() < questbusytime )
		{
			message_vision ("$N看了看你,面带微笑的对$n说道：\n" 
				+ "这位"+RANK_D->query_respect(who)+",坏人已经除尽，不妨先去歇息。\n", me, who);
			return 1;
		}
	}*/
	//每十个怪算一轮，用turn 做参数
   if ( !turn || turn>9 || turn<0) 
	{
		who->set_temp("turn",0);
		turn=0;
	}
	turn = turn+1;
	guailevel=accountlevel(turn, who);
	guaiob=new("/quest/questguai");
	guaiob->set_heart_beat(1);
	guaiob->set("clean_up_times", CLEAN_UP_TIMES); // CLEAN_UP_TIMES 次心跳后清除怪物
	guaiob->set_temp("killername", (string)who->query("id"));
	//设置怪的jingli,neili,exp,
	guaiob->set("max_neili",guaif(turn,who));
	guaiob->set("neili",(int)(guaif(turn,who)*2));
	guaiob->set("jiali",(int)(guaif(turn,who)/800));
	guaiob->set("max_jingli",guaim(turn,who)*3);
	guaiob->set("jingli",(int)(guaim(turn,who)*3));
	guaiob->set("combat_exp",accountguaiexp(turn,who));
	guaiob->set("neili_factor",(int)(guailevel/2));
	guaiob->set("jingli_factor",(int)(guailevel/2));
	set_guai_qi_jing(turn,guaiob);
	// 设置怪物等级、属性
	guaiob->set("xyzx_sys/level", who->query("xyzx_sys/level", 1));
	/*guaiob->set("xyzx_sys/jingzhun", who->query("xyzx_sys/jingzhun", 1));
	guaiob->set("xyzx_sys/minjie", who->query("xyzx_sys/minjie", 1));
	guaiob->set("xyzx_sys/lingxing", who->query("xyzx_sys/lingxing", 1));
	guaiob->set("xyzx_sys/fanying", who->query("xyzx_sys/fanying", 1));*/
	//set guai's "long" and "title" 
	switch (random(3))
	{
		case 1 :
			guaiob->set("long","绿林人物"+guaiob->query("name") + ",听说是星宿派的高手，颇有些本领。\n");
			break;
		case 2 :
			guaiob->set("long","黑道人物"+guaiob->query("name") + "他全身散发出一丝邪气。\n");
			break;
		default :
			guaiob->set("long","武当叛徒"+guaiob->query("name") + "，他混身上下杀气逼人。\n");
	}
	chooseguai=random(7);
	setguaititle(chooseguai,guaiob);
	//rewardexp and rewardpot 是杀怪后得到的qn and exp
	rewardexp=getexp(turn,guailevel,who);
	rewardpot=rewardexp/6; 
	guaiob->set_temp("killrewardpot",rewardpot);
	guaiob->set_temp("killrewardexp",rewardexp);
	guaiob->set_temp("player",who);
	guaiob->setguaiskill(chooseguai,guailevel,guaiob);
	// guaiob->check_time(); 不用这个清除怪物
	//确定怪的位置 
	strtemp = keys(guai_place);
	i1 = sizeof(strtemp);
	temp = random(i1);
	locastr = guai_place[strtemp[temp]];
	tempob = load_guai_place(guai_place[strtemp[temp]]); // 搜索bin文件并尝试载入
	if ( objectp(tempob) )
	{
		exit = tempob->query("exits"); // 房间出口
		if ( !tempob->query("short") 
			|| !mapp(exit) 
			|| !sizeof(exit) ) // 不是地图文件或者没有出口的地图都不进行刷怪
			destruct(tempob);
	}
	//-------------------------
	//没需要的bin文件才用下面的方式获取刷怪位置，一般客户版本是bin运行的，不存在找不到bin文件的问题
	if ( !objectp(tempob) ) 
	{
		strtemp=keys(allloca);
		i1=sizeof(strtemp);
		temp=random(i1);
		if (temp==i1) temp=0;
		locastr=randomlocation(temp);  
		tempob=load_object(locastr);
	}
	//if we get a wrong path,these can help us 
	if ( !objectp(tempob) )
	{
		message_vision(HIR"$N发现好象有什么地方不对劲了，可是" + 
			"又说不上来。\nwrong room :"+locastr+"\n"NOR,who);
		return 1;
	}
	guaiob->move(tempob);
	//设置玩家的暂时参数
	//who->set_temp("questtime1",time()+50);
	who->set_temp("questtime2",time()+300);
	who->set_temp("guainame",guaiob->query("name"));
	who->set_temp("turn",turn);
	who->set_temp("kill",1);
	who->set_temp("wukill_ob", guaiob); // 用来在放弃任务时清除垃圾任务怪
	message_vision("$N哈哈大笑了几声，对$n说道：" + 
		RANK_D->query_respect(who) + "既是同道中人，我有一任务让你去完成\n", me, who);
	message_vision("$N对$n说道：现在" + HIY + "" + guaiob->query("name") 
		//+ "("+capitalize(guaiob->query("id"))+")" + NOR + "在" + HIG + strtemp[temp] + HIC 
		+ "("+guaiob->query("id")+")" + NOR + "在" + HIG + strtemp[temp] + HIC 
		+ "(" + tempob->query("short") + ")"NOR + "与我楼作对，请壮士去杀掉他！\n",me,who); 
	return 1;
}
// accountguaiexp 计算怪的经验值
int accountguaiexp(int turn,object who)
{ 
	int userexp,guaiexp;
	userexp=who->query("combat_exp");
	guaiexp=userexp;
	return guaiexp;
}
// guaif 计算怪的内力
int guaif(int turn,object who)
{
	int userneili,guaineili;
	who=this_player();
	userneili=who->query("max_neili");
	guaineili=userneili*(70+turn*5)/80;
	return guaineili;
}

int guaim(int turn,object who)
{
	int userjingli,guaijingli; 
	userjingli=who->query("max_jingli");
	guaijingli=userjingli*(70+turn*5)/80;
	return guaijingli;
}

int set_guai_qi_jing(int turn,object guai)
{
	int maxqi,maxjing;
	maxqi=200+(int)guai->query("max_neili")/3*(100+turn*20)/200;
	maxjing=200+(int)guai->query("max_jingli")/3*(100+turn*8)*4/1000;
	guai->set_temp("maxqi",maxqi);
	if ( maxqi < 50000 ) maxqi = 50000;
	if ( maxjing < 25000 ) maxjing = 25000;
	guai->set("max_qi",maxqi);
	guai->set("eff_qi",maxqi);
	guai->set("qi",maxqi);
	guai->set("max_jing",maxjing);
	guai->set("eff_jing",maxjing);
	guai->set("jing",maxjing);
	return 1;
}
//杀怪得到的exp,与玩家的skills ,exp,turn 有关
int getexp(int turn,int level,object who)
{
   int exp, my_level;

   my_level = who->query("xyzx_sys/level", 1);

  /* exp = ((level*(turn+1)>15000)?(random(15000)+5000):(level*(turn+1)))
	   + random(3000) + 1000 
	   + (random(my_level)*random(100)>15000)?(random(15000)+5000):(random(my_level)*random(100));*/
    
	//if(my_level>21000) my_level=21000;
	exp = my_level*(100+random(100));    //控制一天大概可以升20级，按6秒杀一个怪算
    if(my_level<=1000) exp *= 5;
   return exp;
}

string setguaititle(int number,object guaiob)
{
	if (random(10)>7)
	{
		if (guaiob->query("combat_exp")>2000000)
			guaiob->set("title","杀人狂魔");
		else if (guaiob->query("combat_exp")>1000000)
			guaiob->set("title","恶贯满盈");
		else if (guaiob->query("combat_exp")>500000)
			guaiob->set("title","江洋大盗");
		else if (guaiob->query("combat_exp")>100000)
			guaiob->set("title","大盗");
		else if (guaiob->query("combat_exp")>50000)
			guaiob->set("title","采花贼");     
		else if (guaiob->query("combat_exp")>10000)
			guaiob->set("title","流氓头");  
		else if (guaiob->query("combat_exp")>5000)
			guaiob->set("title","流氓");
		else  guaiob->set("title","小流氓");
	}
	else 
	{
		switch (number)
		{
			case 1 :guaiob->set("title","魔头");break;
			case 2 :guaiob->set("title","恶道");break;
			case 3 :guaiob->set("title","恶僧");break;
			case 4 :guaiob->set("title","地痞");break;
			case 5 :guaiob->set("title","恶龙");break;
			case 6 :guaiob->set("title","老魔");break;
			default :guaiob->set("title","小贼");break;
		}
	}
}

int accept_object(object me, object obj)
{
	object guai;

	if ( obj->query("money_id") && obj->value() >= 100000 )
	{
		command("say 好吧！"+me->name()+"，上次的任务就算了！");
		me->delete_temp("questtime1");
		//me->delete_temp("questtime2");
		me->delete_temp("kill");
		me->delete_temp("turn");
		if ( objectp(guai=me->query_temp("wukill_ob")) )
		{   // 清除无用任务怪
			message_vision(MAG"$N眼见情况不妙，大叫一声，溜了。\n"NOR, guai);
			destruct(guai);
			me->delete_temp("wukill_ob");
		}
		return 1;
	}
	else
		command("say ...喂....喂...！"+me->name()+"，要真有心孝敬我老人家也该拿出点诚意来才行啊！");
	return 0;
}

object load_guai_place(string file_dir)
{
	string *file, bin_dir;
	int max, get_an;

	bin_dir = "/binaries" + file_dir;
	// 没有这个目录
	if ( file_size(bin_dir) != -2 ) return 0;
	// 取得目录下的文件信息
	file = get_dir(bin_dir, -1);
	// 目录下没有文件
	if ( !(max = sizeof(file)) ) return 0;
	// 随机抽取其中一个文件
	get_an = random(max);
	// 文件是否有效
	if ( file_size(bin_dir + file[get_an][0]) <= 0 ) return 0;
	// 载入改文件，一般只有能正确编译的c文件才会产生bin文件。
	return load_object((file_dir + file[get_an][0])[0..<3]);
}