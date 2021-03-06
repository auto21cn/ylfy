// 初始化编译 By lisa
// 完善优化(修改存在的BUG，款项转移采用钱庄转帐，)
// 支持动态物品的详细资料查询
// auction.c 拍卖与竞价程序
// call_out() 映射控制版
/*-----------------------------------------------------------------------------
key  string ob_id      物品ID
v[0] object obj        拍卖物品     
v[1] int    ob_price   竞标价格               
v[2] object ob_auction 竞标者                 
v[3] object ob_onwer   物品所有者             
v[4] string ob_desc    物品所有者对该物品的介绍
v[5] string auction_id 竞标者ID
v[6] string onwer_id   物主ID
v[7] string ob_name    物品名称
v[8] string ob_long    物品描述

mapping structure:
auction[obj : {ob, ob_price, ob_auction, ob_onwer, ob_desc, auction_id, ...} ]
*/
//-----------------------------------------------------------------------------


#include <ansi.h>
inherit F_DBASE;
inherit F_CLEAN_UP;

#define PRICE_DIFFERENCE 100
// 定义是否支持查询拍卖的动态物品的详细资料
#define XYZX_NEW_ITEM

static mapping auction = ([]);

// 状态变化的控制中心
void auction_chat(string msg);  
void auction_state_check(int times, int s_times, int last_price, string obj_id); 
// 静止的状态切换
void auction_end(string ob_name, int ob_price, mixed ob_auction, object ob_onwer, object ob, string ob_id);
void auction_cancel(string ob_id, object discredit_1, object discredit_2);
// 实现拍卖
void get_ob_desc(string desc, object me, string str, int num);
void choise_secret(string decide, object me, string ob_id, string desc, int num);
// 数据反馈
int player_demand(int num, string unit, object me);
int player_bank(object ob);
int player_pay(object who, int amount);
int help();

int clean_up()
{
	return 1;
}

void create()
{
	seteuid(ROOT_UID);
	set("name", "拍卖指令");
	set("id", "auction");
	set("channel_id","");
}

void auction_chat(string msg) 
{	
	msg = replace_string(msg,NOR,HIY);
	CHANNEL_D->do_channel(this_object(),"jypm",msg);	
}

void auction_state_check(int times, int s_times, int last_price, string obj_id)
{
	int i, ob_price, flag1 = 0, flag2 = 0;
	object ob, ob_auction, ob_onwer, new_auction, new_onwer, nul;
	mixed *v;
	string *k, ob_name, ob_id, str;
	
	// 重新定位此物品，避免因为其他物品被清除导致索引号变化
	k = keys(auction);
	i = member_array(obj_id,k); 
	v = values(auction)[i];
	ob_id      = k[i];
	ob         = v[0];
	ob_price   = v[1];
	ob_auction = v[2];
	ob_onwer   = v[3];
	ob_name    = v[7];
	
	if(!objectp(ob_auction) && !stringp(ob_auction))
	{
		flag1++;
		if(objectp(new_auction = find_player(v[5])))
		{
			ob_auction = new_auction;
			flag1 = 0;
		}
	}

	if(!objectp(ob_onwer))
	{
		flag2++;
		if(objectp(new_onwer = find_player(v[6])))
		{
			ob_onwer = new_onwer;
			flag2 = 0;
		}
	}

	if(flag2 && !flag1) 
	{
		str="由于卖方缺席，取消"+ob_name+HIW"的拍卖";

		//删除文件
		rm("/data/paimai/name");

		auction_chat(str);
		auction_cancel(ob_id, ob_auction, nul);
		return;
	}
	
	if(!objectp(ob) || !objectp(present(ob,ob_onwer)))
	{
		str="由于卖方保管不当，拍卖物品"+ob_name+HIW"丢失，本次拍卖取消！\n";

		//删除文件
		rm("/data/paimai/name");

		auction_chat(str);
		ob_onwer->delete_temp("auctioning");
		auction_cancel(ob_id, ob_auction, nul);
		return;
	}
	
	if ( times < 23 )
	{
		times++;
		
		if(ob_price > last_price)
		{
			s_times = 0;
			call_out("auction_state_check", 20, times, s_times, ob_price, ob_id);
		}
		else
		{
			s_times++;
			
			if(s_times<4)
			{
				str = "第"+CHINESE_D->chinese_number(s_times)+"次喊价:拍卖"+ob_name+HIW"，现价"+MONEY_D->price_str(ob_price)+"!!";
				auction_chat(str);
				call_out("auction_state_check", 15, times, s_times, ob_price, ob_id);	
			}
			else
			{
				if(flag1 && !flag2)
				{
					str="由于买方缺席，取消"+ob_name+HIW"的拍卖！";

					//删除文件
					rm("/data/paimai/name");

					auction_chat(str);
					auction_cancel(ob_id, ob_onwer, nul);
					return;
				}
				
				if(flag1 && flag2)
				{
					str="由于买卖双方缺席，取消"+ob_name+HIW"的拍卖！";

					//删除文件
					rm("/data/paimai/name");

					auction_chat(str);
					auction_cancel(ob_id, nul, nul);
					return;
				}	
				
				auction_end(ob_name, ob_price, ob_auction, ob_onwer, ob, ob_id);
			}
		}
	}
	else
	{
		if(flag1 && !flag2)
		{
			str="由于买方缺席，取消"+ob_name+HIW"的拍卖！";

			//删除文件
			rm("/data/paimai/name");

			auction_chat(str);
			auction_cancel(ob_id, ob_onwer, nul);
			return;
		}
		
		if(flag1 && flag2)
		{
			str="由于买卖双方缺席，取消"+ob_name+HIW"的拍卖！";

			//删除文件
			rm("/data/paimai/name");

			auction_chat(str);
			auction_cancel(ob_id, nul, nul);
			return;
		}
		
		str = "时间已到，拍卖"+ob_name+HIW"的过程到此为止！\n";

		//删除文件
		rm("/data/paimai/name");

		auction_chat(str);
		auction_end(ob_name, ob_price, ob_auction, ob_onwer, ob, ob_id);
		return;
	}
	
	return ;
}

