// 巡察使
#ifndef NPCDATA
#define NPCDATA "/data/npc/"
#endif
#define SHIZHE NPCDATA + "xun-cha"
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
string query_save_file()
{
    return SHIZHE;
}
int rm_file()
{
    seteuid(getuid());
    rm(query_save_file()+__SAVE_EXTENSION__);
    return 1;
}
void create()
{
    seteuid(getuid());
    if (!restore()) {
	set_name("如烟", ({ "xuncha shi", "xuncha", "shi" }) );
	set("title", HIW"武林巡察使"NOR );
	set("gender", "女性" );
	set("age", 25);
	set("long","恶人谷一大逗比，万年水货离经。\n");
	set("attitude", "heroism");
	set("winner", "NONE");
	set("no_get",1);//设置不能背走
	set("per", 27);
	set("str", 25);
	set("con", 25);
	set("int", 25);
	set("dex", 25);
	set("max_qi", 100000);
	set("max_jing", 100000);
	set("neili", 5000);
	set("max_neili", 500);
	set("jiali", 300);
	set("shen_type", 0);
	set("no_clean_up",1);
	set("xyzx_sys/level",50);
	set_skill("force",  100); 
	set_skill("unarmed",100);
	set_skill("dodge",  100);
	set_skill("parry",  100);
	set_skill("taiji-shengong",  100);
	set_skill("taiji-quan",  100);
	set_skill("tiyunzong",  100);
	map_skill("unarmed", "taiji-quan");
	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "taiji-jian");
	set("my_weapon", "/clone/weapon/changjian");
	set("my_armor", "/clone/cloth/cloth");
	setup();
	carry_object("/clone/cloth/cloth")->wear();        
    }
    else
    {
	set("id", "xuncha shi");   	
	if(!query("name"))
	    set_name("如烟", ({ "xuncha shi", "xuncha", "shi" }) );
	else 
	    set_name(query("name"), ({ "xuncha shi", "xuncha", "shi" }) );
	setup();
	if( this_object()->query("my_weapon") ) carry_object(this_object()->query("my_weapon"))->wield();
	if( this_object()->query("my_armor") )  carry_object(this_object()->query("my_armor"))->wear();        
	UPDATE_D->check_user(this_object());
    }
    set("no_suck",1);
}

void init()
{
    object me = this_object();
    object ob = this_player();
    if ( me->query("winner") == ob->query("id")
	    && me->query("age") <= ob->query("age"))
    {
	ob->set("eff_jing",ob->query("max_jing"));
	ob->set("jing",ob->query("max_jing"));
	ob->set("eff_qi",ob->query("max_qi"));
	ob->set("qi",ob->query("max_qi"));
	if (ob->query("neili")<ob->query("max_neili"))
	    ob->set("neili",ob->query("max_neili"));
	if (ob->query("jingli")<ob->query("max_jingli"))
	    ob->set("jingli",ob->query("max_jingli"));
	ob->set_temp("recover",time());
    }
    add_action("do_recopy",  "recopy");       	
    add_action("do_recover", "recover");      	
}

int accept_fight(object ob)
{
    object me, mengzhu, shangshan,player;	
    string name,pname;

    me  = this_object();
    player = this_player();
    pname=player->query("id");

    if(!( mengzhu = find_living("wulin mengzhu")) )
	if(!( mengzhu = find_object(__DIR__"meng-zhu")) )
	    mengzhu = load_object(__DIR__"meng-zhu");
    mengzhu->restore();
    name = mengzhu->query("winner");
    if( pname==name ){
	command("say 盟主大人，在下巡察使怎么是您的对手？！\n");
	return 0;
    }

    if(!( mengzhu = find_living("wulin mengzhu@new")) )
	if(!( mengzhu = find_object(__DIR__"meng-zhu-new")) )
	    mengzhu = load_object(__DIR__"meng-zhu-new");
    mengzhu->restore();
    name = mengzhu->query("winner");
    if( pname==name ){
	command("say 盟主大人，在下巡察使怎么是您的对手？！\n");
	return 0;
    }

    if(!( shangshan = find_living("shangshan shizhe")) )
	if(!( shangshan = find_object(__DIR__"shang-shan")) )
	    shangshan = load_object(__DIR__"shang-shan");
    shangshan->restore();
    name = shangshan->query("winner");
    if( pname==name ){
	command("say 你我同为使者，打架恐怕不合适？！\n");
	return 0;
    }

    if(!( shangshan = find_living("shangshan shizhe@new")) )
	if(!( shangshan = find_object(__DIR__"shang-shan-new")) )
	    shangshan = load_object(__DIR__"shang-shan-new");
    shangshan->restore();
    name = shangshan->query("winner");
    if( pname==name ){
	command("say 你我同为使者，打架恐怕不合适？！\n");
	return 0;
    }

    if(!( shangshan = find_living("fae shizhe")) )
	if(!( shangshan = find_object(__DIR__"fa-e")) )
	    shangshan = load_object(__DIR__"fa-e");
    shangshan->restore();
    name = shangshan->query("winner");
    if( pname==name ){
	command("say 你我同为使者，打架恐怕不合适？！\n");
	return 0;
    }

    if(!( shangshan = find_living("fae shizhe@new")) )
	if(!( shangshan = find_object(__DIR__"fa-e-new")) )
	    shangshan = load_object(__DIR__"fa-e-new");
    shangshan->restore();
    name = shangshan->query("winner");
    if( pname==name ){
	command("say 你我同为使者，打架恐怕不合适？！\n");
	return 0;
    }

    if ( me->query("winner") == ob->query("id") ) 
    {
	command("say 你跟你自己打什么架？！\n");
	return 0;
    }

    if (wizardp(player) && wizhood(player)!="(boss)"){
	command("say 巫师不能抢使者之位！\n");
	return 0;
    }

    if (me->is_fighting() || me->query("fighting"))
	return notify_fail("已经有人正在挑战巡察使！\n");

    me->set("eff_qi", me->query("max_qi"));
    me->set("qi",     me->query("max_qi"));
    me->set("jing",   me->query("max_jing"));
    me->set("neili",  me->query("max_neili")*2);
    remove_call_out("checking");
    call_out("checking", 1, me, ob);
    return 1;
}

