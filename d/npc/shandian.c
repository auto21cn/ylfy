// shandian.c 闪电
inherit NPC;

void create()
{
        set_name(HIW"闪电"NOR, ({ "shan dian", "shandian", "dian" }));        
        set("title", YEL"四大名捕之三"NOR"「"WHT"电"NOR"」");
        set("gender", "男性");
        set("age", 25);
        set("str", 30);
        set("per", 30);
        set("dex", 30);
        set("long", "他，就是闻名天下的四大名捕中的老三，为人疾恶如仇，性格刚烈。\n");
		set("combat_exp", 2100000000);  
        set("xyzx_sys/level", 3000000);			
        set("attitude", "peaceful");
		set("no_suck",1);
		set("end_boss", 1);
		set("max_jing", 35500000);  	
        set("max_qi", 35500000);  	
        set("neili", 113500000);          	
        set("shen_type", 0);
        set("max_neili", 24000000); 
        set("jiali", 275000); 
		
		set_temp("apply/attack", 1160);
        set_temp("apply/defense", 1160);
        set_temp("apply/armor", 1160);
        set_temp("apply/damage", 1160);
		
		set_skill("unarmed", 51340);	
		set_skill("force", 51340);	
		set_skill("sword", 51340);	
		set_skill("qimen-wuxing", 21350);     	
		set_skill("qufeng", 21350);     	
		set_skill("dodge", 51500);	
		set_skill("parry", 51340);	
		set_skill("taiji-shengong", 21340);	
		set_skill("taiji-jian", 21340);	
		set_skill("taiji-quan", 21340);	
		set_skill("shenxing-baibian", 21500);	

        map_skill("force", "taiji-shengong");
        map_skill("sword", "taiji-jian");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("dodge", "shenxing-baibian");
        prepare_skill("cuff","taiji-quan");
		
        set("chat_chance_combat", 100);	
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :),
                (: exert_function, "heal" :),
            }) ); 
       
        set("chat_chance",4);
        set("chat_msg",({
     WHT"闪电"HIY"哼了一声，说道：“有四大名捕在，谁也不要杀人...谁要是杀了人给我找麻烦，就让他妈的去坐牢！”\n"NOR,
     WHT"闪电长啸一声，怒气冲冲地说道：“我平生最痛恨的就是那些胡乱杀人取乐的疯子，要是让我碰上了，哼~！杀无赦！！！”\n"NOR,
        (: random_move :)
        }));
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/armor/tiejia")->wear();
}
void init()
{
        object ob;
        ::init();
        if (!living(this_object())) return;
		add_action("do_go","go");
        if (interactive(ob = this_player())){
                        if ( (int)ob->query_condition("killer")) {
                    command("say "+ob->name()+"，你杀了人，还想往哪逃？！");
					this_object()->set_leader(ob);
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
                                        return ;
                }
                if (  !ob->query_temp("armor/cloth") && ob->query("race")=="人类" 
                   && ((int)ob->query_temp("summon_time")+400)< time() ) {
                remove_call_out("summon_ob");
                call_out("summon_ob", 1, ob);
                                return;
        }
            add_action("do_kill","kill");
        }

}
void summon_ob(object ob)
{
    object room;
    if (!ob || environment(ob)!=environment())
            return;
        if (! room=find_object("/d/city/jianyu"))
            room=load_object("/d/city/jianyu");
        message_vision("\n$N一把抓住$n，光天化日，当街裸跑，有伤风化！\n\n",this_object(),ob);
        message_vision("$N拎着$n向衙门走去！\n",this_object(),ob);
        ob->move(room);
    ob->set_temp("summon_time",time());
    message("vision",YEL+"\n\n当啷一声，一个赤条条的家伙被扔了进来。\n\n"+NOR,room,({ob}));
        if (! room=find_object("/d/city/yamen"))
            room=load_object("/d/city/yamen");
        //this_object()->move(room);
}

int do_kill(string arg)
{
        object ob;
      if (!environment()) return 0;
        if (ob=present(arg,environment()))
        if (userp(ob)){
            command("say 想在大爷面前撒野？找死呀！");
            kill_ob(this_player());
        }
    return 0;
}

int do_go(string arg)
{
        mapping exit;
        if( !mapp(exit = environment()->query("exits")) || undefinedp(exit[arg]) )
                return 0;
        if (is_killing(this_player()))
                if (random(10)<=5) {
                        message_vision(YEL "$N见势不好，转身要走，被$n"+YEL+"一把拦在面前。想走？没那么容易！\n"NOR, this_player(), this_object());
						this_player()->start_busy(1);
                        return 1;
                        }
        return 0;
}

