// dealer.c 商人     write by Fan 12/01/1998
// This is a inheritable object.
// Each dealer should support buy, sell, list, value
// pawn,redeem,check 7 commands

#include <dbase.h>
#include <ansi.h>
string value_string(int value)
{
    if( value < 1 ) value = 1;
    else    if( value < 100 )
        return chinese_number(value) + "文钱";
    else    if( value < 10000 )
        return chinese_number(value/100) + "两白银"
            + (value%100? "又" + chinese_number(value%100) + "文钱": "");
    else
        return chinese_number(value/10000) + "两黄金"
            +( (value%10000)/100 ? chinese_number((value%10000)/100) + "两白银" : "")
            +( (value%10000)%100 ? "又" + chinese_number((value%10000)%100) + "文钱": "");
}
string is_vendor_good(string arg,int once)
{
        string *goods,*all_id;
        int i,j;
        if (goods = query("vendor_goods")) 
        for (i = 0; i < sizeof(goods); i++){
            if (!all_id=goods[i]->parse_command_id_list())
                return "";
            if (goods[i]->query("name")==arg)
                return goods[i];
            for (j=0;j<sizeof(all_id);j++)
                if (all_id[j]==arg)
                    if (goods[i]->id(arg) && once==1)
                        return goods[i];
                    else once--;
        }
        return "";
}
int pay_player(object who, int amount)
{
    object ob;
    int total;
    if( amount < 1 ) amount = 1;
        if( amount/10000 ) {
        if (!ob=present("gold_money", who)){
                    ob = new(GOLD_OB);
            if (!ob->move(who)) ob->move(environment(who));
        }else total=ob->query_amount();
                ob->set_amount(amount/10000+total);
                amount %= 10000;
    }
    if( amount/100 ) {
        if (!ob=present("silver_money", who)){
                    ob = new(SILVER_OB);
            if (!ob->move(who)) ob->move(environment(who));
        }else total=ob->query_amount();
                ob->set_amount(amount/100+total);
        amount %= 100;
    }
    if( amount ) {
        if (!ob=present("coin_money", who)){
            ob = new(COIN_OB);
            if (!ob->move(who)) ob->move(environment(who));
        }else total=ob->query_amount();
                ob->set_amount(amount+total);
    }
    return 1;
}
int vall(object me,string arg)
{
    object ob;
    ob = present(arg, me);
    if( !ob ) ob = present(arg, environment(me));
    if( !ob ) ob = find_object(resolve_path(me->query("cwd"), arg));
    if( !ob ) return notify_fail("没有这样物件或这样物件没有被载入。\n");
    return 1;
}
int do_value(string arg)
{
    object ob;
    int value;
    int amount;
        if (!living(this_object())) return 0;
    if( !arg || !(ob = present(arg, this_player())) )
        return notify_fail("你要拿什麽物品给当铺估价？\n");
    if( ob->query("money_id") )
        return notify_fail("这是「钱」，你没见过吗？\n");
    if (ob->query("shaolin") || ob->query("no_sell")||ob->query("no_drop")) return notify_fail("这东西是无价之宝！\n");
    value = ob->query("value");
    if( !value )
    {
        printf("%s一文不值。\n", ob->query("name"));
        return 1;
    }else 
        if (!amount=ob->query_amount()) amount=1;
        value*=amount;
        if (value<100)
        printf("\n %s%s%s价值%s。\n如果你要典当(pawn)，可以拿到%s。\n如果卖断(sell)，可以拿到%s。\n",
            chinese_number(amount),(ob->query("base_unit")?ob->query("base_unit"):ob->query("unit")),ob->query("name"), value_string(value),
            value_string(value *60/ 100), value_string(value *80/100));
        else
        printf("\n %s%s%s价值%s。\n如果你要典当(pawn)，可以拿到%s。\n如果卖断(sell)，可以拿到%s。\n",
            chinese_number(amount),(ob->query("base_unit")?ob->query("base_unit"):ob->query("unit")),ob->query("name"), value_string(value),
            value_string(value / 100 * 60), value_string(value / 100*80));
    return 1;
}
int do_pawn(string arg)
{
    object ob, *obs;
    string *pawns;
        mapping fam;
    int value, l;
    int amount;
        if (!living(this_object())) return 0;
        if ( (fam=this_player()->query("family")) && fam["family_name"] == "丐帮" ) 
        return notify_fail("你是个穷叫化，当什麽东西！\n");
    if( !arg || !(ob = present(arg, this_player())) )
        return notify_fail("你要典当什麽物品？\n");
    if (ob->query("shaolin"))   return notify_fail(this_object()->name()+"惊呼：小的就一个脑袋，可不敢动少林的亩产！\n");
    if( ob->query("money_id") ) return notify_fail("你要当「钱」？你脑瓜有毛病？\n");
    value = ob->query("value");
    if( !value || ob->query("bind_master_level") )
        return notify_fail("这样东西不值钱。\n");
    if( value<100) return notify_fail("你当我这是垃圾店，什么乱七八糟的东西都往这塞？\n");
    if (ob->query("no_drop") || ob->query("no_sell"))  return notify_fail("这么重要的东西你也敢拿来典当？\n");
	if ( ob->query("xyzx_save_item") && ob->query("owner_id") )
		return notify_fail(this_object()->query("name")+"说道：客官，本店不收这么贵重的物品，小店怕日后担当不起啊。\n");
    pawns=this_player()->query("pawns");
    if (sizeof(pawns)>100)
        return notify_fail(this_object()->query("name")+"说道：客官在本店典当的物品太多了，小店怕日后担当不起。\n");
	
	obs = deep_inventory(ob);
	for ( l=0; l<sizeof(obs); l++ )
	{
		if ( playerp(obs[l]) || obs[l]->is_character() )
			return notify_fail("什么，活物也拿来这里典当？\n");
	}

    if (!amount=ob->query_amount()) amount=1;
    value*=amount;
    if (value<100)
        value=value*60/100;
    else
        value=value/100*60;
    pay_player(this_player(), value);
        message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
        + value_string(value) + "。\n", this_player());
    if (!pawns)
        this_player()->set("pawns",({ base_name(ob) }) );
    else {
        pawns+=({ base_name(ob) });
        this_player()->set("pawns",pawns );
    }
    destruct(ob);
    return 1;
}
int do_sell(string arg)
{
    object ob,obj,*inv, *obs;
    string str, str1, sell_type;
    int value, is_move;
    int amount, i, l, j=1;
      if (!living(this_object())) return 0;
    if( !arg )
        return notify_fail("你要卖断什麽物品？\n");
        if(sscanf(arg, "%d %s", j,str)==2 )
        arg=str;
    if( !(obj = present(arg, this_player())) )
        return notify_fail("你要卖断什麽物品？\n");
    if (j<1) return notify_fail("什么？几个？你当我是三岁小孩呀？\n");
    if( obj->query("money_id") )    return notify_fail("你要卖「钱」？\n");
	// 有绑定级别的装备无法出售
	if ( obj->query("bind_master_level") ) 
	{
		str = obj->query("name");
		destruct(obj);
		tell_object(this_player(), "你把绑定的"+str+"扔给了商铺老板。\n");
		return 1;
	}
    if (obj->query("shaolin"))  return notify_fail(this_object()->name()+"惊呼：小的就一个脑袋，可不敢动少林的亩产！\n");
    if ( ((!obj->query("zhubao_save") && !obj->query("xyzx_save_item") && obj->query("no_sell")) 
		|| obj->query("no_drop"))
		&& !obj->query("bind_master_level") ) 
		return notify_fail("这东西是无价之宝，不能卖断！\n");
	if ( !obj->query("bind_master_level") )
	{
		if (this_object()->query_encumbrance() + obj->weight() > this_object()->query_max_encumbrance())
			return notify_fail("我这货物已经太多了，暂时停止收购。\n");
		if ( this_object()->query_encumbrance() + obj->weight() < 0 )
			return notify_fail("我这货物已经太多了，暂时停止收购。\n");
		if ( this_object()->query_encumbrance() + obj->weight() < this_object()->query_encumbrance() )
			return notify_fail("我这货物已经太多了，暂时停止收购。\n");
		if ( this_object()->query_encumbrance() + obj->weight() < obj->weight() )
			return notify_fail("我这货物已经太多了，暂时停止收购。\n");
	}

	sell_type = this_object()->query("sell_type");
	/* sell_type 值为 
	  1、只收武器
	  2、只收防具
	  3、只收宝石
	  否则只收其他杂物 */
	switch ( sell_type )
	{
		case 1 : 
			if ( !obj->query("weapon_prop/damage") )
				return notify_fail("我这里只收购武器，你可以去其它城市的当铺看看。\n");
			break;
		case 2 : 
			if ( !obj->query("armor_prop/armor") )
				return notify_fail("我这里只收购防具，你可以去其它城市的当铺看看。\n");
			break;
		case 3 : 
			if ( !obj->query("zhubao_save") )
				return notify_fail("我这里只收购悟性宝石，你可以去其它城市的当铺看看。\n");
			break;
		default:
			if ( obj->query("weapon_prop/damage") 
				|| obj->query("armor_prop/armor") 
				|| obj->query("zhubao_save") )
				return notify_fail("我这里不收购装备和悟性宝石，你可以去其它城市的当铺看看。\n");
	}

	obs = deep_inventory(obj);
	for ( l=0; l<sizeof(obs); l++ )
	{
		if ( playerp(obs[l]) || obs[l]->is_character() )
			return notify_fail("什么，活物也拿来这里卖？\n");
	}

	value = obj->query("value");
	if( !value)
	{
        if (!value=obj->query("base_value")) return notify_fail("这样东西不值钱。\n");
	}
	if (!amount=obj->query_amount()) amount=1;
	if ( j>1 && value>100000) return notify_fail("这么多?我可买不起!\n");  
	value*=amount;
	if (value<10000) value=value*80/100;
	else value=value/100*80;
	str = obj->short(1);
	str1 = obj->query("unit")+obj->query("name");
	i=0;
	foreach(ob in all_inventory(this_player()))
	{
		if( ob->short(1)==str)
		{
			if ( ob->move(this_object()) ) is_move = 1;
			inv = all_inventory(this_object());
			if ( sizeof(inv) > 100 ) destruct(inv[random(sizeof(inv))]);
			i++;
			if (i==j) break;
        }
    }
	if ( is_move )
	{
		pay_player(this_player(), value*i);
		message_vision("$N把身上的" + CHINESE_D->chinese_number(i)+str1 + "卖掉"+ value_string(value*i)+"。\n", this_player());
	}
	else
	{
		tell_object(this_player(), HIY"这里似乎并不想收购你的物品。\n"NOR);
		return 1;
	}
	if ( obj && ((obj->query("xyzx_save_item") && obj->query("owner_id")) || obj->query("zhubao_save")) )
		//destruct(obj);
		return 1; // 这里修改为动态物品不销毁，留着给需要的玩家买
	if (obj && (!obj->query("value") || obj->query("value")<100000 )) destruct(obj);
    return 1;
}
object find_player(string target)
{
    foreach (object player in users()){
        if (player->query("id")==target)            return player;
    }
}
int do_check(string arg)
{
    string str,*ob;
    object me,obj;
    int i;
        if (!living(this_object())) return 0;
    me=this_player();
    if (arg){
        if( wizardp(me)) {
            obj = find_player(arg);
            if( !obj ) obj = find_living(arg);
            if( !obj ) obj = present(arg, environment(me));
        }else   return 0;
    }
    if (!objectp(obj))  obj=me;
    if (!(ob = obj->query("pawns")))
        return notify_fail(this_object()->query("name")+sprintf("说道：%s并未在本店典当过任何物品。\n",obj==me?"你":obj->short(1)));
    str="\n"+((obj==me)?"你":obj->query("name"))+"在本店典当的物品如下:\n\n";
    for(i=0;i<sizeof(ob);i++){
        str+=sprintf("%-40s :%s \n",
        ob[i]->short(),
        value_string(ob[i]->query("value")));
    }
    write(str);
    return 1;
}
int do_redeem(string arg)
{
    string *pawns,*new_pawns,ob;
    object obj;
    mapping all_id;
    int i,j;
        if (!living(this_object())) return 0;
    if (!(pawns = this_player()->query("pawns")))
        return notify_fail(this_object()->query("name")+"说道：客官并未在本店典当过任何物品。\n");
    for(i=0;i<sizeof(pawns);i++){
        ob=pawns[i];
        all_id=ob->parse_command_id_list();
        for (j=0;j<sizeof(all_id);j++){
            if (all_id[j]==arg)
                break;
        }   if (j!=sizeof(all_id))
            break;
    }
    if (j==sizeof(all_id))
        return notify_fail(this_object()->query("name")+"急了：你...你何时在小店典当过这东西？\n");
    if( this_player()->can_afford(ob->query("value"),1))
        this_player()->pay_money(ob->query("value"),0);
    else
        return notify_fail("你的钱不够。\n");
    new_pawns=({});
    j=1;
    for(i=0;i<sizeof(pawns);i++){
        if (j==1 && ob==pawns[i]) {
            j--;
            continue;
        }else new_pawns+=({pawns[i]});
    }
        if (sizeof(new_pawns))
            this_player()->set("pawns",new_pawns );
        else
            this_player()->delete("pawns");
    message_vision("$N从当铺里赎回一" + ob->query("unit")
         + ob->query("name") + "。\n",
            this_player() );
    obj=new(ob);
    if (!obj->move(this_player()))  obj->move(environment(this_player()));
    return 1;
}
string inventory_desc(object ob)
{
    if (ob->query("equipped")) return "";
    else return sprintf("  (一%s)%-25s:  %s",
        ob->query("unit"),      ob->short(),
value_string(ob->query("value")));
}
int do_list()
{
        string *goods,nature,respect,rude;
    mapping my;
        object ob,*inv;
        int i,j,amount;
        if (!living(this_object())) return 0;
    inv=all_inventory(this_object());
        if (!sizeof(inv) && !arrayp(goods = query("vendor_goods")))
                return notify_fail("目前没有可以卖的东西。\n");
        nature=NATURE_D->room_event_fun();
	respect=RANK_D->query_respect(this_player());
	rude=RANK_D->query_rude(this_player());
	if(nature=="event_night"){
		message_vision("$N笑着对$n说道:小店刚刚打烊,这位" + respect
		+ "请天亮再来吧。\n", this_object(),this_player());
		return 1;
	}
	if(nature=="event_midnight"){
		message_vision("$N满脸不耐烦对$n说道:"+rude+",半夜三更了还吵什么吵,天亮再来吧。\n", this_object(),this_player());
		return 1;
	}
	if(nature=="event_dawn"){
		message_vision("$N笑着对$n说道:这位" + respect
		+ ",天就要亮了，耐心等等吧。\n", this_object(),this_player());
		return 1;
	}
        if (arrayp(goods = query("vendor_goods")) && sizeof(goods)){
            printf("你可以向%s购买下列物品：\n", query("name"));
                for (i = 0; i < sizeof(goods); i++){
                                        if (replace_string(goods[i]->query("name"),NOR,"")!=goods[i]->query("name"))
                                                     j=-14;
                                            else
                                                     j=0;
                        printf("%s：%s\t\t%s\n", goods[i]->short(),strlen(goods[i]->short())+j>13?"":"\t",
            value_string(goods[i]->query("value")));
                          }
            return 1;
    }
    delete("my");
    ob=first_inventory(this_object());
        while(ob){
                if (ob->query("equipped") || ob->query("money_id")){
            ob = next_inventory(ob);
            continue;
        }
        if (!mapp(my=query("my")))
		{
			if ( ob->query("xyzx_save_item") && ob->query("owner_id") )
				set("my",([ob:1]));
			else
				set("my",([base_name(ob):1]));
		}
        else
		{
			if ( ob->query("xyzx_save_item") && ob->query("owner_id") )
			{
				amount=my[ob];
				my[ob]=amount+1;
			}
			else
			{
				amount=my[base_name(ob)];
				my[base_name(ob)]=amount+1;
			}
        }
        ob = next_inventory(ob);
    }
    if (!mapp(my=query("my")))
    return notify_fail("目前没有可以卖的东西。\n");
        printf("你可以向%s购买下列物品：\n", query("name"));
        inv=keys(my);
        printf(NOR YEL"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"NOR);
        for (i=0;i<sizeof(my);i++)
        {
                     if (replace_string(inv[i]->query("name"),NOR,"")!=inv[i]->query("name"))
                        j=-14;
                     else
                        j=0;
            printf("%" + sprintf("  %d", (30 + color_len(inv[i]->short())))+"s：%s%s%s(共有：%s%s)\n", inv[i]->short(),strlen(inv[i]->short())+j>13?"":"\t",
            value_string(inv[i]->query("value")),strlen(value_string(inv[i]->query("value")))>13?"":"\t",
            CHINESE_D->chinese_number(my[inv[i]]),
            inv[i]->query("unit")
            );
        }
        printf(NOR YEL"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"NOR);
    return 1;
}      