void auction_end(string ob_name, int ob_price, mixed ob_auction, object ob_onwer, object ob, string ob_id)
{

	object  *inv, *en_inv, nul;
	string onwer_id, str;

	// 虽然不太可能发生，但还是判断下保险
	if(!objectp(ob_onwer)) return;

	if ( ob_onwer->is_ghost() )
	{
		//删除文件
		rm("/data/paimai/name");
		str = "由于卖方已经死亡，本次拍卖无效。\n";
		auction_cancel(ob_id, ob_onwer, nul);
		ob_onwer->set("auction_fail", ob_onwer->query("mud_age"));
		auction_chat(str);
		return;
	}
	
	onwer_id = ob_onwer->query_temp("auction/"+ob_id);
	
	if(stringp(ob_auction))
	{
		str=onwer_id+ " 以底价 "+MONEY_D->price_str(ob_price)+" 拍卖 "+
		ob_name+HIW"，三次喊价后无人投标，本次拍卖无效！\n";

		//删除文件
		rm("/data/paimai/name");

		auction_cancel(ob_id, ob_onwer, nul);
		ob_onwer->set("auction_fail",ob_onwer->query("mud_age"));
	}
	else
	{
		if ( ob_auction->is_ghost() )
		{
			//删除文件
			rm("/data/paimai/name");
			str = "由于买方已经死亡，本次拍卖无效。\n";
			ob_auction->delete_temp("auctioning");
			auction_cancel(ob_id, ob_onwer, nul);
			auction_chat(str);
			return;
		}

		str=ob_auction->query("name")+"("+ob_auction->query("id")+")"+ " 出价 "+MONEY_D->price_str(ob_price)+" 竞标 "+
		ob_name+HIW"成功，本次拍卖成交！\n";

		//删除文件
		rm("/data/paimai/name");
			
		// 买卖双方金钱物品的交换，买方需另交成交价10%的手续费（卖方之前已经交过底价10%的保证金）
		inv = all_inventory(ob_auction); 
		en_inv = all_inventory(environment(ob_auction)); 

		if ( sizeof(all_inventory(ob)) > 0 )
		{
			str="由于卖方不守信誉在拍卖品里放置杂物，本次拍卖无效。\n";
			ob_onwer->delete_temp("auctioning");
			auction_cancel(ob_id, ob_auction, nul);
		} else if ( !player_pay(ob_auction, (int)ob_price / 10 + ob_price) ) 
		{
			str="由于买方无力支付竞价，本次拍卖无效。\n";
			ob_auction->delete_temp("auctioning");
			auction_cancel(ob_id, ob_onwer, nul);
		}
		else
		{
			tell_object(ob_auction,"恭喜！你竞标成功，得到了 "+ob_name+"\n");
			
			if(!ob->move(ob_auction) || (inv && sizeof(inv) > 49))
			{
				if(en_inv && sizeof(en_inv) < 49)
				{
					tell_object(ob_auction, "你手头已经拿不下了,东西落到了你的脚边..\n");
					ob->move(environment(ob_auction)); 
				}
				else
				{
					tell_object(ob_auction, "此次拍卖所得由于你无力保管而收归国有！\n");
				 	destruct(ob);
				}
			}	
			
			tell_object(ob_onwer,ob_name+"拍卖成功，所得款已经转至你的钱庄帐户。\n");
			
			//卖方钱庄增加拍卖所得
			if ( ob_onwer->query("money") + ob_price > 99999999 )
			{
				ob_onwer->add("more_money", (int)(ob_onwer->query("money") + ob_price) / 100000000);
				ob_onwer->set("money", (ob_onwer->query("money")+ob_price) % 100000000);
			}
			else
				ob_onwer->add("money", ob_price);
			
			auction_cancel(ob_id, ob_auction, ob_onwer);
		}
	}
	
	auction_chat(str);
	return;
}

