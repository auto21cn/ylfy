//actionavailable.c
//优化增加全列表菜单，使操作更简单更适合新手上手


#define TMA "\x19" //ASCII码25
#define TMB "\x1A" //ASCII码26
#define TMI(x) (TMA+x+TMB)

#include <ansi.h>

inherit F_CLEAN_UP;

#include <item_sx.h>

string wuse_name(string str);
int room_path(object, object, int);
int user_path(object, object, int);
int skill_path(object, string);

int main(object me, string arg)
{
	object ob, *inv, room;
	string id, *ids, *id_list, num, id1, id2, new_id;
	int win, i, m, v, k;

	m = 0;
	k = 0;

	if ( !stringp(arg) ) return 0;
	if ( me->query("xieyi/zmud")) return 0;
	if ( sscanf(arg, "%s,%d", id, win) != 2 ) return 0;

	if ( !sscanf(id, "%s %s", id1, id2) )
	{
		new_id = id; // 不是特殊处理时的，传入的 id 就是 new_id
		v = 0;
	}
	else
	{
		id_list = explode(id , " ");
		if ( !stringp(num = id_list[sizeof(id_list)-1]) ) return 0; // 未知的类型，则直接退出

		if ( !(v = atoi(num)) ) new_id = id; // 不符合特殊处理的格式，则认为 new_id 还是原来的 id
		else new_id = replace_string(id, " "+v, ""); // 是特殊处理的格式，我们重新获得正确的 id(new_id)
	}
	// 我们把传入的常规格式命令看作是指向首位置的特殊格式命令
	if ( !v )
		v = 1;

	switch ( win )
	{
		// 同环境下菜单
		case 0 :
				// 检查 me 是否有环境，没有则直接返回
				if ( !objectp(room = environment(me)) )
						return 1;
				// 通过遍历来查找这个 ob
				inv = all_inventory(room);
				for ( i = 0; i < sizeof(inv); i++ )
				{
					if ( inv[i] == me )
						continue;
					// 我们首先验证 ob 的真实 id
					if ( inv[i]->query("id") == new_id )
					{
						m++;
						k++;
						if ( m == v )
						{
								ob = inv[i]; // 找到并在指定的位置上，那么我们需要的 ob 就是这个了
								break;
						}
						else
							continue; // 如并不在指定的位置上，则继续查找下一个位置
					}
					// 验证伪装后的 id
					if ( ids = inv[i]->query_temp("apply/id") )
					{
						if ( !arrayp(ids) )
							continue;
						// 找到了伪装了的 ob 的 id
						if ( ids[0] == new_id )
						{
							m++;
							if ( m == v )
							{
								ob = inv[i]; // 找到并在指定的位置上，那么我们需要的 ob 就是这个了
								break;
							}
							else
								continue; // 如并不在指定的位置上，则继续查找下一个位置
						}
					}
				}
				// 没有对象 ob ，我们只能返回用户一个空白信息
				if ( !objectp(ob) )
					return 1;
				room_path(me, ob, k);
				break;

		case 1 :
				// 检查 me 是否有效存在，没有则直接返回
				if ( !objectp(me) )
						return 1;
				// 通过遍历来查找这个 ob
				inv = all_inventory(me);
				for ( i = 0; i < sizeof(inv); i++ )
				{
					if ( inv[i] == me )
						continue;
					// 我们首先验证 ob 的真实 id
					if ( inv[i]->query("id") == new_id )
					{
						m++;
						k++;
						if ( m == v )
						{
								ob = inv[i]; // 找到并在指定的位置上，那么我们需要的 ob 就是这个了
								break;
						}
						else
							continue; // 如并不在指定的位置上，则继续查找下一个位置
					}
					// 验证伪装后的 id
					if ( ids = inv[i]->query_temp("apply/id") )
					{
						if ( !arrayp(ids) )
							continue;
						// 找到了伪装了的 ob 的 id
						if ( ids[0] == new_id )
						{
							m++;
							if ( m == v )
							{
								ob = inv[i]; // 找到并在指定的位置上，那么我们需要的 ob 就是这个了
								break;
							}
							else
								continue; // 如并不在指定的位置上，则继续查找下一个位置
						}
					}
				}
				// 没有对象 ob ，我们只能返回用户一个空白信息
				if ( !objectp(ob) )
					return 1;
				user_path(me, ob, k);
				break;
		case 2:
			if ( !me->query_skill(new_id, 1) )
				return 1;
			skill_path(me, new_id);
			break;
	}
	return 1;
}

