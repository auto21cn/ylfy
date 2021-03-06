// 动态地图怪物2

#include <ansi.h>

inherit NPC;


void create()
{
	set_name(HIY"金龙"NOR, ({ "jin long" , "long" , "dragon" }));
	set("race", "野兽");
	set("long","一条浑身闪烁的金光的巨龙，看到了你，向你扑了过来。。\n");
	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" , "claw"}) );
	set("attitude", "aggressive");
	set("max_qi",200000+random(100000));
	set("max_jing",100000+random(50000));
	set("neili",1000000+random(2000000));
	set("max_neili",500000);
	set("jiali",780);
	set("no_suck",1);
	set("dex",100);
	set("con",100);
	set("str" ,100);
	set("is_boss", 1);
	set("age", 80);
	set("combat_exp", 90000000+random(90000000));

	set("xyzx_sys/level", 100);
	set("xyzx_sys/jingzhun", 500);
	set("xyzx_sys/minjie", 500);
	set("xyzx_sys/lingxing", 500);
	set("xyzx_sys/fanying", 500);

	set_temp("apply/attack", 400);
	set_temp("apply/damage", 400);
	set_temp("apply/armor", 400);
	set_temp("apply/defence",400);
	set_skill("dodge", 1400+random(700));
	set_skill("unarmed", 1400+random(700));
	set_skill("dragon", 1400+random(700));
	set_skill("spells",1500);
	set_skill("magic-old",1500);
	map_skill("unarmed", "dragon");
	map_skill("dodge", "dragon");
	map_skill("spells", "magic-old");
	prepare_skill("unarmed", "dragon");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: perform_action, "unarmed.yaoyao" :),
		(: perform_action, "unarmed.penhuo" :),
		(: perform_action, "unarmed.tuwu" :),
		(: perform_action, "spells.magic1" :),
		(: perform_action, "spells.magic2" :),
		(: perform_action, "spells.magic3" :),
		(: perform_action, "spells.magic4" :),
		(: perform_action, "spells.magic5" :),
		(: perform_action, "spells.magic6" :),
		(: perform_action, "spells.magic7" :),
		}) );
	set("chat_chance", 10);
	set("chat_msg", ({
		(: random_move :),
		}) );
	setup();
	
	carry_object("/d/migong/obj/longdan");
}

void init( )
{	
	object ob, me;
	
	me = this_object();
    ob = this_player();
	::init();

	if ( !living(me) ) return;
    
	if ( me->is_fighting() || !playerp(ob) ) return;
	
	if( environment() && !environment()->query("no_fight") )
	{
		remove_call_out("hunting");
		call_out("hunting", 1);
	}

	//command("follow "+ob->query("id"));
}

void hunting()
{
	int i;
	object *ob;
	
	ob = all_inventory(environment());
	for(i=sizeof(ob)-1; i>=0; i--) 
	{
		if( !ob[i]->is_character() || ob[i] == this_object() || !living(ob[i]) || !playerp(ob[i]) )
			continue;
		
		kill_ob(ob[i]);
		ob[i]->fight(this_object());
		call_out("check",0);
	}
}

void check()
{
	object ob=this_object();
	object me=this_player();
	
	if (!ob)
	{
		remove_call_out("check");
		return;
	}
	
	if (!me)
	{
		remove_call_out("check");
		return;
	}
	
	if(! present(me,environment()) )
	{
		remove_call_out("check");
		return;
	}
	
	if( me->is_ghost() )
	{
		remove_call_out("check");
		return;
	}
	
	if (ob->is_busy() && ob->is_fighting())
	{
		message_vision(HIW"$N"HIW"身上圣光一闪，又恢复了行动！\n",ob,me);
		ob->interrupt_me();
		ob->start_busy(1);
	}
	
	remove_call_out("check");
	call_out("check",1+random(3));
}

void die()
{
	object ob, me, corpse, baoshi, env;
	string room;
	int m;

	ob = this_object();

	if ( !objectp(env=environment(ob)) 
		|| !stringp(room=env->query("short")) ) 
	{
		::die();
		return;
	}

	if ( ob->query_temp("last_damage_from") )
	{
		me = ob->query_temp("last_damage_from");
		m = random(45000);
		
		if ( interactive(me) )
		{
			message_vision(HIG"\n你杀死了 "+ob->name(1)+HIG" ，奖励了 "HIY+(me->query_exp_times()*m)+HIG" 点经验和 "HIY+(m/10)+HIG" 潜能。\n"NOR, me);
			me->add("combat_exp",m);
			me->add("potential",m / 10);
		}
	}
	
	if ( objectp(corpse = CHAR_D->make_corpse(ob, me)) )
		corpse->move(environment(ob));

	if ( random(100) > 80 )
	{
		baoshi = new("/clone/gem/gem");
        message_vision(HIG"\n$N在 "HIY+ob->name(1)+" 的尸体上发现了"HIW+baoshi->name(1)+"("+baoshi->query("id")+")。\n"NOR,  me);			
		baoshi->move(corpse);
	}

	COMBAT_D->announce(ob, "dead");
	destruct(ob);
	return;
}


