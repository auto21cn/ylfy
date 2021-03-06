// drift_sense.c
#include <ansi.h>
//inherit SSERVER;

nosave string *stop_maps = (
{
	"shushan",
	"xuehepai",
	"xuantian",
	"tongchi",
	"cxwxm",
	"hainan",
	"longmen",
	"wudie",
	"liandan",
});

int conjure(object me, object target)
{
	object ob,*obj;
	int i;

	if ( me->is_fighting() ) return notify_fail("战斗中你没有时间打洞,呵呵！\n");
	//if ( me->query_condition("killer") ) return notify_fail("官府已设下天罗地网,钻洞不是自寻死路?\n");
	if  ( !environment(me)->query("outdoors") ) return notify_fail("嘣！嘣！嘣！这里的地板，似乎好硬哟！\n");
	if ( present("biao yin",me) ) return notify_fail("你身上带着镖银，无法使用神通！\n");
	//if ( present("xin",me) ) return notify_fail("你身上带着信件，无法使用神通！\n");
	obj = deep_inventory(me);
	for ( i=0; i<sizeof(obj); i++ )
	{
		if (obj[i]->id("illicit salt"))
			return notify_fail("你身上带着私盐，无法使用神通！\n");
	}
	ob = first_inventory(me);
	while ( ob )
	{
		if (ob->is_character() && !ob->is_corpse() )
			return notify_fail(ob->name()+"不能和你一起钻洞！\n");
		ob = next_inventory(ob);
	}
	if ( me->query("jing") < 30 || me->query("jingli") < 75 ) return notify_fail("你的精力不够！\n");
	if ( target ) return notify_fail("奇门遁术只能自己使用！\n");
	if ( me->query_temp("gamble") ) return notify_fail("你还是先下完这把再走吧!\n");
	if ( virtualp(environment(me)) ) return notify_fail("这里无法使用神通!\n");
	write("你要钻到哪一个人身边？");
input_to( (: call_other, __FILE__, "select_target", me :));
	return 1;
}