void auction_cancel(string ob_id, object discredit_1, object discredit_2)
{
	if(member_array(ob_id, keys(auction)) != -1)
		map_delete(auction, ob_id);

	if(objectp(discredit_1))
		discredit_1->delete("discredit");
	if(objectp(discredit_2))
		discredit_2->delete("discredit");
}

int main(object me,string arg)
{
	int i, guaranty, num, index;
	float coin;
	mixed *ob_value;
	string str, unit, *tuned_ch, *ob_key;
	object ob;
	
	ob_key = keys(auction);
	ob_value = values(auction);
	
	//打开拍卖频道
	if(!arg)
	{
		tuned_ch = me->query("channels");
		
		if( !pointerp(tuned_ch) )//没开通任何频道时
			me->set("channels", ({ "jypm" }) );
		else if( member_array(auction, tuned_ch) == -1 )//没开通拍卖频道时
			me->set("channels", tuned_ch + ({ "jypm" }) );
		
		//发送频道开通信息
		tell_object(me,"\n你的拍卖频道(jypm)现在处于开通状态\n");
		return 1;
	}	
		
	if(arg == "-l")
	{
	    if(!sizeof(auction))
		{
			tell_object(me,"目前没有物品被拍卖。\n");
			return 1;
		}
		
		str=HIG"当前拍卖物品清单：\n\n";
		str += "——————————————————————————————————————\n";
		str += "序号  物品名称                    当前标价                  最高竞价者\n";
		str += "——————————————————————————————————————\n"NOR;
		
		for(i=0; i < sizeof(auction); i++)
		{
			mixed  *v = ob_value[i];

			str += sprintf("%-5s ",  i+1+".");
			str += sprintf("%-27s ", v[7]);
			str += sprintf("%-25s ", MONEY_D->price_str(v[1]));
			str += sprintf("%-15s\n", (!stringp(v[2]))? v[5] : "");
		}
		str += HIG"——————————————————————————————————————\n"NOR;
		str += "\n\n";
        me->start_more(str);
		return 1;
	}
	
	if(arg == "-m")
	{
		if(!sizeof(auction))
		{
			tell_object(me,"目前没有物品被拍卖。\n");
			return 1;
		}
		
		write(HIG"当前拍卖物品详细介绍：\n\n"NOR);

#ifdef XYZX_NEW_ITEM
		for(i=0; i < sizeof(auction);i++)
		{
			mixed  *v = ob_value[i];

			//str = HIG+(i+1)+".\n——————————————————————————————————————"NOR"\n物品名称： "+v[7]+
			//采用新的look，上面那行换用下面和行
			str = HIG+(i+1)+".\n——————————————————————————————————————"NOR+
			"\n物主介绍："+v[4]+
			"\n物主    ："+v[6]+
			"\n物品描述：\n";
			write(str);
			__DIR__"look"->look_item(me, v[0]);
		}
		
		write("\n\n");
#else
		for(i=0; i < sizeof(auction);i++)
		{
			mixed  *v = ob_value[i];

			//str = HIG+(i+1)+".\n——————————————————————————————————————"NOR"\n物品名称： "+v[7]+
			//采用新的look，上面那行换用下面和行
			str = HIG+(i+1)+".\n——————————————————————————————————————"NOR+
			"\n物品描述："+v[8]+
			"\n物主介绍："+v[4]+
			"\n物主："+v[6]+"\n\n";
		}
		
		me->start_more(str);
#endif

		return 1;
	}

	if(sscanf(arg,"%s for %d %s",str,num,unit) == 3)
	{
		str = lower_case(str);
		
		/*if(me->query("combat_exp") < 10000)
		{
			tell_object(me,"你虽已成年，但是涉世经验太少，无法对自己的拍卖行为负责。\n");
			return 1;
		}*/
		
		if(me->is_busy())
		{
			tell_object(me,"你正忙着呢。\n");
			return 1;
		}
		
		if(me->is_ghost())
		{
			tell_object(me,"鬼魂无法进行拍卖行为，还是等还阳以后再说吧。\n");
			return 1;
		}
		
		if(me->query("discredit") && !me->query_temp("auctioning"))
		{
			if(me->query("mud_age") - me->query("discredit") < 3600)	
			{
				tell_object(me,"你由于在上次拍卖过程中信誉值降低，暂时无权参与。\n");
				return 1;
			}
			else
				me->delete("discredit");			
		}
		
		if(me->query("mud_age") - me->query("auction_fail") < 30)	
		{
			tell_object(me,"你上次拍卖的物品无人问津，这回还是先花点时间调查市场吧。\n");
			return 1;		
		}
		
		//决定同时间内有多少拍卖进程可以并存
		if ( !wizardp(me) && sizeof(auction) >= 1 )
		{
			tell_object(me,"现在已有人在进行拍卖，请少候。\n");
			return 1;
		}
		
		if(!objectp(ob = present(str,me)))
		{
			tell_object(me,"你身上没有 "+HIG+str+NOR+" 这件物品。\n");
			return 1;
		}		
		
		if(member_array(ob->query("id"),ob_key)!= -1)
		{
			tell_object(me,"你晚了一步，这类物品已经有人拍卖了。\n");
			return 1;
		}
		
		if(!wizardp(me) && !ob->query("buy_sell") && (ob->query("no_drop") || ob->query("no_sell") || ob->query("no_give") || ob->query("no_get") || ob->query("ownmake") || ob->query("no_put") || ob->query("money_id") || ob->is_character()) )  	
		{
			tell_object(me,"这件物品不能参加拍卖。\n");
			return 1;
		}
		
		//防止随意移动禁止的物件，不允许拍卖物品里再放入其他东西
		if(sizeof(all_inventory(ob)) > 0 )
		{
			tell_object(me,"还是把里面的东西都拿出来再参加拍卖吧！\n");
			return 1;
		}

		if ( mapp(ob->query("bind_master_level")) )
		{
			tell_object(me,"已绑定的物品不能参加拍卖。\n");
			return 1;
		}
		
		//克扣拍卖手续费10%
		guaranty = (int)(ob->query("value")/10);
		
		if (guaranty < 10)
			guaranty = 10;
		
		if(!player_pay(me, guaranty)) 
		{
			tell_object(me,"你全部的身家财产尚不足以交纳拍卖保证金！\n");
			return 1;
		}

		unit = lower_case(unit);
		
		if(!(num = player_demand(num, unit, me)))
			return 1;
		
		write("你所要拍卖的物品："+ob->query("name")+"， 底价："+MONEY_D->price_str(num)+"\n\n");
		write("请输入你对该物品的介绍（控制在50个字符内）\n直接按回车(enter)可以忽略此项。\n");
		input_to("get_ob_desc", me, ob->query("id"), num);
		return 1;
	}
	
	if(sscanf(arg,"%d add %d %s", index,num,unit) == 3)
	{
		object obj;
		mixed *v; 
		int ob_price; 

		/*if(me->query("combat_exp") < 10000)
		{
			tell_object(me,"你虽已成年，但是涉世经验太少，无法对自己的拍卖行为负责。\n");
			return 1;
		}*/
		
		if(me->is_ghost())
		{
			tell_object(me,"鬼魂无法进行拍卖行为，还是等还阳以后再说吧。\n");
			return 1;
		}
		
		if(me->is_busy())
		{
			tell_object(me,"你正忙着呢。\n");
			return 1;
		}
		
		if(me->query("discredit") && !me->query_temp("auctioning"))
		{
			if(me->query("mud_age") - me->query("discredit") < 3600)	
			{
				tell_object(me,"你由于在上次拍卖过程中信誉值降低，暂时无权参与。\n");
				return 1;
			}
			else
				me->delete("discredit");			
		}
		
		if(index < 1 || index > sizeof(auction))
		{
			tell_object(me,"没有这个序号的物品！\n请用 auction -l 指令查询目前竞拍物品清单。\n");
			return 1;
		}
		
		v = ob_value[index-1];
		obj = v[0];
		ob_price = v[1];
		
		if(objectp(obj) && v[3] == me)
		{
			tell_object(me,"那是你自己的拍卖物品，想暗地托价不成？\n");
			return 1;
		}
		
		coin = player_bank(me);
		unit = lower_case(unit);

		//检查竞价是否在规划范围内
        if(!(num = player_demand(num, unit, me)))
			return 1;
		
		if(num < ob_price/10)	
		{
			tell_object(me,"竞拍规则：差价以现拍价的10%为底线。\n");	
			return 1;
		}
		
		if ( to_float(num) + ob_price > coin)
		{
			tell_object(me,"你没有这么多钱可以偿付这个出价。\n");
			return 1;
		}

		//检查买方是否能付得起10%的手续费
		if ( (to_float(num) + ob_price)*11/10 > coin)
		{
			tell_object(me,"竞价者还需交付现拍卖价10%的手续费，你没有这么多钱可以偿付这个出价。\n");
			return 1;
		}

		if ( (to_float(num) + ob_price)*11/10 > 2100000000)
		{
			tell_object(me,"对不起，本行不支持无顶竞价，你的这个叫价已超过了顶线。\n"
				HIM"★ 温馨提示：\n"
				HIW"------------------------------------------------------\n"
				HIY"★ 以下公式\n"
				HIR"★ (目前物品的叫拍价格+你的加价)*11/10 < 21万两黄金\n"
				HIG"★ 成立，你的叫价才是有效的】\n"
				HIW"------------------------------------------------------\n"NOR);	
			return 1;
		}

		me->set("discredit",me->query("mud_age"));
		me->set_temp("auctioning",1);
		me->start_busy(10);
		v[1] = num + ob_price;
		v[2] = me;
		v[5] = me->query("id");
		str = me->query("name")+"("+me->query("id")+")投标"+v[7]+HIW"，竞价："+MONEY_D->price_str(v[1])+"!\n"NOR;
		auction_chat(str);
		return 1;
	}
	else return help();
}

