// m_jia.c

#include <ansi.h>
#include <armor.h>
inherit S_ROBE;

int duanlian(object weapon);
int do_hui(object weapon);
int do_jianame(string arg);

//   string query_autoload() { return 1 + ""; }      //autoload weapon	:
void init()
{
	//add_action("do_duanlian1","duanlian1");
	add_action("do_hui1","hui1");
	add_action("do_levelup","jijia");
	add_action("do_jianame","jianame");
}


void create()
{
	object me;
	string w_name,w_id,w_or;
	int w_lv;

	me = this_player();
	//读入数据
	//w_name=me->query("jia/name");
	//w_id = "my "+me->query("jia/id");
	//w_or = me->query("jia/or");
	//w_lv = me->query("jia/lv");
	if ( !objectp(me) )
	{
		w_name="自制的甲衣";
		w_id="my jia";
		w_or="千年神木";
		w_lv=1;
	}
	else
	{
		if ( !stringp(w_name=me->query("jia/name")) ) w_name="自制的甲衣";
		if ( !stringp(w_id=me->query("jia/id")) ) w_id="my jia";
		else w_id = "my "+me->query("jia/id");
		if ( !stringp(w_or=me->query("jia/or")) ) w_or="千年神木";
		if ( !(w_lv=me->query("jia/lv")) ) w_lv=1;
	}

	set("material", "fur");
	set_name(w_name, ( {w_id}));
	set("long", "这是一件用特殊材料精制的铠甲,其上似乎蕴藏着某种神奇的力量。\n");
	set("unit", "件");
	set("value",0);
	set("no_get",1);
	set("no_give",1);
	set("no_drop",1);
	set("no_tie",1);
	set("no_put",1);
	set("no_beg",1);
	set("no_zm",1);    //2015.8 添加 限制自练武器不可以镶嵌动态宝石
	set("no_steal",1);
	set("bianren",w_lv);         //  龙云梦增加于2003年12月17日
	set("ownmake",1);
	set("material", "fur");
//	set("material", "cloth");
//	set_desc(w_lv,w_or,w_name);
	switch(w_or)
	{
	case "千年神木" :
		set_weight(500);
		set("material", "fur");
		break;
	case "海底金母" :
		set_weight(1000);
		set("material", "fur");
		break;
	case "寒丝羽竹" :
		set_weight(30);
		set("material", "fur");
		break;
	default :
	}
	set("unit", "件");
	if ( objectp(me) && me->query("jia/wear_msg") )
		set("wear_msg", me->query("jia/wear_msg")+"\n");
	else
		set("wear_msg", "$N穿上"+w_name+"在身上,顿展王者霸气。\n");
	if( objectp(me) && me->query("jia/unequip_msg"))
		set("remove_msg", me->query("jia/unequip_msg")+"\n");
	else
		set("remove_msg", "$N身上的"+w_name+"脱了下来，眨眼间已然不见影踪。\n");
	set("armor_prop/armor", w_lv * 10);
	set("armor_type","cloth");
	set("material", "fur");
	setup();
}

int do_hui1(object weapon)
{
	string w_name;
	object me;
	me=this_player();
	w_name=me->query("jia/name");
	if( !weapon )
		return notify_fail("你要摧毁什么?\n");
	message_vision(HIR "$N大喝一声，一掌擎甲，一掌猛力击下。结果轰隆一声巨响"
	               +w_name+HIR"断为两截!\n" NOR,me);
	me->set("jia/make",0);
	destruct( this_object() );
	me->delete("weapon");
	me->delete("diablo/cloth");
	me->save();

	return 1;
}

int do_levelup(string arg)
{
	object me, ob;
	object gold;
	int cost = 1;
	int j;
	string id;
	me = this_player();
	id = me->query("id");
	j = (int)me->query("jia/lv");
	if( !arg ) return notify_fail("你要提升什麽神甲？\n");
	gold = present("gold_money", this_player());
	if( !gold) return notify_fail("你身上没有金子。\n");
	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n");
	if(me->is_busy())
		return notify_fail("你上一个动作还没有完成。\n");
	if( ob->query("equipped") )
		return notify_fail("你不可提升装备著了的神甲。\n");
	if( !ob->query("ownmake") )
		return notify_fail("你只可提升自己打造的神甲。\n");
	if( (int)me->query("qi") < 150 )
		return notify_fail("你的气不够，无法锻炼神甲！\n");

	if( (int)me->query("eff_qi") < 30 )
		return notify_fail("你现在的体力太弱，无法锻炼神甲！\n");

	if( (int)me->query("eff_jing") < 10 )
		return notify_fail("你现在的精力无法集中，不能锻炼神甲！\n");
	if( (int)me->query("score") < 100 * j )
		return notify_fail("你现在的江湖阅历不够，不能锻炼神甲！\n");

	if( ((int)me->query("potential") - (int)me->query("learned_points"))< 5000 *j )
		return notify_fail("你的潜能不够，无法锻炼神甲！\n");

	if(j<6) cost = 15*j;
	else if(j<11) cost = 20*j;
	else if(j<16) cost = 30*j;
	else if(j>500) cost = 500*j;
	else cost = 100*j;
	if((int) gold->query_amount() < cost)
		return notify_fail("你身上没带够" + sprintf("%d",cost)+ "两金子。\n");
	gold->add_amount(-cost);
	me->start_busy(2);
	me->add("bellicosity",cost);
	seteuid(ROOT_UID);
	me->add("qi",-150);
	me->add("eff_qi",-30);
	me->add("jing",-30);
	me->add("eff_jing",-30);
	me->add("score",-100 * j);
	me->add("potential",-5000 * j);
	me->set("jia/lv", j+1);
	me->save();
	reload_object(ob);
	message_vision(HIY "甲身忽的一亮，一道金光隐入$N的"+ob->name()+HIY"，不见了！\n" NOR,me);
	message_vision(HIG "$N的"+ob->name()+HIG"的等级提高了！\n" NOR, me);
	seteuid(getuid());
	return 1;
}
int do_jianame(string arg)
{
	object me;
	me=this_player();
	if( !arg )
		return notify_fail("你改什么的名字?\n");
	if (this_object()->query("bianren") > me->query("jia/lv"))
		return notify_fail("你只能改自己护甲的名字!\n");
	if( strlen(arg) > 100 )
		return notify_fail("你的护甲名称最多只能设置五十个字符。\n");
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);
	me->set("jia/name",arg+NOR);
	set("name",arg+NOR);
	write("ok!\n");
	this_object()->create();
	return 1;
}