int checking(object me, object ob)
{
    int my_max_qi, his_max_qi;
    object *enemy=me->query_enemy();
    if (sizeof(enemy)>1)    return 1;
    if (!ob) return 1;
    if(sizeof(ob->query_enemy())>1) return 1;
    my_max_qi  = me->query("max_qi");
    his_max_qi = ob->query("max_qi");
    if (me->is_fighting())
    {
	if ( (me->query("qi")*100 / my_max_qi) <= 80 )
	    command("exert recover");
	call_out("checking", 1, me, ob);
	return 1;
    }
    if ( !present(ob, environment()) ) return 1; 
    if (( (int)me->query("qi")*100 / my_max_qi) <= 50 )
    {
	if (!living(me))    me->revive();
	command("say 果然厉害，恭喜你成为当今武林巡察使！\n");
	command("chat 哈哈哈，到底是长江後浪推前浪，一代新人换旧人！\n");
	command("chat 恭喜" + ob->query("name") + "被推举为当今武林巡察使！\n");
	me->set("fighting",1);
	me->set("got_xun_cha_time",time());
	remove_call_out("do_copy");
	call_out("do_copy", 1, me, ob);
	return 1;
    }
    if (( (int)ob->query("qi")*100 / his_max_qi ) < 50 )
    {
	command("say 看来" + RANK_D->query_respect(ob) + 
		"还得多加练习，方能在当今武林中出人头地 !\n");
	return 1;
    }
    return 1;  
}

int do_copy(object me, object ob)
{
    seteuid(getuid());
    if (!living(me))    me->revive();
    me->set("winner", ob->query("id"));
    me->set("name",  ob->query("name") );
    me->apply_condition("killer", ob->query_condition("killer"));
    me->set("PKS",ob->query("PKS"));
    me->set("DIED",ob->query("DIED"));

    ob->delete("party/party_name");
    ob->delete("party/rank");
    ob->set("party/party_name",HIW+"武林"+ NOR );
    ob->set("party/rank",HIW+"巡察使"+NOR);
    me->set("short", HIW"武林巡察使 "HIY + me->query("name")+NOR+" (Xuncha shi)");
    me->delete("title");
    remove_call_out("do_clone");
    call_out("do_clone", 0, me, ob);
    return 1;
}

int do_recopy(object me, object ob)
{
    me = this_object();
    ob = this_player();

    if (me->is_fighting() || ob->is_fighting() || me->query("fighting"))
	return notify_fail("现在这里正打的不亦乐乎！等会吧！\n");
    if ( me->query("winner") != ob->query("id") ) 
	return notify_fail("你不是现任巡察使！\n");
    if((time()-ob->query_temp("recopy")) < 300)
	return notify_fail("状态暂时不能保存！\n");
    me->set("name",  ob->query("name") );
    me->apply_condition("killer", ob->query_condition("killer"));
    me->set("PKS",ob->query("PKS"));
    me->set("DIED",ob->query("DIED"));
    ob->delete("party/party_name");
    ob->delete("party/rank");
    ob->set("party/party_name",HIW+"武林"+ NOR );
    ob->set("party/rank",HIW+"巡察使"+NOR);
    me->set("short", HIW"武林巡察使 "HIY + me->query("name")+NOR+" (Xuncha shi)");
    me->delete("title");
    remove_call_out("do_clone");
    call_out("do_clone", 0, me, ob);
    return 1;
}