//控制物品介绍描述，只允许使用中文，以免被写入非法代码
void get_ob_desc(string desc, object me, string str, int num)
{
	int i;
	i = strlen(desc);

	write("\n");
	//物品描述限制为30个汉字(60个字节)
	if (strlen(desc) > 60)
	{
		write("您对物品的介绍太长了，请注意言简意赅。\n");
	        input_to("get_ob_desc", me, str, num);
                return ;
	}
	
	while(i--)
	{
		if( desc[i]<=' ' )
		{
			write("物品的介绍不能使用控制字元。\n");
			input_to("get_ob_desc", me, str, num);
			return ;
		}
		if( i%2==0 && !is_chinese(desc[i..<0]) )
		{
			write("物品的介绍必需是中文。\n");
			input_to("get_ob_desc", me, str, num);
			return ;
		}
	}
	
	write("作为物主，您是否愿意在拍卖过程中透露自己姓名？(y/n)\n");
	input_to("choise_secret", me, str, desc, num);
	return;
}

//开始拍卖的最后检查判断
void choise_secret(string yn, object me, string ob_id, string desc, int num)
{
	mixed *values;	
	string ob_name, onwer_id, str, query_who;
	object ob;

	if (yn[0] != 'y' && yn[0] != 'Y')
		me->set_temp("auction/"+ob_id, "某人");
	else 
		me->set_temp("auction/"+ob_id, me->query("name")+"("+me->query("id")+")");
	
	if(!objectp(ob = present(ob_id, me)))
	{
		tell_object(me,"你身上已经没有这件东西了，不能参加拍卖。\n");
		return;
	}        	
	
	if(sizeof(auction) && member_array(ob_id,keys(auction))!= -1)
	{
		tell_object(me,"你晚了一步，这类物品已经被人抢先拍卖了。\n");
		return;
	}
	
	onwer_id = me->query_temp("auction/"+ob_id);
	query_who = me->query("name")+"("+me->query("id")+")";
	ob_name = ob->short();

	//设置信任属性，判断违反拍卖规则的玩家
	me->set("discredit",me->query("mud_age"));
	me->set_temp("auctioning",1);
	me->start_busy(10);
	
	values = ({ob, num, "", me , desc, "", onwer_id, ob_name, ob->long()});
	auction[ob_id] = values;
	
	str = onwer_id+"现在开始拍卖"+ob_name+HIW"，"+"底价："+MONEY_D->price_str(num)+"。\n";

	//记录拍卖物品名给Tomud协议引用
	write_file("/data/paimai/name",sprintf(ob_name));
	auction_chat(str);
	CHANNEL_D->do_channel( this_object(), "sys", query_who + "现在开始拍卖" + ob_name + HIW"，" + "底价：" + MONEY_D->price_str(num)+"。");
	call_out("auction_state_check", 10, 0, 0, num,ob_id);
	return;
}

