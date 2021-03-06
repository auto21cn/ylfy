// yihua-jiemu.c 移花接木
// by King 97.05

inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
string  *msg_weapon = (
{
	YEL"$N回手一挥，想掠斜$w"YEL"来势，哪料到这么轻轻一挥之力，回击的力量竟如此大得异乎寻常！\n"NOR,
	RED"哪知$N的$W"RED"微转，平平的搭在$w"RED"之上，一股柔和的劲力送出，将$w"RED"直荡了开去！\n"NOR,
	HIY"$N向左踏出两步，右手$W"HIY"挥出，一股劲风扑向$n的后心，方位时刻拿捏得恰到好处！\n"NOR,
	HIC"$n攻出的这一招，原是极高明的招数，但被$N手指一拂，劲力又斜斜卸了开去！\n"NOR,
	BLU"$N待$n的$w"BLU"将要触及心口时，左足突然踢出，压下$w"BLU"，一借力顺势踏落！\n"NOR,
	HIB"$N双手同时施展移花接木心法，一声清啸，拔身而起，在半空中轻轻一个转折，飘然落在$n身旁！\n"NOR,
	HIW"$n武功虽高，但于$N刚猛掌力袭体而来，手中$w"HIW"再也难以拆解$N的$W"HIW"招式！\n"NOR,
	YEL"$N右手五指犹如抚琴鼓瑟，忽挑忽捻，忽弹忽拨，上身半点不动，片刻间将$n的力道尽数卸了！\n"NOR,
	GRN"$N右打出一招泰山剑法「来鹤清泉」，左手却已使出移花接木的手法，拂向$n手中$w"GRN"！\n"NOR,
	CYN"$N单伸$W"CYN"，按在$n$w"CYN"边上，依照所练的移花接木心法，微一运劲，便将$n的劲力轻轻移开了！\n"NOR,
});

