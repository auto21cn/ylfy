// By zjb@ty 写与 2002.5.18
// update by Wenwu

int main(object me)
{
	object caoyao;
	object ob;
	
	me = this_player();

	if ( !environment(me)->query("outdoors")
		|| environment(me)->query("no_fight") )
		return notify_fail("你在房间里挖个屁,要挖去外面挖!\n");

	if ( !sscanf(base_name(environment(me)),"/d/guanwai/%*s")
		&& !sscanf(base_name(environment(me)),"/d/quanzhen/%*s")
		&& !sscanf(base_name(environment(me)),"/d/gumu/%*s") )
		return notify_fail("暂时只开通关外和全真,古墓可以挖掘草药!\n");

	if ( me->is_busy() ) return notify_fail("您现在正忙,等一下再挖吧!\n");

	if ( !(ob = present("chu tou", this_player())) ) 
		return notify_fail("没锄头你挖个什么劲。\n");

	if ( environment(me)->query("wajue")>time() )
		return notify_fail("这里刚刚被人挖掘过,你等一会再来吧!\n");

	if ( me->query_temp("wajuedi") ) 
	{
		if ( me->query_temp("wajuedi") == environment(me) )
			return notify_fail(HIG"你刚刚才在这里挖掘了,还呆这里想挖什么东西?\n"NOR);
	}

	me->set_temp("wajuedi", environment(me));

	if ( random(5)>2 ) 
	{
		me->start_busy(5);
		return notify_fail(HIW"你感到好象挖到什么东西了,仔细一看原来是石块!\n"NOR);
	}
  
	if ( random(20)<5 ) 
	{
		message_vision(HIG"$N突然听到『喀嚓一声』,锄头挖断了!\n"NOR, this_player());
		destruct(ob);
		return 1;
	}
	// 主药
	if ( sscanf(base_name(environment(me)),"/d/guanwai/%*s") ) 
	{
		caoyao = new("/d/liandan/zyao/yao"+random(10));
		me->start_busy(10);
	}
	// 副药
	if ( sscanf(base_name(environment(me)),"/d/quanzhen/%*s") 
		|| sscanf(base_name(environment(me)),"/d/gumu/%*s")) 
	{
		switch(random(2))
		{
			case 0:
				caoyao = new("/d/liandan/fyao/yao");
				break;
			case 1:
				caoyao = new("/d/liandan/fyao/yao2");
				break;
		}
		me->start_busy(7);
	}
   
	if ( !me->query("env/no_msg") ) me->set("env/no_msg",1); 
	
	me->add("neili", -(me->query("neili")/10));
	me->add("qi", -(me->query("qi")/10));
	me->add("jing",-(me->query("jing")/10));
	environment(me)->set("wajue", time()+300+random(300));
	caoyao->set("zhuren",""+me->query("id")+"");
	caoyao->move(me);
	message_vision(HIR"$N拿着锄头辛苦的挖呀挖呀,好象挖到了什么,拿出来\n"
		"一看原来是"+caoyao->name()+HIR",你不由感到自己没白辛苦!...。\n"NOR, this_player());
	return 1;
}