//控制底价和竞价上限(设定为10万两)
int player_demand(int num, string unit, object me)
{
	switch(unit)
	{
		case "coin":break;
		case "silver":num*=100;break;
		case "gold":num*=10000;break;
		case "thousand-cash":num*=100000;break;
		case "thousand-gold":num*=10000000;break;
		default:tell_object(me,"非法的货币单位！\n");
		return 0;
	}

	if (num < 10000)	
	{
		tell_object(me,"对不起，本行不支持无底价拍卖，一两黄金是出价底线。\n");	
		return 0;
	}
	
	if (num > 1000000000)
	{
		tell_object(me,"对不起，本行不支持无限高底价拍卖，十万两黄金是出价上限。\n");
		return 0;
	}
	
	return num;
}

//取得买方钱庄存款数目
int player_bank(object ob)
{
	float total;
	
	total = ob->query("money");
	
	if ( ob->query("more_money") )
		total = total + to_float(ob->query("more_money")) * 100000000;
	
	return total;
}

//钱庄转帐方式
int player_pay(object who, int amount)
{
	float all_m;

	seteuid(getuid());

	all_m = who->query("money");
	all_m = all_m + who->query("more_money") * to_float(100000000);

	//竞价失败
	if ( all_m < amount )
		return 0;

	who->add("more_money", -(int)amount / 100000000);

	if ( who->query("money") < amount % 100000000 )
	{
		who->add("more_money", -1);
		who->add("money", 100000000 - (int)amount % 100000000);
	}
	else
		who->add("money", -(int)amount % 100000000);

	tell_object(who,"所需费用已直接从钱庄帐户上扣除。\n\n");
	return 1;
}