string  *msg_unarmed = (
{
	HIC"一刹那间$N化刚为柔的急剧转折，已使出属移花接木心法的第七层神功！\n"NOR,
	HIW"$N动也不动，待$n进到身前，移花接木内力斜引，将$n力道挪移推卸了开去！\n"NOR,
	GRN"岂知刚刚相触，突然一股柔和而厚重的劲力从$N身上发出，挡住了$n的劲力。同时，$N右手五指也已按在$n胸口膻中穴的周遭！\n"NOR,
	RED"结果$N使出移花接木心法，依着八卦方位，倒反了$n这招的去势。\n"NOR,
	CYN"$N运使移花接木，越奔越快，如风如火，似雷似电，跟着纵身而前，左手探出抓向$n！\n"NOR,
	BLU"$N此时体内真气流转，一遇外力，自然而然而生反击，比之$n击来的力道又大得多了！\n"NOR,
	BLU"$n右手一指戳向$N肩头，却不知如何被轻轻一带，噗的一响，竟戳到了自己手臂，只痛得眼前金星直冒！\n"NOR,
	YEL"蓦地里好象旁边有一股力道飞来，将$n的力道一引，从$N身旁斜斜带过！\n"NOR,
	YEL"$N当下潜运移花接木心法，使$n击向$N的一招莫名奇妙的溜滑向一旁。\n"NOR,
	HIR"$N再使移花接木心法，一牵一引，托的一响，将$n的力道引偏。\n"NOR,
	YEL"$N右手五指犹如抚琴鼓瑟，忽挑忽捻，忽弹忽拔，上身半点不动，将$n此招化于无形！\n"NOR,
	WHT"$N巧运移花接木心法，使$n这招莫名其妙的在中途转了方向，力道化于无形！\n"NOR,
	CYN"移花接木神功变幻，何等奥妙，结果$N手指拂出，已点中了$n双腕穴道！\n"NOR,
	GRN"$N使出移花接木，$n这招莫名其妙的在中途转了方向，打出的力量向自己飞了回来！\n"NOR,
});
string *parry_msg = (
{
	"$N一招击在$n身上，却被$n暗运移花接木，将内力尽数移入地下。\n",
	"$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
	"$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
	"$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
	"$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
	"$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
	"$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
	"$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

string *dodge_msg = (
{
	"$N一招击在$n身上，却被$n暗运移花接木，将内力尽数移入地下。\n",
	"$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
	"$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
	"$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
	"$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
	"$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
	"$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
	"$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

int valid_enable(string usage)
{
	return (usage == "parry") || (usage == "dodge");
}

string query_parry_msg(string limb)
{
	return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_teach(object me)
{
	if ((int)me->query_skill("yihua-jiemu", 1) > 1)
		return notify_fail("移花接木乃移花宫宫主所创,向来不传男子。\n");
	return 1;
}
int practice_skill(object me)
{
    if( (int)me->query("qi") < 40 )
        return notify_fail("你的体力太差了，不能练移花接木。\n");
    if ((int)me->query_skill("mingyu-shengong", 1) < 120)
        return notify_fail("你的冥雨神功火候太浅，不能练移花接木。\n");
    me->receive_damage("qi", 30);
    return 1;
}
int valid_learn(object me)
{
	int lvl = (int)me->query_skill("yihua-jimu", 1);

	if ( !wizardp(this_player()) && (me->query("family/family_name") != "移花宫"))
		return notify_fail("你不是移花宫弟子不能使用冥雨神功.\n移花接木博大精深, 非移花宫弟子不传, 真不知道你是怎么学会的!\n要是让两位宫主知道了你可惨了.\n");

	if ( me->query("gender") != "女性")
		return notify_fail("移花接木乃移花宫宫主所创,向来不传男子。\n");

	if ((int)me->query_skill("mingyu-shengong", 1) < 180)
		return notify_fail("你的冥雨神功还不到家怎么能学移花接木呢？\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("就这么点基本内功还想学移花接木？\n");

	if ((int)me->query("max_neili", 1) < 15000)
		return notify_fail("就这么点内力还想学移花接木？\n");

	if ((int)me->query_skill("force", 1) < lvl)
		return notify_fail("你的基本内功火候还不够，小心走火入魔！\n");

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yihua-jiemu/"  + action;
}

int ob_hit(object ob, object me, int damage)
{
	object wp,wp1;
	string msg;
	int p,j,skill, neili, neili1, exp, exp1;
	int level2,damage2;
	wp = me->query_temp("weapon");
	wp1 = ob->query_temp("weapon");
	neili = me->query("neili");
	neili1 = ob->query("neili");
	exp = me->query("xyzx_sys/level");
	exp1 = ob->query("xyzx_sys/level");

	level2= (int) me->query_skill("mingyu-shengong",1);
	skill = me->query_skill("yihua-jiemu", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");

	damage2= (int) ob->query("neili",1)/10;
	if (random(8)==0 && level2>=300 && me->query_skill_mapped("force") == "mingyu-shengong" )
	{
		j = -damage/2;
		j = 0;
		if (damage2> 10000)	damage2=10000;
		if (damage2 < 0 ) damage2=0;
		msg = HIC+"$N运起冥雨神功 全身内力爆发，浮现出一层阴柔的劲气! !\n" +NOR;
		message_vision(msg, me, ob);
		if ( me->is_busy())
		{
			me->start_busy(1);
			ob->start_busy(2);
		}
		if (me->query("neili") > me->query("max_neili")*2)
		{

			me->add("neili", damage2);
		}

	}

	if (random(me->query_skill("mingyu-shengong",1)) > 120
	        && me->query("neili") < me->query("max_neili")
	        && me->query_skill_mapped("force") == "mingyu-shengong")

	{
		message_vision(HIR"$N运起冥雨神功，全身内力源源不断的涌出!\n"NOR,me, ob);
		me->add("neili",random(me->query_skill("jiuyang-shengong",1))+200);
	}

	if (random(me->query_skill("mingyu-shengong",1)) > 120
	        && me->query("qi") < me->query("max_qi")
	        && me->query_skill_mapped("force") == "mingyu-shengong"
	        && random(2)==0
	   )
	{
		message_vision(RED"$N运起冥雨神功，身上的伤好了很多!\n"NOR,me, ob);
		me->add("qi",random(me->query_skill("mingyu-shengong",1))+380);
		if (me->query("eff_qi") < me->query("max_qi"))
			me->add("eff_qi",random(me->query_skill("mingyu-shengong",1))+380);
	}

	if (random(me->query_skill("yihua-jiemu",1)) > 120
	        && me->is_busy()
	        && me->query_skill_mapped("force") == "mingyu-shengong"
	        && random(3)==0)
	{
		message_vision(HIC"$N暗运移花接木，本来忙乱的动作快了起来!\n"NOR,me, ob);
		me->start_busy(1);
	}
	
	if(me->query_temp("fanzhen"))
	{
		me->delete_temp("fanzhen");
		return 1;
	}
	if(me->query("jiali") && living(me) &&
	        random(exp) < exp1/3 && skill > 50 && neili > 500 && living(ob)
	        && !ob->query("env/invisibility")
	        && me->query_skill_mapped("force") == "mingyu-shengong"
	  )
	{
		if(random(2)==1) me->add_temp("fanzhen", 1);
		me->add("neili", -(random(10)));
		if(wp && wp1 && userp(me))
		{
			msg = msg_weapon[random(sizeof(msg_weapon))];
			msg = replace_string(msg, "$W", wp->name());
			msg = replace_string(msg, "$w", wp1->name());
			if(neili >= neili1*2+damage)
			{
				if(random(me->query_str(1)) > ob->query_str(1)/2 && skill > 150)
				{
					msg += HIW"结果$n一个抵挡不住，手中"+wp1->name()+HIW"脱手飞出！\n"NOR,
					       me->add("neili", -50);
					wp1->unequip();
					wp1->move(environment(ob));
					j = -5000;
				}
				else
				{
					if (damage>50)
					{
						ob->receive_damage("qi", damage/2?damage/2:10, me);
						ob->receive_wound("qi", damage/10 > 0?damage/10:2, me);
					}
					p = ob->query("qi")*100/ob->query("max_qi");
					msg += damage_msg(damage/2, "伤害");
					msg += "( $n"+eff_status_msg(p)+" )\n";
					j = -5000;
				}
			}
			else if(neili >= random(neili1)*2+damage)
			{
				msg += "结果基本上卸掉了$n的力道。\n";
				j = -5000;
			}
			else
			{
				j = damage/2+random(damage/2);
				if(j<damage/2) msg += "结果卸掉了一些$n的力道。\n";
				else msg += "结果卸掉了$n大半的力道。\n";
				j = -j;
			}
			message_vision(msg, me, ob);
			return j;
		}
		else
		{
			msg = msg_unarmed[random(sizeof(msg_unarmed))];
			if(neili >= neili1*2+damage)
			{
				if (damage>50)
				{
					ob->receive_damage("qi", damage/2?damage/2:10, me);
					ob->receive_wound("qi", damage/10 > 0?damage/10:2, me);
				}
				p = ob->query("qi")*100/ob->query("max_qi");
				msg += damage_msg(damage, "内伤");
				msg += "( $n"+eff_status_msg(p)+" )\n";
				j = -5000;
			}
			else if(neili >= random(neili1)*2+damage)
			{
				msg += "结果基本上卸掉了$n的力道。\n";
				j = -5000;
			}
			else
			{
				j = damage/2+random(damage/2);
				if(j<damage/2) msg += "结果卸掉了一些$n的力道。\n";
				else msg += "结果卸掉了$n一半的力道。\n";
				j = -j;
			}
			message_vision(msg, me, ob);
			return j;
		}
	}
}