int do_buy(string arg)
{
    string items,targ;
    object dest,ob, owner,obj;
        mapping fam;
    int price, i,amount=1;
    int once=1;
        if (!living(this_object())) return 0;
           if(NATURE_D->room_event_fun()=="event_night") 
	{
		message_vision("$N笑着对$n说道:本店刚打烊，请明天再来吧。\n",this_object(),this_player());
		return 1;
	}
     if(NATURE_D->room_event_fun()=="event_midnight") 
	{
		message_vision("$N满脸的不耐烦对$n说道:半夜三更的，吵什么吵，天亮再来!\n", this_object(),this_player());
		return 1;
	}
	if(NATURE_D->room_event_fun()=="event_dawn") 
	{
		message_vision("$N笑着对$n说道:天就要亮了，您耐心等等吧。\n",this_object(),this_player());
		return 1;
	}
        dest=this_player();
    reset_eval_cost();
      
        if ( (fam=dest->query("family")) && fam["family_name"] == "丐帮" ) 
        return notify_fail("你是个穷叫化，买什麽东西！\n");
    targ="";
    if ( !arg )
        return notify_fail("你要买什么东西？\n");
        if(sscanf(arg, "%d %s %d from %s",amount,items,once, targ)!=4 )
            if(sscanf(arg, "%d %s from %s",amount,items, targ)!=3 )
            if(sscanf(arg, "%s %d from %s", items,once,targ)!=3 )
        if( sscanf(arg, "%d %s %d",amount,items,once)!=3 )
                if(sscanf(arg, "%s from %s", items, targ)!=2 )
            if( sscanf(arg, "%d %s",amount,items)!=2 )
            if( sscanf(arg, "%s %d",items,once)!=2 )
                items=arg;
    if(targ=="")
        owner=this_object();
    else    if (!objectp(owner = present(targ, environment(dest))) )
        return notify_fail("你要跟谁买东西？\n");
          if (owner!=this_object()) return notify_fail("你要跟谁买东西？\n");
    arg=items;
    items = is_vendor_good(arg,once);
    if (items == ""){
            if (!objectp(obj=present(arg, owner)))
                return notify_fail("你想买什么？ \n");
    }
    if(amount<1) return notify_fail("至少得买一个吧？\n");
    if(amount>30) return notify_fail("你一次不能买这么多。\n");
if (amount>1 && items->query("value",1)>=10000000)  	
return notify_fail("这么贵重的东西,还是单个交易的好。\n");	
    if (items == ""){
        if (obj->query("equipped")||obj->query("money_id"))
            return notify_fail(owner->query("name")+"气冲冲地说：身上的东西，不卖！\n");
        price=obj->query("value");
    }else{
        price=items->query("value");
    }
    if( dest->can_afford(price*amount) ) {
        reset_eval_cost();
        for (i=0;i<amount;i++){
            if (items == ""){
             targ=obj->short(1);
                foreach (ob in all_inventory(owner)){
                    if (!ob || ob->short(1)!= targ) continue;
                   if (ob->query_amount()>1){
                        ob->add_amount(-1);
                       obj=new(base_name(ob));
                if (!obj->move(dest)) obj->move(environment(dest));
                }else
                if (!ob->move(dest)) ob->move(environment(dest));
                    i++;
                    if (i == amount) break;
                }
                break;
            } else{
                ob=new(items);
                if (!ob->move(dest)) ob->move(environment(dest));
            }
        }
        amount=i;
        dest->pay_money(price*amount);
        if (items == "")
            message_vision("$N向$n买下" +CHINESE_D->chinese_number(amount)+obj->query("unit") + obj->query("name") + "。\n",dest, owner );
        else{
            if (amount>9 && items->query("name")=="牛皮酒袋")
                message_vision("$N一边转身去装酒，嘴里一边嘀咕：买这么多酒，用来洗澡呀？\n",owner );
            message_vision("$N向$n买下" +CHINESE_D->chinese_number(amount)+items->query("unit") + items->query("name") + "。\n",dest, owner );
        }
        return 1;
    } else
        return notify_fail("你的钱不够。\n");
}

int do_look_item(string arg)
{
	object me, ob, *inv;
	string id;
	int i, flag, max, find;

	me = this_player();
	if ( !me ) return 0;
	ob = this_object();
	inv = all_inventory(ob);
	max = sizeof(inv);
	if ( max < 2 ) return notify_fail("目前没有可出售的物品。\n");
	if ( !arg ) return notify_fail("你要查看哪件物品的属性？\n");
	if ( !sscanf(arg, "%s,%d", id, flag) )
	{
		id = arg;
		flag = 1;
	}
	for ( i=0; i<max; i++ )
	{
		if ( inv[i]->query("equipped") || inv[i]->query("money_id") ) continue;
		if ( inv[i]->query("id") == id ) 
		{
			find++;
			if ( find == flag )
			{
				"/cmds/std/look"->look_item(me, inv[i]);
				return 1;
			}
		}
	}
	tell_object(me, "你要查看哪件物品的属性？\n");
	return 1;
}