int help()
{	
    write(@HELP
	命令格式：
    
　  开启拍卖频道：auction
　  关闭拍卖频道：tune jypm
　　查看目前处于竞拍状态的物品清单：auction -l
　　查看目前处于竞拍状态的物品介绍：auction -m
　　拍卖物品：auction <物品ID> for <底价值> <货币单位>
　　竞拍物品：auction <物品序列号> add <加价值> <货币单位>
    
    说明文档：
　  1. 拍卖过程中采用钱庄转帐方式，所有金额从钱庄帐户里直接转移。	
　　2. 当有人拍卖物品时，拍卖进程正式开始，此时玩家可以以至少1两黄金     	
       的最低差价值参加竞拍，如果一段时间内无人投标，将进行喊价，如果
       三次喊价后仍然无人出价，则拍卖终止。如果一直有人投标，到了规定
       时间，此次拍卖活动仍会被终止。
    3. 拍卖活动终止后，最后出价者为胜，货款从买者手边及钱庄提取，物品
       直接转移到买者身上，如果不堪负重则放在买者所在房间之中，如果房
       间也无法装下，物品作没收处理，切记！物主所得款额直接转至其钱庄
       帐户。整个拍卖活动加收10%的手续费。倘若拍卖过程中始终无人投标，
       拍卖过程宣布失败，手续费恕不退还物主。    
    4. 拍卖过程中，如果因为买卖双方的离开游戏或者物品离开了物主本人，
       导致拍卖进程中断，当作违反拍卖规则处理，责任方信誉度会降低，
       惩罚是一小时内不得参加任何与拍卖有关的活动。倘若拍卖物品三次喊
       价之后因为无人竞标而取消，卖家信誉度也会降低，五分钟内不得再拍
       卖其他物品。
HELP
    );
    return 1;
}