int room_path(object me, object ob, int v)
{
	mapping skills,meskills;
	object *inv;
	string *str, id, tmp, *goods, teamname, temp, arg;//temp arg排序用
	int i, my_skill, m;//m排序首行标识

	m = 0;

	if(stringp(tmp=ob->query_menu(me,0)))//如果对象能解释菜单，则直接返回菜单
	{
		write(tmp);
		return 1;
	}

	if ( v > 1 && !ob->query_temp("apply/id") )
		id = ob->query("id") + sprintf(" %d", v);
	else
		id = ob->query("id");

	tmp = TMI("mbegin "+ob->name(1)+";"+id)+TMI("mitem 观察$U;look "+id);

	if ( !wizardp(me) && playerp(ob) && ob->query_temp("apply/id") )
	{
		tmp = TMI("mbegin "+ob->name(1)+";"+id);
		tmp += TMI("mitem 对方似乎是经过易容改扮的，无法看出其虚实。;");
		tmp += TMI("mendd");
		tell_object(me, tmp);
		return 1;
	}

	if(living(ob))
	{
		if(interactive(ob))
		{
			tmp+=TMI("mitem 告诉$U...;tell "+id+" ...");
			tmp+=TMI("mitem 对$U耳语...;whisper "+id+" ...");

			if ( id == me->query_temp("reply") )
				tmp+=TMI("mitem 回答$U...;reply ...");

			if ( !me->query("xieyi/zmud") )
				tmp+=TMI("mitem 查询$U的装备;arm "+id);
		}

		tmp+=(me->query_leader()==ob)?TMI("mitem 停止跟随$U;follow none"):TMI("mitem 跟随$U;follow "+id);

		if(!environment(me)->query("no_fight"))
		{
			tmp+=TMI("mitem 与$U切磋;fight "+id);

			if ( (int)ob->query("age") > 17
				|| !playerp(ob)
				|| ob->query_condition("killer") )
				tmp+=TMI("mitem 攻击$U;hit "+id)+TMI("mitem 杀死$U;kill "+id)+TMI("mitem 偷袭$U;touxi "+id)+TMI("mitem 偷$U的...;steal ... from "+id);
		}

		if(ob->query("inquiry"))
		{
			str=keys(ob->query("inquiry"));
			for(i=0; i<sizeof(str); i++)
				tmp+=TMI("mitem 向$U打听关于"+str[i]+"的信息;ask "+id+" about "+str[i]+"");
		}

		// 组队系统
		if ( !stringp(teamname=me->query_temp("xyzx_team/name")) )
		{
			// 申请入队
			if ( stringp(ob->query_temp("xyzx_team/name")) && ob->query_temp("xyzx_team/zhang") )
				tmp+=TMI("mitem 加入$U的队伍;team jiaru "+id);
			// 创建队伍
			tmp+=TMI("mitem 创建队伍...;team found ...");
		}
		else
		{
			// 队长
			if ( me->query_temp("xyzx_team/zhang") )
			{
				// 邀请入队
				tmp+=TMI("mitem 邀请...加入队伍;team yaoqing ...");
				if ( !stringp(ob->query_temp("xyzx_team/name")) )
				{
					tmp+=TMI("mitem 邀请$U加入队伍;team yaoqing "+id);
				}
				else if ( ob->query_temp("xyzx_team/name") == me->query_temp("xyzx_team/name") )
				{
					tmp+=TMI("mitem 把队长转让给$U;team rang "+id); // 转让队长
					tmp+=TMI("mitem 把$U踢出队伍;team out "+id); // 踢人出队
				}
				tmp+=TMI("mitem 把队长转让给...;team rang ...");
				tmp+=TMI("mitem 把...踢出队伍;team out ...");
				if ( TEAMD->get_allot_type(teamname)=="平均分配" )
					tmp+=TMI("mitem 更改队伍分配模式为：等级比例;team change level");
				else
					tmp+=TMI("mitem 更改队伍分配模式为：平均分配;team change average");
			}
			// 队伍成员通用指令
			tmp+=TMI("mitem 脱离队伍;team out"); // 脱离队伍
			tmp+=TMI("mitem 查看队伍信息;team"); // 查看队伍信息
			tmp+=TMI("mitem 发送队伍聊天信息...;team talk ..."); // 队伍聊天
			// 队伍信息处理
			if ( me->query_temp("xyzx_team/block") )
				tmp+=TMI("mitem 接听队伍奖励信息;team listen"); // 接听队伍奖励信息
			else
				tmp+=TMI("mitem 屏蔽队伍奖励信息;team block"); // 屏蔽队伍奖励信息
		}

		//人物行囊物件完全列表
		if ( inv = all_inventory(me) )
		{
			for (i=0; i<sizeof(inv); i++)
			{
				if ( base_name(ob) == "/clone/gem/zhang" && inv[i]->query("max_sockets")
					&& me->query_temp("paid/张天师") && inv[i]->query("sockets/max") < inv[i]->query("max_sockets") )
					tmp+=TMI("mitem 开光"+wuse_name(inv[i]->short())+";show "+inv[i]->query("id"));

				//给予完全列表
				if ( !inv[i]->query("no_drop") || !inv[i]->query("no_give") )
				{
					if ( interactive(ob) || ob->id(inv[i]->query("target")) || function_exists("accept_object",ob) || (inv[i]->query("owner_id") && inv[i]->query("owner_id") == ob->query("id") && inv[i]->query("owner_name") == ob->query("name")) )
					{
						if ( inv[i]->query("money_id") )
						{
							tmp+=TMI("mitem 拿出..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +"给$U;give ... " + inv[i]->query("id") + " to " + id);
							tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "都给$U;give " + inv[i]->query("id") + " to "+id );
						}
						else
							tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "给$U;give " + inv[i]->query("id") + " to "+id );
					}
				}

				//普通宝石存放
				if ( (ob->query("id") == "jin yinhua" || ob->query("id") == "jin juhua")
					&& inv[i]->query("zhubao_save") )
					tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "存进珠宝店;cun " + inv[i]->query("id"));

				//当铺相关列表(估价、卖、典当东西)
				if ( !ob->query("no_diandang") && !ob->query("vendor_goods") && function_exists("do_value",ob) && function_exists("do_redeem",ob) && function_exists("do_pawn",ob) )
				{
					//估价
					if ( inv[i]->query("value") && !inv[i]->query("money_id") && !inv[i]->query("shaolin") && !inv[i]->query("no_sell") && !inv[i]->query("no_drop") )
						tmp+=TMI("mitem 惦估" + wuse_name(inv[i]->short()) + "的价格;value " + inv[i]->query("id"));

					//卖和典当
					if ( inv[i]->query("value") && !inv[i]->query("shaolin") && !inv[i]->query("no_drop") && !inv[i]->query("no_sell") && !inv[i]->query("money_id") )
					{
						if ( m == 0 )
						{
							temp = TMI("mitem 卖" + wuse_name(inv[i]->short()) + ";sell " + inv[i]->query("id"));
							arg = TMI("mitem 典当" + wuse_name(inv[i]->short()) + ";pawn " + inv[i]->query("id"));
						}
						else
						{
							temp += TMI("mitem 卖" + wuse_name(inv[i]->short()) + ";sell " + inv[i]->query("id"));
							arg += TMI("mitem 典当" + wuse_name(inv[i]->short()) + ";pawn " + inv[i]->query("id"));
						}

						m++;
					}
				}

				//钱庄
				if ( function_exists("do_deposit",ob) && function_exists("do_withdraw",ob) && function_exists("do_convert",ob) )
				{
					//存钱
					if ( inv[i]->query("money_id") )
						tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "存进钱庄;deposit all " + inv[i]->query("id"));
				}
			}

			if ( temp )
				tmp += temp;

			if ( arg )
				tmp += arg;
		}

		if(me->query("family/family_name") == "丐帮" )
		{
			if ( me->query_skill("checking",1) >= 10 )
				tmp+=TMI("mitem 打探...的技能;check ...");

			if(ob->query("family/family_name") != "丐帮" )
				tmp+=TMI("mitem 乞讨$U的...;beg ... from "+id);
		}

		if(ob->query("id")=="bigeye" && ob->query("name")=="千里眼" && ob->query("where"))
			tmp+=TMI("mitem 寻找...人;where ...");

		if(ob->query("id") == "zhu banxian")
			tmp+=TMI("mitem 向朱半仙打听有关「任务」的消息;quest");

		if(ob->query("id") == "jin yinhua" || ob->query("id") == "jin juhua")
		{
			tmp+=TMI("mitem 把...从珠宝店里取出来;qu ...");
			tmp+=TMI("mitem 查询存放的珠宝;chaxun");
		}

		if(me->query("dushu") && (ob->query("id") == "zhu danchen" || ob->query("id") == "zhu xi"))
			tmp+=TMI("mitem 学习"+"读书写字"+";learn literate at 1 from "+id);

		if(ob->query("xy_shoucheng"))
			tmp+=TMI("mitem 向郭靖打听关于功劳的信息;task over");

		if(ob->query("duchang/du"))
		{
			tmp+=TMI("mitem 在小上压...银子;bet 0 ... silver");
			tmp+=TMI("mitem 在小上压...黄金;bet 0 ... gold");
			tmp+=TMI("mitem 在小上压...银票;bet 0 ... thousand-cash");
			tmp+=TMI("mitem 在小上压...金票;bet 0 ... thousand-gold");
			tmp+=TMI("mitem 在大上压...银子;bet 1 ... silver");
			tmp+=TMI("mitem 在大上压...黄金;bet 1 ... gold");
			tmp+=TMI("mitem 在大上压...银票;bet 1 ... thousand-cash");
			tmp+=TMI("mitem 在大上压...金票;bet 1 ... thousand-gold");
			tmp+=TMI("mitem 在围骰上压... ...;bet 2 ... ...");
			tmp+=TMI("mitem 在...上压... ...;bet ... ... ...");
		}

		if(ob->query("id")=="taohua tong" && ob->query("name")=="桃花童")
			tmp+=TMI("mitem 申请建房;apply house");

		if(ob->query("vendor_goods"))
		{
			//增加Buy菜单列表
			if (arrayp(goods = ob->query("vendor_goods")))
			{
				for (i = 0; i < sizeof(goods); i++)
				{
					tmp+=TMI("mitem 买"+wuse_name(goods[i]->short())+";buy "+goods[i]->query("id")+"\n");
				}
			}

			tmp+=TMI("mitem 查询出售物品价格;list");
		}

		if ( !ob->query("no_diandang") && !ob->query("vendor_goods") && function_exists("do_value",ob) && function_exists("do_redeem",ob) && function_exists("do_pawn",ob) )
		{
			if(me->query("cwf"))
				tmp+=TMI("mitem 查询典当的东西;check");

			//增加redeem菜单列表
			if (arrayp(goods = me->query("pawns")))
			{
				for (i = 0; i < sizeof(goods); i++)
				{
					tmp+=TMI("mitem 赎回"+wuse_name(goods[i]->short())+";redeem "+goods[i]->query("id")+"\n");
				}
			}

			//增加buy菜单列表
			if ( inv = all_inventory(ob) )
			{
				for (i = 0; i < sizeof(inv); i++)
				{
					if (inv[i]->query("equipped") || inv[i]->query("money_id"))
						continue;

					tmp+=TMI("mitem 买"+wuse_name(inv[i]->short())+";buy "+inv[i]->query("id")+"\n");
				}
				tmp+=TMI("mitem 查看...第...个序号的属性;look_item ...英文名,...序号");
			}

			tmp+=TMI("mitem 查询出售物品价格;list "+id);
		}

		if ( function_exists("do_deposit",ob) && function_exists("do_withdraw",ob) && function_exists("do_convert",ob) )
		{
			tmp+=TMI("mitem 存钱;deposit ...");
			tmp+=TMI("mitem 兑换货币;convert ...");
			tmp+=TMI("mitem 把1000两黄金兑换成金票;convert 1000 gold to thousand-gold");
			tmp+=TMI("mitem 把2000两黄金兑换成金票;convert 2000 gold to thousand-gold");
			tmp+=TMI("mitem 把...两黄金兑换成金票;convert ... gold to thousand-gold");

			if(me->query("money") || me->query("more_money"))
			{
				tmp+=TMI("mitem 取10两黄金;withdraw 10 gold");
				tmp+=TMI("mitem 取50两黄金;withdraw 50 gold");
				tmp+=TMI("mitem 取100两黄金;withdraw 100 gold");
				tmp+=TMI("mitem 取500两黄金;withdraw 500 gold");
				tmp+=TMI("mitem 取1000两黄金;withdraw 1000 gold");
				tmp+=TMI("mitem 取2000两黄金;withdraw 2000 gold");
				tmp+=TMI("mitem 取钱;withdraw ...");
				tmp+=TMI("mitem 查询存款;check");
			}
		}

		//潜能银行
		if ( function_exists("cun_qn",ob) && function_exists("qu_qn",ob) && function_exists("cha_qn",ob) )
		{
			tmp+=TMI("mitem 查询存有潜能点数;check");
			tmp+=TMI("mitem 存入...点潜能;cun ...");
			tmp+=TMI("mitem 把潜能都存进银行;cun " + me->query("potential"));
			tmp+=TMI("mitem 取出...点潜能;qu ...");
			tmp+=TMI("mitem 把潜能都取出来;qu " + me->query("temp_svqn"));
		}

		//泰山盟主、使者像功能列表
		if ( ob->query("winner") == me->query("id") )
		{
			tmp+=TMI("mitem 储存档案;recopy");
			tmp+=TMI("mitem 读取档案;recover");
		}

		if ( !me->is_apprentice_of(ob) )
		{
			if(ob->query("attitude")=="peaceful")
				tmp+=TMI("mitem 拜$U为师;apprentice "+id);
		}
		else
		{
			tmp+=TMI("mitem 向师父$U磕头;apprentice "+id);
			tmp+=TMI("mitem 查询师父$U技能;skills "+id);

			if(ob->query_skills() && me->query("jing")>=1 && (int)me->query("potential")>(int)me->query("learned_points"))
			{
				skills=ob->query_skills();
				str=keys(skills);
				for(i=0; i<sizeof(str); i++)
				{
					if(me->query_skills())
					{
						meskills=me->query_skills();
						my_skill = me->query_skill(str[i], 1);

						if( (string)SKILL_D(str[i])->type()=="martial" && (int)((my_skill+1)*((my_skill+1)/10)*(my_skill+1))>(int)me->query("combat_exp") )
							continue;

						if(skills[str[i]]>my_skill && str[i]!="idle")
							tmp+=TMI("mitem 学习"+to_chinese(str[i])+";learn "+str[i]+" at 1 from "+id);
					}
					else
						tmp+=TMI("mitem 学习"+to_chinese(str[i])+";learn "+str[i]+" at 1 from "+id);
				}
			}
		}
	}
	else
	{
		if ( ob->is_character() && !ob->is_corpse() && !environment(me)->query("no_fight") )
		{
			if ( (int)ob->query("age") > 17 || !interactive(ob) )
				tmp+=TMI("mitem 杀死$U;kill "+id);
		}

		if(!ob->query("no_get"))
			tmp+=TMI("mitem 把$U捡起来;get "+id);

		if( ob->is_container() || (ob->is_character() && !living(ob)) )
		{
			//容器取出物件完全列表
			if ( inv = all_inventory(ob) )
			{
				for (i=0; i<sizeof(inv); i++)
				{
					if ( ob->is_character() )
					{
						if ( inv[i]->query("money_id") )
							tmp+=TMI("mitem 从$U身上收出..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +";get ... " + inv[i]->query("id") + " from " + id);

						tmp+=TMI("mitem 从$U身上收出" + wuse_name(inv[i]->short()) + ";get " + inv[i]->query("id") + " from "+id);
					}
					else
					{
						if ( inv[i]->query("money_id") )
							tmp+=TMI("mitem 从$U里拿出..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +";get ... " + inv[i]->query("id") + " from " + id);

						tmp+=TMI("mitem 从$U里拿出" + wuse_name(inv[i]->short()) + ";get " + inv[i]->query("id") + " from "+id);
					}
				}

				if ( sizeof(inv) > 0)
				{
					if ( ob->is_character() )
						tmp+=TMI("mitem 把$U身上的东西都收出来;get all from "+id);
					else
						tmp+=TMI("mitem 把$U里的东西都拿出来;get all from "+id);
				}
			}

			//容器放入完全列表
			if ( inv = all_inventory(me) )
			{
				for (i=0; i<sizeof(inv); i++)
				{
					if ( !inv[i]->query("no_put") )
					{
						if ( ob->is_character() )
						{
							if ( inv[i]->query("money_id") )
								tmp+=TMI("mitem 把..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +"放在$U身上;put ... " + inv[i]->query("id") + " in " + id);

							tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "放在$U身上;put " + inv[i]->query("id") + " in "+id);
						}
						else
						{
							if ( inv[i]->query("money_id") )
								tmp+=TMI("mitem 把..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +"装进$U里;put ... " + inv[i]->query("id") + " in " + id);

							tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "装进$U里;put " + inv[i]->query("id") + " in "+id);
						}
					}
				}
			}
		}

		if(ob->query("board_id"))
		{
			tmp+=TMI("mitem 设置...为斑竹;banzhu ...");
			tmp+=TMI("mitem 读新的贴子;read new");
			tmp+=TMI("mitem 读第...个贴子;read ...");
			tmp+=TMI("mitem 读第...贴的...条回复;read .......");
			tmp+=TMI("mitem 写新的贴子;post ...");
			tmp+=TMI("mitem 回复第...贴;re ...");
			tmp+=TMI("mitem 删除贴子...;discard ...");
		}

		if(id=="touzhu ban")
		{
			tmp+=TMI("mitem 购彩向导;read rules");
			tmp+=TMI("mitem 购彩规则;read duijiang");
			tmp+=TMI("mitem 投注状况;read biao");
			tmp+=TMI("mitem 投注;touzhu");
			tmp+=TMI("mitem 对奖;duijiang");
		}

		if(ob->query("id")=="bingqi pu")
		{
			tmp+=TMI("mitem 查阅$U;read "+id);
			tmp+=TMI("mitem 评定兵器;ping "+id);
		}

		if ( base_name(ob) == "/clone/misc/swordjia" )
		{
			tmp+=TMI("mitem 取出风雷剑;na fenglei jian from jia");
			tmp+=TMI("mitem 取出风火棍;na fenghuo gun from jia");
			tmp+=TMI("mitem 取出风云刀;na fengyun dao from jia");
		}
	}

	tmp+=TMI("mendd");
	tell_object(me,tmp);
	return 1;
}

int user_path(object me, object ob, int v)
{
	mapping prop;
	string id, tmp, *item_sx, ob_id;
	object *obj, *inv;
	int i, j, n, m, pinjie, item_levl;

	n = 1;// n为特殊宝石的合成条件判断，赋初值为 1
	m = 1;// m为普通宝石的合成条件判断，赋初值为 1

	if(stringp(tmp=ob->query_menu(me,1)))//如果对象能解释菜单，则直接返回菜单
	{
		write(tmp);
		return 1;
	}

	if ( v > 1 && !ob->query_temp("apply/id") )
		id = ob->query("id") + sprintf(" %d", v);
	else
		id = ob->query("id");

	ob_id = ob->query("id");

	tmp=TMI("mbegin "+ob->name(1)+";"+id)+TMI("mitem 观察$U;look "+id);

	if ( !ob->query("no_drop") || base_name(environment(me)) == "/d/city/drop" )
		tmp+=TMI("mitem 丢弃$U;drop "+id);

	if(ob->query("liquid"))
	{
		if(ob->query("liquid/remaining"))
			tmp+=TMI("mitem 喝$U;drink "+ob_id);
		if(environment(me)->query("resource/water"))
			tmp+=TMI("mitem 把$U装满水;fill "+ob_id);
	}

	if(ob->query("food_remaining"))
		tmp+=TMI("mitem 吃$U;eat "+ob_id);

	//容器取出物件完全列表
	if( ob->is_container() || (ob->is_character() && !living(ob)) )
	{
		if ( inv = all_inventory(ob) )
		{
			for (i = 0; i < sizeof(inv); i++)
			{
				if ( ob->is_character() )
				{
					if ( inv[i]->query("money_id") )
						tmp+=TMI("mitem 从$U身上收出..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +";get ... " + inv[i]->query("id") + " from " + id);

					tmp+=TMI("mitem 从$U身上收出" + wuse_name(inv[i]->short()) + ";get " + inv[i]->query("id") + " from "+id);
				}
				else
				{
					if ( inv[i]->query("money_id") )
						tmp+=TMI("mitem 从$U里拿出..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +";get ... " + inv[i]->query("id") + " from " + id);

					tmp+=TMI("mitem 从$U里拿出" + wuse_name(inv[i]->short()) + ";get " + inv[i]->query("id") + " from "+id);
				}
			}

			if ( sizeof(inv) > 0)
			{
				if ( ob->is_character() )
					tmp+=TMI("mitem 把$U身上的东西都收出来;get all from "+id);
				else
					tmp+=TMI("mitem 把$U里的东西都拿出来;get all from "+id);
			}
		}
	}

	if(mapp(prop=ob->query("armor_prop"))&& stringp(ob->query("armor_type")) )
	{
		if(!ob->query("equipped"))
			tmp+=TMI("mitem 穿上$U;wear "+id);
		else
			tmp+=TMI("mitem 脱下$U;remove "+id);
	}

	if(mapp(prop=ob->query("weapon_prop")) && stringp(ob->query("skill_type")))
	{
		if(!ob->query("equipped"))
			tmp+=TMI("mitem 装备$U;wield "+id);
		else
			tmp+=TMI("mitem 解除装备$U;unwield "+id);
	}

	if(!ob->is_character() && !ob->query("money_id"))
	{
		tmp+=TMI("mitem 以底价...两黄金拍卖$U;auction "+id+" for "+"... gold");

		if ( file_size("/data/paimai/name") != -1 )
		{
			tmp+=TMI("mitem 加价...两黄金竞标拍卖物品：" + wuse_name(read_file("/data/paimai/name")) + ";auction 1 add "+"... gold");
			tmp+=TMI("mitem 查看目前处于竞拍状态的物品清单;auction -l");
			tmp+=TMI("mitem 查看目前处于竞拍状态的物品介绍;auction -m");
		}
	}

	//嵌宝石完全列表
	if ( inv = all_inventory(me) )
	{
		for (i = 0; i < sizeof(inv); i++)
		{
			//容器放入物品完全列表
			if( ob->is_container() || (ob->is_character() && !living(ob)) )
			{
				if ( !inv[i]->query("no_put") && inv[i] != ob )
				{
					if ( ob->is_character() )
					{
						if ( inv[i]->query("money_id") )
							tmp+=TMI("mitem 放..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +"在$U身上;put ... " + inv[i]->query("id") + " in " + id);

						tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "放在$U身上;put " + inv[i]->query("id") +" in "+id);
					}
					else
					{
						if ( inv[i]->query("money_id") )
							tmp+=TMI("mitem 把..." + wuse_name(inv[i]->query("base_unit")) + wuse_name(inv[i]->name(1)) +"装进$U里;put ... " + inv[i]->query("id") + " in " + id);

						tmp+=TMI("mitem 把" + wuse_name(inv[i]->short()) + "装进$U里;put " + inv[i]->query("id") +" in "+id);
					}
				}
			}

			if ( inv[i]->query("equipped") )
				continue;

			//普通宝石
			if( ob->query("zhubao_save") )
			{
				if ( inv[i]->query("armor_prop/armor") || inv[i]->query("weapon_prop/damage") )
					tmp+=TMI("mitem 把$U嵌在" + wuse_name(inv[i]->short()) + "上;inset " + inv[i]->query("id"));

				//合成
				if ( inv[i]->query("b_lvl") == ob->query("b_lvl") )
				{
					if ( m == 3 )
					{
						tmp+=TMI("mitem 把$U合成更高一级宝石;hecheng "+id);
						m = 0;
					}

					m += 1;
				}
			}

			// 符
			if ( inv[i]->query("armor_prop/armor") || inv[i]->query("weapon_prop/damage") )
			{
				if ( inv[i]->query("armor_prop/armor") )
				{
					pinjie = 0;
					item_sx = keys(armor_shuxing);
					for (j = 0; j < sizeof(item_sx); j++)
					{
						if ( inv[i]->query("armor_prop/" + item_sx[j]) )
							pinjie++;
					}
				}
				if ( inv[i]->query("weapon_prop/damage") )
				{
					pinjie = 0;
					item_sx = keys(weapon_shuxing);
					for (j = 0; j < sizeof(item_sx); j++)
					{
						if ( inv[i]->query("weapon_prop/" + item_sx[j]) )
							pinjie++;
					}
				}

				if ( inv[i]->query("weapon_prop") )
					item_levl = inv[i]->query("weapon_prop/level");
				else if ( inv[i]->query("armor_prop") )
					item_levl = inv[i]->query("armor_prop/level");

				// 绑定符
				if( base_name(ob) == "/clone/map/obj/bangding-fu" )
				{
					if ( item_levl == !ob->query("xyzx_sys/bind_type", 1) && item_levl == !ob->query("xyzx_sys/bind_type", 2))
						tmp+=TMI("mitem 用$U绑定" + wuse_name(inv[i]->short()) + "的装备[不适用];bang " + id + " to " + inv[i]->query("id"));
					else
						tmp+=TMI("mitem 用$U绑定" + wuse_name(inv[i]->short()) + "的装备[适用];bang " + id + " to " + inv[i]->query("id"));
				}
				// 不带等级的优化符				
				if( base_name(ob) == "/clone/map/obj/hanyu-jingtie" )
				{
					if ( item_levl == 30)
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[不适用];ronglian " + id + " to " + inv[i]->query("id"));
					else
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[适用];ronglian " + id + " to " + inv[i]->query("id"));
				}
				if( base_name(ob) == "/clone/map/obj/jingang-shi" ) //金刚石
				{
					if ( item_levl < 30)
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[不适用];ronglian1 " + id + " to " + inv[i]->query("id"));
					else
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[适用];ronglian1 " + id + " to " + inv[i]->query("id"));
				}
				if( base_name(ob) == "/clone/map/obj/longwen-chijin" ) //龙纹赤金
				{
					if ( item_levl < 30)
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[不适用];ronglian2 " + id + " to " + inv[i]->query("id"));
					else
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[适用];ronglian2 " + id + " to " + inv[i]->query("id"));
				}
				if( base_name(ob) == "/clone/map/obj/feixian-xuanjing" ) //飞仙玄晶
				{
					if ( item_levl < 30)
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[不适用];ronglian3 " + id + " to " + inv[i]->query("id"));
					else
						tmp+=TMI("mitem 用$U提升" + wuse_name(inv[i]->short()) + "的装备[适用];ronglian3 " + id + " to " + inv[i]->query("id"));
				}
			}

			//特殊宝石
			if ( ob->query("liebiao_gem") )
			{
				//嵌
				if ( inv[i]->query("max_sockets") && inv[i]->query("sockets/max") > 0  )
				{
					for (j = 0; j < (int)inv[i]->query("sockets/max"); j++)
					{
						tmp+=TMI("mitem 把$U嵌在" + wuse_name(inv[i]->short()) + "的第 " + (j+1) + " 个接孔上;insert " + ob_id + " into " + inv[i]->query("id") +" at socket " + (j+1));
					}
				}

				//合成
				if ( inv[i]->name(1) == ob->name(1) && inv[i]->query("id") == ob->query("id") )
				{
					if ( n == 3 )
					{
						tmp+=TMI("mitem 把$U合成更高一级宝石;combine "+ob_id);
						n = 0;
					}

					n += 1;
				}
			}
		}
	}

	if ( ob->query("skill") )
	{
		tmp+=TMI("mitem 读$U;study "+id);
		tmp+=TMI("mitem 全力读$U;study "+id+" at all");
	}
	else if ( function_exists("do_du",ob) && !living(ob) )
		tmp+=TMI("mitem 读$U;study "+id);

	//在特定场景下对物品的特殊动作菜单
	obj = all_inventory(environment(me));
	for (i=0;i < sizeof(obj);i++)
	{
		//物品买卖和存取完全列表化
		if ( !userp(obj[i]) )
		{
			if ( living(ob) || ob->is_character() || ob->is_corpse() )
			continue;

			//卖
			if ( !obj[i]->query("no_diandang") && !obj[i]->query("vendor_goods") && function_exists("do_value",obj[i]) && function_exists("do_redeem",obj[i]) && function_exists("do_pawn",obj[i]) )
			{
				if ( ob->query("zhubao_save") || ob->query("xyzx_save_item") || (!ob->query("shaolin") && !ob->query("no_drop") && !ob->query("no_sell") && !ob->query("money_id")) )
				{
					tmp+=TMI("mitem 出售$U;sell "+id);
					if ( !ob->query("xyzx_save_item") && !ob->query("zhubao_save") )
						tmp+=TMI("mitem 典当$U;pawn "+id);
				}

				//估价
				tmp+=TMI("mitem 惦估" + wuse_name(ob->short()) + "的价格;value " + ob->query("id"));
			}

			//存钱
			if ( function_exists("do_deposit",obj[i]) && function_exists("do_withdraw",obj[i]) && function_exists("do_convert",obj[i]) && ob->query("money_id") )
				tmp+=TMI("mitem 把$U存进钱庄;deposit all "+id);
		}

		//面具完全列表
		if ( ob->query("name") == "面具" && ob->query("id") == "mian ju" )
		{
			//戴面具
			if ( !obj[i]->query_temp("apply/name") )
			{
				if ( obj[i] == me )
					continue;

				//不对不想显形的巫师增加列表，保证其隐身效果
				if ( wizardp(obj[i]) && obj[i]->query("env/invisibility") > 9 )
					continue;

				if ( userp(obj[i]) )
					tmp+=TMI("mitem 使用面具装扮成" + wuse_name(obj[i]->query("name")) + " (玩家);pretend "+obj[i]->query("id"));
				else
					tmp+=TMI("mitem 使用面具装扮成" + wuse_name(obj[i]->query("name")) + " (NPC);pretend "+obj[i]->query("id"));
			}
		}

		//物品给予完全列表
		if ( !ob->query("no_drop") || !ob->query("no_give") )
		{
			if ( obj[i] == me )
				continue;

			//不对不想显形的巫师增加列表，保证其隐身效果
			if ( wizardp(obj[i]) && obj[i]->query("env/invisibility") > 9 )
				continue;

			// 送信任务
			if ( ob->query("target") == obj[i]->short() && function_exists("do_give",ob) )
				tmp+=TMI("mitem 把"+wuse_name(ob->short())+"交给" + wuse_name(obj[i]->name()) + ";give "+id+" to " + obj[i]->query("id"));

			//注意：此处过滤是为了使列表简单化加快循环，作用域本次循环的结尾，如果你需要在这后面增加新的列表菜单，请仔细检查你所需要的是否被该句所忽略。
			if ( !interactive(obj[i]) && obj[i]->query("id") != ob->query("target") && !function_exists("accept_object",obj[i]) && (!ob->query("owner_id") || ob->query("owner_id") != obj[i]->query("id") || ob->query("owner_name") != obj[i]->query("name")) )
				continue;

			if ( userp(obj[i]) )
			{
				if ( ob->query("money_id") )
				{
					tmp+=TMI("mitem 拿出..." + wuse_name(ob->query("base_unit")) + wuse_name(ob->name(1)) +"给"+wuse_name(obj[i]->name())+" (玩家);give ... " + ob->query("id") + " to " + obj[i]->query("id"));
					tmp+=TMI("mitem 把"+wuse_name(ob->short())+"都给" + wuse_name(obj[i]->name()) + " (玩家);give "+id+" to " + obj[i]->query("id"));
				}
				else
					tmp+=TMI("mitem 把"+wuse_name(ob->short())+"给" + wuse_name(obj[i]->name()) + " (玩家);give "+id+" to " + obj[i]->query("id"));
			}
			else
			{
				if ( ob->query("money_id") )
				{
					tmp+=TMI("mitem 拿出..." + wuse_name(ob->query("base_unit")) + wuse_name(ob->name(1)) +"给"+wuse_name(obj[i]->name())+" (NPC);give ... " + ob->query("id") + " to " + obj[i]->query("id"));
					tmp+=TMI("mitem 把"+wuse_name(ob->short())+"都给" + wuse_name(obj[i]->name()) + " (NPC);give "+id+" to " + obj[i]->query("id"));
				}
				else
					tmp+=TMI("mitem 把"+wuse_name(ob->short())+"给" + wuse_name(obj[i]->name()) + " (NPC);give "+id+" to " + obj[i]->query("id"));
			}
		}
	}

	//取下面具
	if ( ob->query("name") == "面具" && ob->query("id") == "mian ju" && me->query_temp("apply/name") )
		tmp+=TMI("mitem 取下面具回复本来面目;pretend none");

	//礼物包相关列表
	if ( base_name(ob) == "/d/city/obj/gift" || base_name(ob) == "/clone/misc/gift" )
		tmp+=TMI("mitem 打开" + wuse_name(ob->short()) + ";chai gift");

	//自练的装备  //2015.10 添加 针对 my jia 和my sword 武器类的命令区分
	if ( function_exists("do_hui",ob) || function_exists("do_hui1",ob) )
	{
		//毁
		if ( ob->query("id") == "my jia" )
		tmp+=TMI("mitem 摧毁" + wuse_name(ob->short()) + ";hui1 " + ob->query("id"));
        else
		tmp+=TMI("mitem 摧毁" + wuse_name(ob->short()) + ";hui " + ob->query("id"));
	
		//改名
		if ( function_exists("do_rename",ob) || function_exists("do_jianame",ob) )
		{
			if ( ob->query("id") == "my jia" )
				tmp+=TMI("mitem 把" + wuse_name(ob->short()) + "的名称改为...;jianame ...");
			else
				tmp+=TMI("mitem 把" + wuse_name(ob->short()) + "的名称改为...;rename ...");
		}

		//使用货币提升
		if ( function_exists("do_levelup",ob) || function_exists("do_levelup1",ob))
			if ( ob->query("id") == "my jia" )
			tmp+=TMI("mitem 祭升" + wuse_name(ob->short()) + ";jijia " + ob->query("id"));
		   else
			tmp+=TMI("mitem 祭升" + wuse_name(ob->short()) + ";jiwu " + ob->query("id")); 
	}

	//补天石
	if ( base_name(ob) == "/d/npc/m_weapon/tan/item/stone" )
	{
		tmp+=TMI("mitem 冶炼" + wuse_name(ob->short()) + ";yelian " + id);
		tmp+=TMI("mitem 吃" + wuse_name(ob->short()) + ";eat " + ob->query("id"));
	}

	tmp+=TMI("mendd");
	tell_object(me,tmp);
	return 1;
}

int skill_path(object me, string skill)
{
	string tmp, *skill_types, enable_skill, use_text;
	int i;

	skill_types = ({"unarmed", "axe", "sword", "blade", "stick", "staff", "spear", "fork", "club", "throwing",
		"force", "parry", "hammer", "dodge", "magic", "spells",	"taoism", "whip", "poison", "finger", "hand",
		"cuff", "claw", "strike"});

	tmp = TMI("mbegin "+to_chinese(skill)+";"+skill);
	tmp+=TMI("mitem 查看使用中的特殊技能;enable");
	tmp+=TMI("mitem 遗忘(放弃)技能：$U;abandon "+skill);
	// 特殊技能
	if ( member_array(skill, skill_types) == -1 )
	{
		// 战斗技能
		if ( SKILL_D(skill)->type() == "martial" )
		{
			for ( i=0; i<sizeof(skill_types); i++ )
			{
				if( SKILL_D(skill)->valid_enable(skill_types[i]) )
				{
					if ( skill_types[i] == "force" )
					{
						use_text=TMI("mitem 查看特殊内功("+to_chinese(skill)+")的运功法门;help "+skill);
						tmp += TMI("mitem 激发特殊内功("+to_chinese(skill)+")到["+to_chinese(skill_types[i])+"]上;enable "+skill_types[i]+" "+skill);
					}
					else
					{
						use_text=TMI("mitem 查看特殊技能("+to_chinese(skill)+")的绝招;help "+skill);
						tmp += TMI("mitem 激发特殊技能("+to_chinese(skill)+")到["+to_chinese(skill_types[i])+"]上;enable "+skill_types[i]+" "+skill);
					}
				}
			}
			tmp += use_text;
		}
		else // 非战斗技能
		{
			tmp+=TMI("mitem 查看技能使用说明;help "+skill);
			for ( i=0; i<sizeof(skill_types); i++ )
			{
				if( SKILL_D(skill)->valid_enable(skill_types[i]) )
					tmp += TMI("mitem 激发特殊技能("+to_chinese(skill)+")到["+to_chinese(skill_types[i])+"]上;enable "+skill_types[i]+" "+skill);
			}
		}
	}
	else // 基础技能
	{
		tmp+=TMI("mitem 查看技能使用说明;help "+skill);
		if ( stringp(enable_skill = me->query_skill_mapped(skill)) )
		{
			tmp+=TMI("mitem 解除激发在$U上的特殊技能："+to_chinese(enable_skill)+";enable "+skill+" none");
			tmp+=TMI("mitem 修炼激发在$U上的特殊技能："+to_chinese(enable_skill)+";practice "+skill);
		}
	}
	// 个别技能的特殊功用
	//----------------------start-----------------------------
	if ( skill == "force" )
	{
		tmp+=TMI("mitem 运功恢复自己的精神;exert regenerate");
		tmp+=TMI("mitem 运功恢复自己的气血;exert recover");
		tmp+=TMI("mitem 运功替自己疗治精神上的损伤;exert jingheal");
		tmp+=TMI("mitem 运功替自己疗治气血上的损伤;exert heal");
		tmp+=TMI("mitem 运功替...疗治精神上的损伤;exert jingheal ...");
		tmp+=TMI("mitem 运功替...疗治气血上的损伤;exert heal ...");
		tmp+=TMI("mitem 使用...点气血打坐修炼内力;exercise ...");
		if ( stringp(me->query_skill_mapped(skill)) )
			tmp+=TMI("mitem 每次使用...点内力进行物理攻击;enforce ...");
	}
	if ( skill == "taoism" )
	{
		tmp+=TMI("mitem 使用...点精神吐纳修炼精力;respitate ...");
		if ( stringp(me->query_skill_mapped(skill)) )
			tmp+=TMI("mitem 每次使用...点精力进行神通攻击;enchant ...");
	}
	if ( skill == "qimen-flee" )
	{
		tmp+=TMI("mitem 使用神通：遁地之术;conjure drift");
		tmp+=TMI("mitem 使用神通：飞天遁甲;conjure dunjia");
	}
	if ( skill == "count" )
	{
		tmp+=TMI("mitem 使用八卦推算查找...目前位置;location ...");
	}
	//-----------------------end------------------------------
	tmp+=TMI("mendd");

	tell_object(me, tmp);
	return 1;
}

//因旧版Tomud客户端列表菜单不能解释ANSI，故清除颜色字符串以维持正常
string wuse_name(string str)
{
	if ( !stringp(str) ) str = "";

	str = replace_string(str,BLK,"");
	str = replace_string(str,RED,"");
	str = replace_string(str,GRN,"");
	str = replace_string(str,YEL,"");
	str = replace_string(str,BLU,"");
	str = replace_string(str,MAG,"");
	str = replace_string(str,CYN,"");
	str = replace_string(str,WHT,"");
	str = replace_string(str,HIR,"");
	str = replace_string(str,HIG,"");
	str = replace_string(str,HIY,"");
	str = replace_string(str,HIB,"");
	str = replace_string(str,HIM,"");
	str = replace_string(str,HIC,"");
	str = replace_string(str,HIW,"");
	str = replace_string(str,NOR,"");
	str = replace_string(str,BLINK,"");
	return str;

}