void select_target(object me, string name)
{
	object ob, env;
	mapping exits;
	int i;

	if ( !name || name=="" )
	{
		write("中止施法。\n");
		return;
	}
	ob = find_player(name);
	if ( !ob || !me->visible(ob) || wizardp(ob) ) ob = find_living(name);
	if ( !ob || !me->visible(ob) || !living(ob) || wizardp(ob) )
	{
		write("你无法感受到这个人的精力 ....\n");
		return;
	}
	if ( !objectp(env=environment(ob)) )
	{
		write("你无法感受到这个人的精力 ....\n");
		return;
	}
	if ( random(me->query("jing"))<30 || random(me->query("jingli"))<20 )
	{
		write("你无法感觉到对方的存在\n");
		return;
	}
	if ( me->query("quest/quest_type")=="杀"
	        && (string)me->query("quest/quest")==ob->short()
	        && me->query("quest/task_time")<time() )
	{
		write("你无法感受到这个人的精力 ....\n");
		return;
	}
	if	( ob->query("id")=="salt seller"
	        || virtualp(environment(ob)) )
	{
		write("你无法感受到这个人的精力 ....\n");
		return;
	}
	if ( me->is_fighting() )
	{
		write("战斗中你没有时间打洞,呵呵！\n");
		return;
	}
	else if( me->query("jingli") < 75 )
	{
		write("现在你的精神状态不太好，歇会吧！\n");
		return;
	}
	me->add("jingli", -75);
	me->receive_damage("jing", 30);
	if ( random(ob->query("jingli")) > (int)me->query("jingli")
	        || time() - me->query_temp("do_flee") < 1 )
	{
		message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
		write("咚咚几声，你挖到几块大石头，哇，没门！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	me->set_temp("do_flee",time());
	if ( !environment(ob) || environment(ob)->query("no_magic")
	        || environment(ob)->query("no_fight")
	        || random(me->query_skill("qimen-flee",1)) < 30 )
	{
		write("你手指都磨破了，才挖出个老鼠洞，MY GOD，怎么钻呀！\n");
		message( "vision",HIY+me->name()+"使劲把脸往土里蹭了几下，真无聊。\n" NOR, environment(me),( {me}));
		return;
	}
	exits=environment(ob)->query("exits");
	if (!mapp(exits) || !sizeof(exits) )
	{
		write("你挖到一堵石墙，不得不退了回来！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="shaolin"
	        || domain_file(base_name(environment(ob)))=="new"
	        || domain_file(base_name(environment(ob)))=="mingjiao"
	        || domain_file(base_name(environment(ob)))=="shenlong"
	        || domain_file(base_name(environment(ob)))=="wizard"
	        || domain_file(base_name(environment(ob)))=="death" )
	{
		write("那里佛气好重，非道术所能及！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="changan" )
	{
		write("咚咚几声，你挖到几块大石头，哇，没门！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="party" )
	{
		write("你无法感受到这个人的精力.....！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="huashan" )
	{
		write("咚咚几声，你挖到几块大石头，哇，没门！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="wudujiao" )
	{
		write("那里毒气好重，恐怕是有去无回！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
//        message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
//        return;
//    }
	if ( domain_file(base_name(environment(ob)))=="player" )
	{
		write("那里是人家的家里，你想做贼吗？\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="kefang%d" )
	{
		write("那里是人家的睡觉的地方，你想做贼吗？\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="migong" )
	{
		write("咚咚几声，你挖到几块大石头，哇，没门！\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="taohua" || domain_file(base_name(environment(ob)))=="miwudao")
	{
		write("恭喜你，你挖到了泉水哩！\n");
		message( "vision",HIY+me->name()+"从口了吐出几口水大叫：好咸呀！\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="yihua" )
	{
		write("恭喜你，你挖到了茅坑哩！\n");
		message( "vision",HIY+me->name()+"从口了吐出几口大粪大叫：好臭呀！好臭呀！\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="flypproom" )
	{
		write("恭喜你，你挖到了茅坑哩！\n");
		message( "vision",HIY+me->name()+"从口了吐出几口大粪大叫：好臭呀！好臭呀！\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="xiakedao" )
	{
		write("恭喜你，你挖到了茅坑哩！\n");
		message( "vision",HIY+me->name()+"从口了吐出几口大粪大叫：好臭呀！好臭呀！\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="gaochang" )
	{
		write("那里太遥远了。\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="city3" )
	{
		write("那里太遥远了。\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="mingjiao" || domain_file(base_name(environment(ob)))=="automap" )
	{
		write("那里太遥远了。\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="heimuya" || domain_file(base_name(environment(ob)))=="gumu")
	{
		write("那里太遥远了。\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}

	if (!environment(ob) || wizardp(ob))
	{
		message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
		write("你在地底钻了半天，发现"+ob->name()+"似乎在天上 ....\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	if(ob->query("id")=="zhang tianshi")
	{
		message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
		write("你在地底钻了半天，发现"+ob->name()+"似乎在天上 ....\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}

	if( userp(ob) )
	{
		message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
		write("你在地底钻了半天，发现似乎不着边际 ....\n");
		message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),( {me}));
		return;
	}
	message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
	message( "vision", HIY "\n很快，洞口又封了起来，" + me->name() + "不见了！\n\n" NOR, environment(me), ( { me }) );

	for ( i=0; i<sizeof(stop_maps); i++ )
	{
		if ( domain_file(base_name(environment(ob))) == stop_maps[i] )
		{
			write("但是，很快地你发现那里似乎无法到达，于是又灰头土脸地退了回来。\n");
			return;
		}
	}

	if(file_size(file_name(environment(ob))+".c")<=0 && file_size("/binaries" + file_name(environment(ob))+".b")<=0)
	{
		write(HIY"但是，很快地你发现那里似乎并不存在，于是又灰头土脸地退了回来。\n"NOR);
		return;
	}
	else me->move(environment(ob));
	message( "vision", HIY "\n一个黑影突然从地下冒了出来，喷了你满脸的灰！\n\n" NOR,
	         environment(ob), ( { me }) );
	if (me->query_skill("taoism",1)>me->query_skill("qimen-flee",1))
		me->improve_skill("qimen-flee", random(me->query_skill("taoism")),0);
	else me->improve_skill("qimen-flee", random(me->query_skill("taoism")),1);
}

