// beg.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string what, who;
	object ob, victim;
	mapping myfam, vtfam;
	int sp, dp;
        
	seteuid(getuid());
	
	if ( (!(myfam = me->query("family")) || myfam["family_name"] != "丐帮") )
		return notify_fail("只有乞丐才能乞讨！\n");
	if ( environment(me)->query("no_beg") || environment(me)->query("no_fight"))
		return notify_fail("这里不是你叫化子能来讨饭的地方！\n");
	if ( me->query_temp("begging") )
		return notify_fail("你已经在向人家乞讨了！\n");
	if ( !arg || sscanf(arg, "%s from %s", what, who)!=2 ) 
		return notify_fail("指令格式：beg <物品> from <人物>\n");
	
	victim = present(who, environment(me));
	
	if ( !victim || victim == me) return notify_fail("你想乞讨的对象不在这里。\n");
	if ( !living(victim) || !objectp(victim)) return notify_fail("你要向谁乞讨？\n");
	if ( (vtfam = victim->query("family")) && vtfam["family_name"] == "丐帮" )
		return notify_fail("你不能向乞丐乞讨！\n");
	if ( !wizardp(me) && wizardp(victim) ) return notify_fail("玩家不能向巫师乞讨。\n");
	if ( me->is_fighting() ) return notify_fail("一边打架一边要饭？你真是活腻了！\n");
	if ( victim->is_fighting() ) return notify_fail(victim->name() + "正在打架，没空理你！\n");
	if ( !ob = present(what, victim) ) 
	{
		object *inv;
		inv = all_inventory(victim);
		if ( !sizeof(inv) ) return notify_fail( victim->name() + "身上看起来没有什麽让你感兴趣的东西。\n");
		ob = inv[random(sizeof(inv))];
	}
	if ( ob->query("equipped") || ob->query("no_drop") )
		return notify_fail("这是那人的随身家伙，肯定不会给你。\n");
	
	sp = (int)me->query_skill("begging") * 15 
		+ (int)me->query_kar() 
		- (int)me->query("begger") 
		+ me->query("combat_exp") / 1000 
		+ me->query("xyzx_sys/level") * 1000;
	
	if ( sp < 1 ) sp = 1;
	
	dp = (int)victim->query("jing") 
		+ victim->query("combat_exp") / 1000 
		+ victim->query("xyzx_sys/level") * 1000 
		+ (int)victim->query_per();
	
	tell_object(me, "你装出可怜巴巴的样子，慢慢地向" + victim->name() + "走过去，伸出双手，想要"
		+ ob->query("unit") + ob->name() +"...\n\n");
	tell_object(victim, me->name() + "可怜巴巴地向你慢慢走过来，伸出手，说道：" + RANK_D->query_respect(victim) + "行行好，给我" 
		+ ob->query("unit") + ob->name() + "吧 ...！\n\n");
	message("vision", "只见" + me->name() + "装出可怜巴巴的样子，慢慢地向" 
		+ victim->name() + "走过去，\n伸出双手，说道："
		+ RANK_D->query_respect(victim) + "，行行好吧 ...\n\n", environment(me), ({ me, victim }) );
	me->set_temp("begging", 1);
	call_out( "compelete_beg", 3, me, victim, ob, sp, dp);
	return 1;
}

protected void compelete_beg(object me, object victim, object ob, int sp, int dp)
{
	int amount;
	object ob1;
	object where;
	
	if ( !me ) return;
	
	me->delete_temp("begging");
	where = environment(me);
	
	if ( !victim )
	{
		tell_object(me, "太可惜了，你要乞讨的人已经走了。\n");
		return;
	}
	if ( !where 
		|| (!wizardp(me) && where->query("no_fly")) )
	{
		tell_object(me, "这里不是你叫化子能来讨饭的地方！\n");
		return;
	}
	if ( environment(victim) != environment(me) ) 
	{
		tell_object(me, "太可惜了，你要乞讨的人已经走了。\n");
		return;
	}
	if ( !ob || (playerp(me) && !playerp(victim)) )
	{
		tell_object(me, "对方好象很吝啬耶!\n");
		return;
	}
	if ( !living(victim) )
	{
		tell_object(me, "很显然，"+victim->name()+"正躺着，不会理你。\n");
		return;
	}
	if ( playerp(me) && me->query_temp("apply/name") )
	{
		tell_object(me, victim->name()+"瞪了你眼，摇了摇头嘀咕道：“这是谁呀？”\n");
		return;
	}
	if ( victim->query("shen") < -5000 )
	{
		message_vision(victim->name() + "狠狠地瞪了$N一眼，喝道：“妈辣给巴子，既然要饭要到" 
			+ RANK_D->query_self_rude(victim) 
			+ "头上来了。”\n", me);
		me->fight_ob(victim);
		victim->kill_ob(me);
		return;
	}
	if ( random(sp) > dp ) 
	{
		if ( ob->query("money_id") )
		{
			amount = ob->query_amount();
			if ( amount < 5 )
			{
				tell_object(me, "看来还是走吧，这家伙身上已经没有多少油水可榨了。\n");
				return;
			}
			ob->set_amount(amount - amount/5);
			ob1=new("/clone/money/" + ob->query("money_id"));
			ob1->set_amount(amount/5);
			ob1->move(me);
		}
		else if ( !ob->move(me) ) 
		{
			ob->move(where);
			tell_object(me, "你讨到一" + ob->query("unit") + ob->name() 
			+ "，可是对你而言太重了，不得丢在地下。\n");
			return;
		}
		tell_object(me, victim->name() + "低头想了一会，又看了看你，摇摇头，叹了口气，丢给你一" 
			+ ob->query("unit") + ob->name() + "。\n");
		tell_object(victim, "你看着" +  me->name() +"的可怜样，叹了口气，丢给他一" 
			+ ob->query("unit") + ob->name() + "。\n");
		me->improve_skill("begging", random(me->query("int")));
		me->add("potential", 1, 1);
		me->add("combat_exp", 1, 1);
		if ( random(sp) < dp/2 )
			message("vision", "你看到" + victim->name() + "冲着" + me->name() + "满脸不屑地摇摇头，"
				+ "丢给他一" + ob->query("unit")
				+ ob->name() + "！\n", environment(me), ({ me, victim }) );
		me->start_busy(6);
	} 
	else 
	{
		if ( random(sp) > dp/2 ) 
		{
			message_vision(victim->name() + "狠狠地瞪了$N一眼，喝道：滚！ $N吓了一跳，急忙扭头灰溜溜地走开了。\n", me);
			me->add("begger", 1);
			return;
		}
		tell_object(me, victim->name() + "扭过头去，对你理都不理。\n");
		tell_object(victim, "你扭过头去，对" + me->name() + "理都不理。\n");
		message("vision", victim->name() + "扭过头去，对" + me->name() + "理都不理。\n", 
			environment(me), ({ me, victim }) );
		me->start_busy(3);
	}
}

int help(object me)
{
write(@HELP
指令格式 : beg <某物> from <某人>
HELP
    );
    return 1;
}