int do_clone(object me, object ob)
{
    object *inv, weapon;
    mapping hp_status, skill_status, map_status;
    string *sname, *mname;
    int i, temp;
    string skill1,skill2;
    seteuid( geteuid(me) );
    if (!living(me))    me->revive();
    /* delete and copy skills */
    if (mapp(skill_status=ob->query("weapon")))
	me->set("weapon",skill_status);
    else    me->delete("weapon");
    if ( mapp(skill_status = me->query_skills()) ) {
	skill_status = me->query_skills();
	sname  = keys(skill_status);
	temp = sizeof(skill_status);
	for(i=0; i<temp; i++) {
	    me->delete_skill(sname[i]);
	}
    }
    if ( mapp(skill_status = ob->query_skills()) ) {
	skill_status = ob->query_skills();
	sname  = keys(skill_status);
	for(i=0; i<sizeof(skill_status); i++) {
	    me->set_skill(sname[i], skill_status[sname[i]]);
	}
    }

    /* delete and copy skill maps */
    if ( mapp(map_status = me->query_skill_map()) ) {
	mname  = keys(map_status);
	temp = sizeof(map_status);
	for(i=0; i<temp; i++) {
	    me->map_skill(mname[i]);
	}
    }
    if ( mapp(map_status = ob->query_skill_map()) ) {
	mname  = keys(map_status);
	for(i=0; i<sizeof(map_status); i++) {
	    me->map_skill(mname[i], map_status[mname[i]]);
	}
    }

    /* unwield and remove weapon & armor */
    inv = all_inventory(me);
    for(i=0; i<sizeof(inv); i++) {
	destruct(inv[i]);
    }
    set("my_weapon", 0);
    set("my_armor", 0);
    /* wield and wear weapon & armor */
    inv = all_inventory(ob);
    for(i=0; i<sizeof(inv); i++) {
	if( inv[i]->query("weapon_prop/damage") > 100 
		||  inv[i]->query("armor_prop/armor") > 100
		||  inv[i]->query("shaolin")
		||  inv[i]->query("value")>100000 ) continue;
	if( inv[i]->query("weapon_prop") &&  inv[i]->query("equipped") ) {
	    if (!inv[i]->id(query("weapon/id"))){
		me->set("my_weapon", base_name(inv[i]));
	    }
	}
	else if( inv[i]->query("armor_prop") &&  inv[i]->query("equipped") ) {
	    me->set("my_armor", base_name(inv[i]));
	}
    }

    /* copy entire dbase values */
    hp_status = ob->query_entire_dbase();
    me->set("str", hp_status["str"]);
    me->set("int", hp_status["int"]);
    me->set("con", hp_status["con"]);
    me->set("dex", hp_status["dex"]);
    me->set("age", hp_status["age"]);
    me->set("max_qi",    hp_status["max_qi"]);
    me->set("eff_qi",    hp_status["eff_qi"]);
    me->set("qi",        hp_status["qi"]);
    me->set("max_jing",  hp_status["max_jing"]);
    me->set("eff_jing",  hp_status["eff_jing"]);
    me->set("jing",      hp_status["jing"]);
    me->set("max_neili", hp_status["max_neili"]);
    me->set("neili",     2*hp_status["max_neili"]);
    me->set("max_jingli",hp_status["max_jingli"]);
    me->set("jingli",    hp_status["jingli"]);
    me->set("jiali",     hp_status["jiali"]);
    me->set("gender",    hp_status["gender"]);
    me->set("combat_exp",hp_status["combat_exp"]);
    me->set("birthday",  hp_status["birthday"]);

    //保存等级制相关参数
    me->set("xyzx_sys/level",ob->query("xyzx_sys/level"));
    /*me->set("xyzx_sys/levup_exp",ob->query("xyzx_sys/levup_exp"));
    me->set("xyzx_sys/jingzhun",ob->query("xyzx_sys/jingzhun"));
    me->set("xyzx_sys/lingxing",ob->query("xyzx_sys/lingxing"));
    me->set("xyzx_sys/minjie",ob->query("xyzx_sys/minjie"));
    me->set("xyzx_sys/fanying",ob->query("xyzx_sys/fanying"));
    me->set("xyzx_sys/shuxingdian",ob->query("xyzx_sys/shuxingdian"));

    me->set("xyzx_sys/skill_dian",ob->query("xyzx_sys/skill_dian"));*/
    me->set("skillup_add",  hp_status["skillup_add"]);


    me->delete("fighting");
    if (objectp(weapon=me->query_temp("weapon"))){
	skill1=weapon->query("skill_type");
	if (objectp(weapon=me->query_temp("secondaly_weapon")))
	    skill2=weapon->query("skill_type");
    }
    if ( mapp(skill_status = me->query_skills()) ) {
	sname  = keys(skill_status);
	for(i=0; i<sizeof(skill_status); i++) {
	    command("enable unarmed "+sname[i]);
	    command("enable force "+sname[i]);
	    command("enable parry "+sname[i]);
	    command("enable dodge "+sname[i]);
	    if (stringp(skill1))
		command("enable "+skill1+" "+sname[i]);
	    if (stringp(skill2))
		command("enable "+skill2+" "+sname[i]);
	}
    }

    command("enforce max");
    command("enable unarmed liumai-shenjian");
    save();
    ob->set_temp("recopy",time());
    tell_object(ob, "状态储存完毕。\n");
    environment(me)->update_here();
    destruct(me);
    return 1;
}

