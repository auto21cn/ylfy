// dunjia_sense.c
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

	if ( me->is_fighting() ) return notify_fail(HIM "战斗中你没有时间施用神通！\n" NOR);
	//if ( me->query_condition("killer") ) return notify_fail("官府已设下天罗地网,使用飞天御剑术不是自寻死路?\n");
	if  (environment(me)->query("no_fly")) return notify_fail("你现在可是在监狱里耶，也妄想使用神通？\n");
	if ( present("biao yin",me) ) return notify_fail(HIM "你身上带着镖银，无法使用神通！\n" NOR);
	//if ( present("xin",me) ) return notify_fail(HIM "你身上带着信件，无法使用神通！\n" NOR);
	obj = deep_inventory(me);
	for ( i=0; i<sizeof(obj); i++ )
	{
		if ( obj[i]->id("illicit salt") )
			return notify_fail(HIM "你身上带着私盐，无法使用神通！\n" NOR);
	}
	ob = first_inventory(me);
	while ( ob )
	{
		if ( ob->is_character() && !ob->is_corpse() )
			return notify_fail(HIM ""+ob->name()+"不能和你一起御剑飞行！\n");
		ob = next_inventory(ob);
	}
	if ( me->query("jing") < 30 || me->query("jingli") < 75 )
		return notify_fail(HIM "你的精力不够,无法集中念力！\n" NOR);
	if ( target ) return notify_fail(HIM "奇门遁甲只能自己使用！\n" NOR);
	if ( me->query_temp("gamble") ) return notify_fail("你还是先下完这把再走吧!\n");
	write(HIM "你要飞遁到哪一个人身边？" NOR);
	if ( virtualp(environment(me)) ) return notify_fail("这里无法使用神通!\n");
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
		write(HIM "中止施法。\n" NOR);
		return;
	}
	ob = find_player(name);
	if ( !ob || !me->visible(ob) || wizardp(ob) ) ob = find_living(name);
	if ( !ob || !me->visible(ob) || !living(ob) || wizardp(ob) )
	{
		write(HIM "你集中念力静心感应，似乎感觉不到这个人的存在。\n" NOR);
		return;
	}
	if ( !objectp(env=environment(ob)) )
	{
		write(HIM "你集中念力静心感应，似乎感觉不到这个人的存在。\n" NOR);
		return;
	}
	if ( random(me->query("jing"))<30 || random(me->query("jingli"))<20 )
	{
		write(HIM "你集中念力静心感应，似乎精力不够脑中一片空白。\n" NOR);
		return;
	}
	if ( me->query("quest/quest_type")=="杀"
	        && (string)me->query("quest/quest")==ob->short()
	        && me->query("quest/task_time") < time() )
	{
		write(HIM "你集中念力静心感应，隐约感应到了什么。突然任务精灵出现挥手斩断了你的念力。\n" NOR);
		return;
	}
	if ( ob->query("id")=="salt seller" || virtualp(environment(ob)) )
	{
		write(HIM "你集中念力静心感应，只觉脑中一片空白 ....\n" NOR);
		return;
	}
	if ( me->is_fighting() )
	{
		write(HIM "战斗中你没有时间施用神通,呵呵！\n" NOR);
		return;
	}
	else if ( me->query("jingli") < 75 )
	{
		write(HIM "现在你的精神状态不太好，无法聚集念力！\n" NOR);
		return;
	}
	me->add("jingli", -75);
	me->receive_damage("jing", 30);

	if ( /*random(ob->query("jingli")) > (int)me->query("jingli") || */time() - me->query_temp("do_flee") < 1 )
	{
		message_vision( HIM "$N手捏剑诀，漫天飘起七彩花瓣一道剑光望空而去 ....\n" NOR, me);
		write(HIM "你纵升半空，一股强大的力量把你强扯回地面，你只觉脑中一片茫然！\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	me->set_temp("do_flee",time());
	if( !environment(ob) ||
	        environment(ob)->query("no_magic") || me->query_skill("taoism",1) < 800 || me->query_skill("buddhism",1) < 650 || me->query_skill("qimen-flee",1) < 300 )
	{
		write(HIM "你手捏剑诀望空一纵，升得半丈来高已然把持不住一交摔了下来，脑中一片茫然！\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	exits=environment(ob)->query("exits");
	if (!mapp(exits) || !sizeof(exits) )
	{
		write(HIM "你脑中灵光一闪似乎感应到了什么，但又一片茫然！\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="shaolin"
	        || domain_file(base_name(environment(ob)))=="new"
	        || domain_file(base_name(environment(ob)))=="mingjiao"
	        || domain_file(base_name(environment(ob)))=="shenlong"
	        || domain_file(base_name(environment(ob)))=="wizard"
	        || domain_file(base_name(environment(ob)))=="death" )
	{
		write(HIM "那里佛气好重，非尔等微末道行所能及！\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="party" )
	{
		write(HIM "那里是人家的帮派，随便闯进去不挨打才怪?\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if(ob->query("id")=="zhang tianshi")
	{
		write(HIM "在天师面前施展道法，岂不是班门弄斧?\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="taohuacun" )
	{
		write(HIM "那里是人家的私宅，想进去偷东西啊?\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="huashan" )
	{
		write(HIM"一股强大的煞气将你挡了回来.......！\n"NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="migong" )
	{
		write(HIM "一股强大的煞气将你强行扯回地面，没门.....！\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="wudujiao" )
	{
		write(HIM "那里毒气好重，恐怕是有去无回！\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
//        message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
//        return;
//    }
	if ( domain_file(base_name(environment(ob)))=="player" )
	{
		write(HIM "那里是人家的家里，你想做贼吗？\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="kefang%d" )
	{
		write(HIM "那里是人家的睡觉的地方，你想做贼吗？\n" NOR);
		message( "vision",HIM+me->name()+"从半空急坠而下，模样狼狈之极。\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="changan" )
	{
		write(HIM "你被一股强大的煞气挡了回来！\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下,脸色似乎不太好看！\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="flypproom" )
	{
		write(HIM "你被一股强大的煞气挡了回来！\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下,脸色似乎不太好看！\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="yihua" )
	{
		write(HIM "你自忖尚无通天彻地之能！\n" NOR);
		message( "vision",HIY+me->name()+"从半空悻悻落下,脸色似乎不太好看！\n" NOR, environment(me),( {me}));
		return;
	}
	if ( domain_file(base_name(environment(ob)))=="xiakedao" || domain_file(base_name(environment(ob)))=="miwudao")
	{
		write(HIM "你自忖尚无飞洋渡海之能！\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下,脸色似乎不太好看！\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="gaochang" || domain_file(base_name(environment(ob)))=="automap")
	{
		write(HIM "你自忖道行尚未达到畅游乾坤的境界。\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下，颜色似乎不太好看。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="city3" )
	{
		write(HIM "你自忖道行尚未达到畅游乾坤的境界。\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下，脸色似乎不太好看。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="mingjiao" )
	{
		write(HIM "你自忖道行尚未达到畅游乾坤的境界。\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下，脸色似乎不太好看。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( domain_file(base_name(environment(ob)))=="heimuya" || domain_file(base_name(environment(ob)))=="gumu")
	{
		write(HIM "你自忖道行尚未达到畅游乾坤的境界。\n" NOR);
		message( "vision",HIM+me->name()+"从半空悻悻落下，脸色似乎不太好看。\n" NOR, environment(me),( {me}));
		return;
	}

	if (!environment(ob) || wizardp(ob))
	{
		message_vision( HIM "$N手捏剑诀道声 ∮=起=∮，漫天飘起七彩花瓣一道剑光望空而去 ....\n" NOR, me);
		write(HIM "你御剑飞行半天，发现"+ob->name()+"似乎遥在天上,非自己道行所能及 ....\n" NOR);
		message( "vision",HIM+me->name()+"御飞剑在半空转了几转悻悻落回地面，一副呆头呆脑的样子。\n" NOR, environment(me),( {me}));
		return;
	}

	if ( userp(ob) )
	{
		message_vision( HIM "$N手捏剑诀道声 ∮=起=∮，漫天飘起七彩花瓣一道剑光望空而去 ....\n" NOR, me);
		write(HIM "你御剑飞行半天，发现荧荧矿空既然毫无边际 ....\n" NOR);
		message( "vision",HIM+me->name()+"御飞剑在半空转了几转悻悻落回地面，一副呆头呆脑的样子。\n" NOR, environment(me),( {me}));
		return;
	}

	message_vision( HIM "$N手捏剑诀道声 ∮=起=∮，漫天飘起七彩花瓣一道剑光望空而去 ....\n" NOR, me);
	message( "vision", HIM "\n七色花瓣随着剑光远去逐渐飘散消失，" + me->name() + "已远在天边凝成一个黑点！\n\n" NOR, environment(me), ( { me }) );

	for ( i=0; i<sizeof(stop_maps); i++ )
	{
		if ( domain_file(base_name(environment(ob))) == stop_maps[i] )
		{
			write(HIM "但是，很快地你发现那里似乎无法到达，于是又悻悻地落了下来。\n" NOR);
			return;
		}
	}

	if(file_size(file_name(environment(ob))+".c")<=0 && file_size("/binaries" + file_name(environment(ob))+".b")<=0)
	{
		write(HIM "但是，很快地你发现那里似乎并不存在，于是又悻悻地落了下来。\n" NOR);
		return;
	}
	else me->move(environment(ob));
	write(HIM "漫天飘起七彩花瓣，你御行飞剑徐徐从空降了下来。\n" NOR);
	message( "vision", HIM "\n满空飘起七彩花瓣，一道炫亮剑光从天而降！\n\n" NOR,
	         environment(ob), ( { me }) );
	if (me->query_skill("taoism",1)>me->query_skill("qimen-flee",1))
		me->improve_skill("qimen-flee", random(me->query_skill("taoism")),0);
	else me->improve_skill("qimen-flee", random(me->query_skill("taoism")),1);
}

