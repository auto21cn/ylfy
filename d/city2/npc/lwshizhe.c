// lwshizhe.c 送礼使者

// 定义这次礼物标识
#define THIS_GIFT_ALL "1001_gift"
// 定义上次礼物标识
#define LAST_GIFT_ALL "0925_gift"
// 发放装备等级
#define GIST_ITEM_LEVEL 15

inherit NPC;
inherit F_MASTER;

#include <item_sx.h>

string *random_item = ({
	"/clone/map/weapon/axe",
	"/clone/map/weapon/blade",
	"/clone/map/weapon/club",
	//"/clone/map/weapon/dagger",
	//"/clone/map/weapon/fork",
	"/clone/map/weapon/hammer",
	//"/clone/map/weapon/ring",
        "/clone/map/weapon/staff",
	"/clone/map/weapon/whip",
	"/clone/map/weapon/sword",
	"/clone/map/weapon/spear",
	});

int gift_item(string str);
int ask_yuebing(string str);
int ask_qiankun(string str);

void create()
{
	set_name(HIC"节日礼物使者"NOR, ({ "gift shizhe", "shizhe" }));
	set("title", HIW"小天使"NOR);
	set("nickname", HIG"碧云神女"NOR);      	
	set("str", 37);
	set("gender", "女性");
	set("age", 14);
	set("per",30);
	set("long", "这是一个美丽动人的小姑娘，大大的眼睛里闪着无限的热情。\n 她在这里专门给大家发送节日礼物。\n");
	set("combat_exp", 15000000);
	set("max_qi", 3000000);
	set("max_jing", 3000000);
	set("neili", 15000000);
	set("jiali", 50000);
	set("no_get", 1);	
	set("attitude", "friendly");
	set("inquiry", ([
		"黄金会员装备": "如果您是黄金会员，可以通过指令 "HIM"draw weapon 装备编号[0～7]"NOR
		" 领取一件三星紫装武器。\n"HIW"装备类型对应编号如下：\n"HIY
		"斧(0)、刀(1)、棍(2)、锤(3)、杖(4)、鞭(5)、剑(6)、枪(7)\n"NOR,
		//"国旗": (: ask_yuebing :),         
        "乾坤袋" : (: ask_qiankun :),		
		]));
    
	setup();
	carry_object("/clone/cloth/female1-cloth")->wear();	
}

void init()
{
	object ob;

	ob = this_player();

	if ( !ob ) return;

	add_action("gift_item", "draw");
}

