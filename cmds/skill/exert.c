// exert.c

#include <skill.h>
inherit F_CLEAN_UP;

static string *allow_exert = ({"regenerate", "recover", "suck", "qisuck", "neilisuck", "maxsuck", 
		"jingsuck", "jinglisuck","roar"});

int main(object me, string arg)
{
	object *env;
	string force1, force2, str1, str2;
	int i, flag;
	
	seteuid(getuid());
	
	if( !arg )
		return notify_fail("你要用内功做什麽？\n");
	
	if( environment(me)->query("no_fight") )
		return notify_fail("这里是是非之地，不可久留，别练功了，快走吧！\n");

	if (me->query("eff_qi") >= me->query("max_qi") && arg == "heal")
		return notify_fail("你现在不需要运功疗伤！\n");

	if (me->query("eff_jing") >= me->query("max_jing") && arg == "jingheal")
		return notify_fail("你现在不需要运功疗伤！\n");

	if (me->query("jing") >= me->query("eff_jing") && arg == "regenerate")
		return notify_fail("你现在精力充沛。\n");

	if (me->query("qi") >= me->query("eff_qi") && arg == "recover")
		return notify_fail("你现在气息充沛。\n");

	if (me->query("neili") <= 0)
	{
		if (me->query("neili") < 0)
			me->set("neili",0);
		
		return notify_fail("你的内力不够。\n");
	}

	if ( arg != "chong" && me->is_busy() )
		return notify_fail("( 你上一个动作还没有完成，不能施用内功。)\n");
	
	if ( file_name(environment(me)) == "/d/shaolin/bagua" && arg == "roar" )
		return notify_fail("这里不能使用内功发出巨吼！\n");

	if ( (sscanf(arg, "%*sroar%*s") || sscanf(arg, "%*sfanchang%*s"))
		&& !wizardp(me) )
	{
		env = all_inventory(environment(me));
		for ( i=0; i<sizeof(env); i++ )
		{
			if ( playerp(env[i]) && env[i] != me && env[i]->query("age") < 18 )
				return notify_fail(HIY"现场有未满18岁的新玩家，在这里使用音波功恐怕会造成误伤。\n"NOR);
		}
	}

	if ( !me->query("xy_huiyuan") )
	{
		if ( member_array(arg, allow_exert) == -1 )
			return notify_fail(HIY"只有会员才能应用内功这方面的功能。\n"NOR);
	}
	
	if (sscanf(arg,"%s %s",str1,str2)!=2)
		str1=arg;

	if ( stringp(force1 = me->query_skill_mapped("force")) 
		&& (file_size(SKILL_D(force1)->exert_function_file(str1)+".c") != -1 
			|| file_size("/binaries" + SKILL_D(force1)->exert_function_file(str1)+".b") != -1) )
		force2 = force1;
	else if ( me->query_skill("force", 1) > 0 
		&& (file_size(SKILL_D("force")->exert_function_file(str1)+".c") != -1 
			|| file_size("/binaries" + SKILL_D("force")->exert_function_file(str1)+".b") != -1) )
		force2 = "force";
	else
		return notify_fail("你所学的内功中没有这种功能。\n");

	if ( SKILL_D(force2)->exert_function(me, arg) )
	{
		flag = (int)me->query_skill(force2, 1)/500;
		flag += ((int)me->query_skill(force2, 1)/1000);
		if ( (int)me->query_skill(force2, 1) > 1500 )
			flag += (((int)me->query_skill(force2, 1)-1500)/100);
		if ( flag < 1 ) flag = 1;
		if( (int)me->query_skill(force2, 1) < 100 
			&& (int)me->query_skill(force2, 1) < (int)me->query_skill("force", 1) )
			me->improve_skill(force2, random(me->query_con()/flag)+1, 0);
		else
			me->improve_skill(force2, random(me->query_con()/flag)+1, 1);
		
		//没busy增加busy，防止技能系统没Busy的技能产生不合理的效果
		if ( !me->is_busy() && member_array(arg, allow_exert) == -1 )
			me->start_busy(1);

		return 1;
	}
	else
		return SKILL_D(force2)->exert_function(me, arg);
}

int help (object me)
{
        write(@HELP
指令格式：exert <功能名称> [<施用对象>]
用内力进行一些特异功能，你必需要指定<功能名称>，<施用对象>则可有可无。
在你使用某一种内功的特异功能之前，你必须先用 enable 指令来指定你要使用
的内功。
请参考 help force 可得知一些大部分内功都有的功能，至于你所用的内功到底
有没有该功能，试一试或参考其他说明便知。
注：如果你改变自己的内功，你原本蓄积的内力并不能直接转换过去，必须
    从０开始。
HELP
        );
        return 1;
}
