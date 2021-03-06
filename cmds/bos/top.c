
#include <ansi.h>

inherit F_CLEAN_UP;

int top_list(object ob1,object ob2);
int get_score(object ob);

int main(object me, string arg)
{	
	object *list, *ob;
	string msg;
	int i, num, my_n;
	
	ob = filter_array(children(USER_OB), (: environment($1) :));
	list = sort_array(ob, (: top_list :));
	my_n = 0;

	if ( sizeof(ob) < 10 )
		num = 10;
	else
		num = sizeof(ob);

	msg =  "\n\t\t\t\t\t\t\t\t\t\t"+BBLU+HIM"【"HIY"『夕阳再现之炎龙封印』"HIR"在线高手排行榜"HIM"】\n"NOR+HIW;
	msg += "┏━━━━━━━┯━━━━━━━━━━━━━━━┯━━━━━┯━━━━━━┓\n";
	msg += "┃     名次     │         高        手         │  门  派  │  综合评价  ┃\n";
	msg += "┠───────┴───────────────┴─────┴──────┨\n";
	
	for ( i = 0; i < num; i++ )
	{
		if ( i >= sizeof(list)) 
			msg += HIW"┃暂时空缺。                                                              ┃\n";
		else
		{
			if ( list[i] == me )
			{
				msg +=HIY;
				my_n = i;
			}
			else
				msg +=HIW;
		
			msg += sprintf("┃  %-13s %-26s      %-10s   %10d ┃\n"NOR,
				chinese_number(i+1),
				list[i]->query("name") + "(" + capitalize(list[i]->query("id")) + ")",
				list[i]->query("family")?list[i]->query("family/family_name"):"普通百姓",
				get_score(list[i]));
		}
	}	
	
	msg += HIW+"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	
	if ( my_n == 0 )
		msg += NOR+YEL"◇"HIM"恭喜您，您目前正傲居榜首，乃天下第一高手是也"NOR+YEL"◇\n";
	else
		msg += NOR+YEL"◇"HIG"加油吧，您目前正位居 "HIY"第"+chinese_number(my_n+1)+"名"HIG" ，距离 "HIM"第"+chinese_number(my_n)+"名"HIG" 就差那么点点了"NOR+YEL"◇\n";

	msg += HIW"                                                   " + NATURE_D->game_time() + "记。\n"+NOR;
	
	me->start_more(msg);
	return 1;
}

int top_list(object ob1, object ob2)
{
	int score1, score2;
	score1 = get_score(ob1);
	score2 = get_score(ob2);
	return score2 - score1;
}

int get_score(object ob)	
{
	int tlvl, i, score;
	string *ski;
	mapping skills;
	reset_eval_cost();

	tlvl = 0;
	score = 0;
	
	// 没有任何技能，则技能综合评价为 1
	if ( !sizeof(skills = ob->query_skills()) )
		score += 1;
	else
	{
		// 有技能，则取技能平均等级*15为技能评价
		ski  = keys(skills);
		for ( i = 0; i < sizeof(ski); i++ )
			tlvl += skills[ski[i]];
		
		tlvl = tlvl / sizeof(ski) * 15;
		score += tlvl;
	}
	
	score += ob->query("max_neili") / 10;
	score += ob->query("max_jingli") / 5;     	
	score += ((ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con() + ob->query("kar") + ob->query("per")) * 10);	
	score += ((int)ob->query("combat_exp") / 15000);
	score += (ob->query("xyzx_sys/level") * 1000);
	score += ((ob->query("xyzx_sys/jingzhun") + ob->query("xyzx_sys/lingxing") + ob->query("xyzx_sys/minjie") + ob->query("xyzx_sys/fanying") + ob->query("xyzx_sys/shuxingdian")) * 120);
	return score;	
}	

int help(object me)	
{	
write(@HELP	
指令格式 : top 	
这个指令可以让你知道在线玩家的状态差距。	
HELP	
);
return 1;	
}	