int do_recover()
{
    object me, ob;	
    mapping skill_status, map_status;
    string *sname, *mname;
    int i,temp;          	
    me = this_object();
    ob = this_player();


    if (me->is_fighting() || ob->is_fighting() || me->query("fighting"))
	return notify_fail("现在这里正打的不亦乐乎！等会吧！\n");
    if ( me->query("winner") != ob->query("id")  || me->query("age")>ob->query("age")|| me->query("birthday")!=ob->query("birthday")) 
	return notify_fail("你不是现任巡察使！\n");
    if(ob->query("DIED") > me->query("DIED"))
    {
	if(ob->query("PKS") > me->query("PKS"))
	    return notify_fail("你在任职期间杀玩家"HIR+(ob->query("PKS") - me->query("PKS"))+NOR"人次，违背了"HIY"“武林领袖不得滥杀无辜“"NOR"的江湖法令,状态不能复元。\n"NOR);
    }
    if(time()-ob->query_temp("recover") < 300)
        return notify_fail("状态暂时不能复元。\n");
    if ( mapp(skill_status = ob->query_skills()) ) {
	sname  = keys(skill_status);
	temp = sizeof(skill_status);	
	for(i=0; i<temp; i++) {       	
	    ob->delete_skill(sname[i]);
	}
    }
    if ( mapp(skill_status = me->query_skills()) ) {
	sname  = keys(skill_status);
	for(i=0; i<sizeof(skill_status); i++) {
	    ob->set_skill(sname[i], skill_status[sname[i]]);
	}
    }

    /* delete and copy skill maps */
    if ( mapp(map_status = ob->query_skill_map()) ) {
	mname  = keys(map_status);
	for(i=0; i<sizeof(map_status); i++) {
	    ob->map_skill(mname[i]);
	}
    }
    if ( mapp(map_status = me->query_skill_map()) ) {
	mname  = keys(map_status);
	for(i=0; i<sizeof(map_status); i++) {
	    ob->map_skill(mname[i], map_status[mname[i]]);
	}
    }

    /* copy combat exp values */
    //读取等级制相关参数
    ob->set("xyzx_sys/level",me->query("xyzx_sys/level"));
    /*ob->set("xyzx_sys/levup_exp",me->query("xyzx_sys/levup_exp"));
    ob->set("xyzx_sys/jingzhun",me->query("xyzx_sys/jingzhun"));
    ob->set("xyzx_sys/lingxing",me->query("xyzx_sys/lingxing"));
    ob->set("xyzx_sys/minjie",me->query("xyzx_sys/minjie"));
    ob->set("xyzx_sys/fanying",me->query("xyzx_sys/fanying"));
    ob->set("xyzx_sys/shuxingdian",me->query("xyzx_sys/shuxingdian"));

    ob->set("xyzx_sys/skill_dian",me->query("xyzx_sys/skill_dian"));*/
    ob->set("skillup_add",  me->query("skillup_add"));

    //    ob->set("combat_exp", me->query("combat_exp"));
    if(me->query_condition("killer") && !ob->query_condition("killer"))
	ob->apply_condition("killer", me->query_condition("killer"));
    ob->set_temp("recover",time());
    write("状态复元完毕。\n");
    return 1;
}

int chat()
{
    object env;
    int time;
    object me=this_object();
    if(!me || me->is_fighting() || me->is_busy() || !living(me))
	return 0;
    env = environment();
    if(!env)
	return 0;
    if(me->query("winner")=="NONE")
	return 0;
    if(base_name(env) != me->query("startroom"))
	me->move(env);
    time = me->query("got_xun_cha_time");
    if(time && (time()-time)>2*60*60)
    {
	me->set("winner","NONE");
	me->set("name","如烟");
	me->clear_condition("killer");
	me->delete("PKS");
	me->delete("DIED");

	me->delete("party/party_name");
	me->delete("party/rank");
	me->delete("short");
	me->set("title",HIW"武林巡察使"NOR);
	rm_file();
	environment(me)->update_here();
	destruct(me);
    }
}
