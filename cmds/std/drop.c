
// drop.c
//sophos
//	add busy state checking for 1 sec at critical code

 
inherit F_CLEAN_UP;

int do_drop(object me, object obj);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj, *inv, obj2;
	int i, amount;
	string item;

	if(!arg) return notify_fail("你要丢弃什麽东西？\n");

	if(sscanf(arg, "%d %s", amount, item)==2) {
		if( !objectp(obj = present(item, me)) )
			return notify_fail("你身上没有这样东西。\n");
		if( stringp(obj->query("no_drop")) )
			return notify_fail( (string)obj->query("no_drop") );
		if( !obj->query_amount() )
			return notify_fail( obj->name() + "不能被分开丢弃。\n");
		if( amount < 1 )
			return notify_fail("东西的数量至少是一个。\n");
		if( amount > obj->query_amount() )
			return notify_fail("你没有那麽多的" + obj->name() + "。\n");
		else if( amount == (int)obj->query_amount() )
			return do_drop(me, obj);
		else {
			//add busy checking here.   - sophos
			if( me->is_busy() )
				return notify_fail("你上一个动作还没有完成！\n");
			me->start_busy(1);
			obj->set_amount( (int)obj->query_amount() - amount );
			obj2 = new(base_name(obj));
			obj2->set_amount(amount);
			return do_drop(me, obj2);
		}
	}

	if(arg=="all") {
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++) {
			do_drop(me, inv[i]);
		}
		write("Ok.\n");
		return 1;
	}

	if(!objectp(obj = present(arg, me)))
		return notify_fail("你身上没有这样东西。\n");
	return do_drop(me, obj);
}

int do_drop(object me, object obj)
{
	mixed no_drop;

	if( !wizardp(me) && no_drop = obj->query("no_drop") )
		return notify_fail( stringp(no_drop) ? no_drop : "这样东西不能随意丢弃。\n");
	
	if( file_name(environment(me)) == "/d/city/wumiao" || file_name(environment(me)) == "/d/wizard/fightroom2" )
		return notify_fail("这里也能随便乱扔东西？");
	if ( playerp(me) && me->query_condition("killer") )
		return notify_fail("你目前正被通缉着，还是不要留下线索为好。\n");

	if (obj->move(environment(me))) {
		if( obj->is_character() )
			message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
		else {

            if ( wizardp(me) && wizhood(me) != "(boss)" ) {
                write(HIG"一只绿色小精灵很快地跑出来，接住你丢下的东西，然后消失不见了！！！\n"NOR);
                destruct(obj); 
                return 1;
            }  
			message_vision( sprintf("$N丢下一%s$n。\n",	obj->query("unit")),
				me, obj );
			if (obj->id("illicit salt"))	me->delete_temp("illicit");
		if( !obj->query("value") && !obj->value() ) {
					if (obj->id("biao yin"))
						write("因为这样东西太值钱，所以很快人们就把它给瓜分了。\n");
					else
						write("因为这样东西并不值钱，所以人们并不会注意到它的存在。\n");
					destruct(obj);
				}
		}
		return 1;
	}
	return 0;
}

int help(object me)
{
	write(@HELP
指令格式 : drop <物品名称>
 
这个指令可以让你丢下你所携带的物品.
 
HELP
    );
    return 1;
}
 