int gift_item(string arg)	
{
	object me, shizhe, gift, *inv;
	string name, *item;
	int i, max, type;

	me = this_player();
	shizhe = this_object();

	if ( !me || !shizhe ) return 0;
	/*if ( me->query("xyhy_type") != 2 )
	{ // 不是黄金会员
		tell_object(me, "只有黄金会员才能领取装备\n");
		return 1;
	}*/
	if ( !arg || sscanf(arg, "weapon %d", type) != 1 )
	{ // 检查命令格式
		tell_object(me, "领取装备命令格式：draw weapon 装备编号[0～7]\n"
						HIW"装备类型对应编号如下：\n"HIY
						"斧(0)、刀(1)、棍(2)、锤(3)、杖(4)、鞭(5)、剑(6)、枪(7)\n"NOR);
		return 1;
	}
	if ( type < 0 || type > sizeof(random_item)-1 )
	{ // 检查编号范围
		tell_object(me, "领取装备命令格式：draw weapon 装备编号[0～7]\n"
						HIW"装备类型对应编号如下：\n"HIY
						"斧(0)、刀(1)、棍(2)、锤(3)、杖(4)、鞭(5)、剑(6)、枪(7)\n"NOR);
		return 1;
	}
	if ( sizeof(all_inventory(me)) > 50 )
	{ // 检查包裹物品数量
		tell_object(me, "你身上的东西太多了无法再装下更多的物品，整理好行囊再来领吧！\n");
		return 1;
	}

	// 取得具体装备
	gift = new(random_item[type]);
	// 取得装备可能的所有属性项
	item = keys(weapon_shuxing);
	max = sizeof(item);
	for ( i=0; i<max; i++ )
	{
		gift->set("weapon_prop/"+item[i], GIST_ITEM_LEVEL*100); // 设置常规属性
	}
	//_______________________设置特殊属性______________________
	gift->set_weight(3000 + (random(max) * 100) + (random(GIST_ITEM_LEVEL) * 100)); // 重量
	gift->set("value", 5000000 + (random(max + GIST_ITEM_LEVEL) * 1000000)); // 价值
	gift->set("weapon_prop/level", GIST_ITEM_LEVEL*2); // 等级
	gift->set("flag", 2); // 设置为单手武器
	gift->set("no_get", 1);
	gift->set("no_put", 1);
	gift->set("no_drop", 1);
	gift->set("no_sell", 1);
	gift->set("no_give", 1);
	gift->set("no_tie",1);
	gift->set("bind_master_level/"+me->query("id"), 1); // 设置绑定等级
	//___________________________ END _________________________
	//________________________更改名称_____________________
	name = gift->name(1);
	name = filter_color(name);
	gift->set("name", MAG"☆☆☆"HIY+name+"★VIP★"NOR); // 更改名称
	gift->set("xyzx_item/pinji", 3); // 设置为紫装
	//__________________________END________________________

	if ((int)me->query_encumbrance() + gift->weight() > (int)me->query_max_encumbrance() )
	{ // 检查负重情况
		tell_object(me, "礼物包对你而言太重了，还是先整理好行囊再来领吧！\n");
		destruct(gift);
		return 1;
	}
	/*if ( !wizardp(me) && me->query(THIS_GIFT_ALL) )
	{ // 每 ID 只能领取一次
		tell_object(me, "对不起哦，每个人只可以领取一次，你已经领过了哦。\n");
		destruct(gift);
		return 1;
	}*/
	inv = all_inventory(me);
	for ( i=0; i<sizeof(inv); i++ )
	{
		if ( inv[i]->query("bind_master_level/"+me->query("id")) 
			&& inv[i]->query("xyzx_item/pinji")==3 )
		{ // 身上有则不能再次领取
			tell_object(me, "对不起哦，你身上已经有一把了。\n");
			destruct(gift);
			return 1;
		}
	}
	
	message_vision(YEL"$N伸出纤纤玉指优雅地一拂变出一"+gift->query("unit")+gift->name(1)+"送给了$n\n"NOR, shizhe, me);
	gift->move(me);
	//_______________________标志领取领取状态________________________
	me->delete(LAST_GIFT_ALL);
	me->set(THIS_GIFT_ALL, 1);
	//_____________________________ END _____________________________
	return 1;
}

int ask_yuebing(string arg)	
{    
	object me;
	object shizhe;	
	object gift;
	
	me = this_player();
	shizhe = this_object();

	if ( !me || !shizhe ) return 0;
	if ( me->query("071001_gift") )     	
	{ // 已经领过了
		tell_object(me, "你不是已经领过国旗了，怎么还来拿？\n");
		return 1;
	}

	message_vision(CYN "送礼特使拿出一面国旗送给了$N \n" NOR, me);
	gift = new("/clone/misc/guoqi");
	gift->move(me);	      	
	me->delete("07815_gift");
	me->set("071001_gift", 1);
	return 1;
}

int ask_qiankun(string arg)	
{
	object me,obj;
	object shizhe;
	me = this_player();
	shizhe=this_object();
	if ( sizeof(all_inventory(me)) > 50 )
	{ // 检查包裹物品数量
		tell_object(me, "你身上的东西太多了无法再装下更多的物品，整理好行囊再来领吧！\n");
		return 1;
	}
	if(present("qiankun dai", me))
	{
		command("say 已经有了还想拿,你怎么如此贪得无厌呢?");
		return 1;
	}
	else
	{
		message_vision(CYN "礼物使者微笑着拿出个乾坤袋，送了给$N \n" NOR,me);
		obj=new("/clone/misc/qiankun-dai.c");
		obj->set("xyzx_sys/bind_type", 2);
		obj->set("xyzx_save_item", 1);
		obj->move(me);
		command("love");
		return 1;
	}
}
