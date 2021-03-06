// move.c by Wenwu On 2003.06.21

#include <dbase.h>
#include <room.h>
#include <liebiao.h>

int room_outs_tomud(object me, object ob);

nosave int weight = 0;
nosave int encumb = 0, max_encumb = 0;
// 查询携带物品的重量
nomask int query_encumbrance()
{
	return encumb;
}
// 超重
nomask int over_encumbranced()
{
	return encumb > max_encumb;
}
//负重百分比
nomask int than_encumbranced()
{
	int than_encumb;
	
	than_encumb = encumb * 100 / max_encumb;
	if ( than_encumb < 0 ) than_encumb = 0;
	if ( than_encumb > 100 ) than_encumb = 100;

	return than_encumb;
}
// 查询能携带物品的最大重量
nomask int query_max_encumbrance()
{
	return max_encumb;
}
// 记录能携带物品的最大重量
nomask void set_max_encumbrance(int e)
{
	max_encumb = e;
}
// 增加重量
nomask void add_encumbrance(int w)
{
	encumb += w;
	
	if( encumb < 0 ){
		log_file("move.bug", sprintf("%O encumbrance underflow.\n", this_object()));
	}
	if( encumb > max_encumb )
		this_object()->over_encumbrance();
	
	if( environment() )
		environment()->add_encumbrance(w);
}

void over_encumbrance()
{
	if( !interactive(this_object()) )
		return;
	
	tell_object(this_object(), "你的负荷过重了！\n");
}

nomask int query_weight()
{
	return weight;
}
nomask void set_weight(int w)
{
	if( !environment() )
	{
		weight = w;
		return;
	}
	
	if( w!=weight )
		environment()->add_encumbrance( w - weight );
	
	weight = w;
}

// This is the "current" weight of an object, which is used on weight
// checking in move().
nomask int weight()
{
	return weight + encumb;
}

varargs int move(mixed dest, int silently)
{
	object me, ob, env, obj;
	mapping exits, my, is_bind;
	string str, *dirs;
	int i;

	me = this_object();
	
	//If we are equipped, unequip first.
	if( query("equipped") && !this_object()->unequip() )
        return notify_fail("你没有办法取下这样东西。\n");
	
	//Find the destination ob for moving.
	if( objectp(dest) )
		ob = dest;
	else if( stringp(dest) )
	{
		//call_other(dest, "???");
        ob = load_object(dest);
		if(!ob)
			return notify_fail("move: destination unavailable.\n");
    }
	else
		return notify_fail(sprintf("move: invalid destination %O.\n", dest));

	// 绑定的物品无法交易
	if ( environment(this_object()) 
		&& mapp(is_bind = this_object()->query("bind_master_level")) 
		&& !is_bind[ob->query("id")])
		return notify_fail("绑定的物品无法交易。\n");
    
	//Check if the destination ob can hold this object.
	//Beforce checking it, we check if the destination is environment of
	//this_object() (or environment of its environment). If it is, then
	//this could be like get something from a bag carried by the player.
	//Since the player can carry the bag, we assume he can carry the this
	//object in the bag and encumbrance checking is unessessary.
	
	env = this_object();
	
	while ( env = environment(env) )
	{
		if( env==ob )
			break;
	}

	if( !env )
	{
		// 首先检查负重，目标OBJ无法能容纳得下时的处理
		if( (int)ob->query_encumbrance() + weight() > (int)ob->query_max_encumbrance() )
		{
			// 目标OBJ有环境，则移动到环境
			if ( environment(ob) && !wizardp(ob) )
			{
				tell_room(environment(ob), "由于"+this_object()->name()+"对于"+ob->name()+"而言实在是太重了，只好先扔在一旁。\n");
				ob = environment(ob);
			} else if( ob == this_player() ) // 对目标玩家提示信息
				return notify_fail( this_object()->name() + "对你而言太重了。\n");
			else
				return notify_fail( this_object()->name() + "对" + ob->name() + "而言太重了。\n");
		} else if ( playerp(ob) && sizeof(all_inventory(ob)) > 50 ) // 检查目标玩家OBJ身上携带物件数目是否超过50
		{
			// 该玩家所处环境存在，则移动到环境
			if ( environment(ob) && !wizardp(ob) )
			{
				tell_room(environment(ob), "由于"+this_object()->name()+"对于"+ob->name()+"而言实在是太多了，只好先扔在一旁。\n");
				ob = environment(ob);
			}
			else if( ob == this_player() )
			{
				tell_object(ob, "你身上的东西太多了！\n");
				return notify_fail( this_object()->name() + "对你而言太多了。\n");
			}
			else
				return notify_fail( this_object()->name() + "对" + ob->name() + "而言太多了。\n");
		}
	}
	
	// Move the object and update encumbrance
	if ( env = environment() )
	{
		//_________________________限制低级巫师给予东西______________________
		if ( playerp(env) )
		{ 
			if ( ob->is_character() )
			{ // 从玩家 ---> 其他生物
				if ( wizardp(env) && wiz_level(env) < 9 && !wizardp(ob) )
				{ // 是巫师，且巫师等级 < 9，也就是 admin 权限以下的
					if ( me->query("is_wiz_level") )
					{
						tell_object(env, "您是巫师，请遵守好巫师守则不要随意交易东西！\n");
						return 0;
					}
				}
			}
		}
		//________________________________END________________________________
		// 玩家从擂台出来清除战斗伤害参数
		if ( playerp(me) )
		{
			if ( base_name(env) == "/d/wizard/fightroom3" 
				|| base_name(env) == "/d/wizard/fightroom2" )
			{
				me->delete_temp("last_unconcious_from");
				me->delete_temp("last_damage_from");
			}
		}
		env->add_encumbrance( - weight());
	}
	
	//Tomud列表删除
	if ( me && ob )
	{
		//对env重新赋值，作用域仅限于该程式，被指定为this_object()原来所在的环境
		//env = environment(this_object());
		
		if ( env )
		{
			//过滤，只传回目前的可互动物件
			if(interactive(env)) 
			{
				if(!env->query("xieyi/zmud"))
				{
					//删除物品栏里的列表图标
					tell_object(env,REM1(this_object()));
				}
			}
			else if(!env->is_character())
			{
				object *temp;
				//只搜索同环境下的所有物件，比原来的users()效率高多了
				temp=all_inventory(env);
				for(i=0;i<sizeof(temp);i++)
				{
					if (temp[i] == this_object())
						continue;

					if(environment(temp[i]) == env)
					{
						if(!temp[i]->query("xieyi/zmud"))
						{
							if (interactive(temp[i]))
							tell_object(temp[i],REM0(this_object()));
						}
					}
				}
			}
		}
	}
	
	// RPG系统特殊处理
	//if ( !clonep(ob) || virtualp(ob) ) ob->xyzx_system_clean_up();
	// Add by Wenwu
	if ( !this_object() ) return 0;
	// 物品获取绑定
	if ( this_object()->query("xyzx_sys/bind_type") == 2 && playerp(ob) )
	{
		this_object()->set("bind_master_level/"+ob->query("id"), 2);
		this_object()->set("owner_id", 1);
		this_object()->set("xyzx_save_item", 1);
	}

	move_object(ob);
	
	// 动态物品即时保存
	// ----------------------------------------------
	if ( objectp(env) )
	{
		if ( this_object()->query("xyzx_save_item") && this_object()->query("owner_id") )
		{
			if ( playerp(env) ) env->save_item_call(); // 动态物品从玩家身上移开时更新数据库
			if ( playerp(ob) ) ob->save_item_call(); // 动态物品移动到玩家身上时更新数据库
		}

		if ( playerp(this_object()) )
		{
			if ( base_name(ob) == VOID_USER )
			{
				this_object()->set_temp("move_temp_room", base_name(env));
			}
		}
		else if ( this_object()->is_character() )
			this_object()->delete("env/no_combat_msg");
	}
	else
	{
		if ( playerp(ob) )
		{
			if ( this_object()->query("xyzx_save_item") && this_object()->query("owner_id") )
				ob->save_item_call(); // 动态物品移动到玩家身上时更新数据库
		}
	}
	// ----------------------------------------------

	//Tomud列表图标增加
	if (this_object() && ob)
	{
		//ob->add_encumbrance(weight());
		//当移动到玩家身上时，在玩家物品栏里增加列表图标
		if(interactive(ob))
		{
			if(!ob->query("xieyi/zmud"))
			{
				//巫师如果不想让人看到自己可以把隐身等级设置为10，则不增加列表，保留了巫师的隐形效果，
				if(!(wizardp(this_object()) && this_object()->query("env/invisibility") == 10))
					//向玩家物品栏增加一项列表图标
					tell_object(ob,ADD1(this_object()) );
			}
		}
		//当移动到一个环境时，则在这个环境里的所有玩家的人物栏里添加列表图标
		else if(!ob->is_character())
		{
			object *temp;
			//增加过滤，指定增加列表的目标提高执行效率
			temp=all_inventory(ob);
			for(i=0;i<sizeof(temp);i++)
			{
				if (temp[i] == this_object())
					continue;

				if ( sizeof(temp) > 50 )
				{
					if ( !temp[i]->is_character() && temp[i]->query("startroom") != base_name(this_object()) )
						continue;
				}

				if(environment(temp[i]) == ob)
				{
					if(!temp[i]->query("xieyi/zmud"))
					{
						if(!(wizardp(this_object()) && this_object()->query("env/invisibility") == 10))
						{
							//过滤，只传回目前的可互动物件
							if (interactive(temp[i]))
								tell_object(temp[i],ADD0(this_object()));
						}
					}
				}
			}
		}
	}
    
	ob->add_encumbrance(weight());
    
	//If we are players, try look where we are.
    if( interactive(this_object()) && living(this_object()) && objectp(env=environment()) && !silently )
	{
		ob=this_object();
		
		if(!intp(query("env/brief")))
			set("env/brief",0);
		
		if((int)query("env/brief") == 1 )
		{
			room_outs_tomud(ob, environment());
			tell_object(ob, HIW+environment()->query("short") +NOR+ "\n");
		}
		else if ( (int)query("env/brief") == 2 )
		{
			str=NOR+"\n";
			exits = environment()->query("exits");
			
			if( !sizeof(exits) )
				str += "    这里没有任何明显的出路。\n";
			else
			{
				dirs = keys(exits);
				for(i=0; i<sizeof(dirs); i++)
				if( (int)environment()->query_door(dirs[i], "status") & DOOR_CLOSED )
					dirs[i] = 0;
				dirs -= ({ 0 });
				
				if( !sizeof(dirs))
					str += "    这里没有任何明显的出路。\n";
				else if( sizeof(dirs)==1 )
					str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
				else
					str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
			}
			
			if ( (int)query("env/brief")==2 )
			{
				tell_object(ob, HIW+environment()->query("short") +str+NOR+ "\n");
			}
			else
			{
				obj=first_inventory(env);
				while(obj)
				{
					reset_eval_cost();
					
					if (obj==this_object() || !this_object()->visible(obj))
					{
						obj = next_inventory(obj);
						continue;
					}
					
					if (obj->query("money_id") || !obj->query("unit") || obj->is_character())
					{
						str+=sprintf("    %s\n",obj->short());
						obj = next_inventory(obj);
						continue;
					}
					
					if (!mapp(my))
						my=([obj->query("unit")+obj->short():1]);
					else
					{
						i=my[obj->query("unit")+obj->short()];
						my[obj->query("unit")+obj->short()]=i+1;
					}
					obj = next_inventory(obj);
				}
				if (mapp(my))
				{
					dirs=keys(my);
					for (i=0;i<sizeof(my);i++)
						str+=sprintf("    %s%s\n",my[dirs[i]]==1?"":CHINESE_D->chinese_number(my[dirs[i]]),my[dirs[i]]==1?dirs[i][2..]:dirs[i]);
				}
				
				tell_object(ob, HIW+environment()->query("short") +str+NOR+ "\n");
			}
			
			room_outs_tomud(ob, environment());
		}
		else if ( (int)query("env/brief") == 3 )
		{
			command("maphere -min");
			room_outs_tomud(ob, environment());
		}
		else
		{
			//command("look");
			"/cmds/std/look"->main(ob);
			room_outs_tomud(ob, environment());   
		}
	}
        
	return 1;
}

void remove(string euid)
{
	object default_ob;
	
	// 呼叫此函式的不是 SIMUL_EFUN_OB 
	if( !previous_object() || base_name(previous_object()) != SIMUL_EFUN_OB )
		error("move: remove() can only be called by destruct() simul efun.\n");
	// 没有 this_object() 
	if ( !objectp(this_object()) )
		return;
	// 没有 default_ob 对象
	if( objectp(default_ob = this_object()->query_default_object()) )
		default_ob->add("no_clean_up", -1);	
	// this_object() 是被装备着的装备，尝试御除装备
	if( this_object()->query("equipped"))
	{
		if( !this_object()->unequip() )
			log_file("destruct", sprintf("Failed to unequip %s when destructed.\n",file_name(this_object())));
	}
    
	// We only care about our own weight here, since remove() is called once
	// on each destruct(), so our inventory (encumbrance) will be counted as
	// well.
	
	// 有环境
	if( environment() )
	{
		// 减去 this_object() 的重量
		environment()->add_encumbrance( - weight );
		// 是玩家保存档案
		/*if ( playerp(this_object()) )
			this_object()->save();*/
	}
	return;
}

int move_or_destruct( object dest )
{
	if ( playerp(this_object()) )
	{	
		tell_object(this_object(), "一阵时空的扭曲将你传送到另一个地方....\n");
		move(VOID_USER);

		if ( stringp(this_object()->query_temp("move_temp_room")) )
		{
			this_object()->apply_condition("move", 1);
		}
	}
}

int room_outs_tomud(object me, object ob)
{
	mapping exits;
	string *outs, msg;
	object *inv;
	int i;

	if ( me->query("xieyi/zmud") )
		return 0;

	msg = "" + CLEAN0;
	inv = all_inventory(ob);
	for ( i = 0; i < sizeof(inv); i++ )
	{		
		if ( !inv[i]->query_temp("check_only") && inv[i] != me && me->visible(inv[i]) )
		{
			if ( i > 50 )
			{
				if ( inv[i]->is_character() || inv[i]->query("startroom") == base_name(ob) )
					msg += ADD0(inv[i]);
			}
			else
				msg += ADD0(inv[i]);
		}
	}

	if ( mapp(exits = ob->query("exits")) )
	{
		if ( sizeof(exits) < 1 )
			msg += ADDWAY("");
		else
		{
			outs = keys(exits);
			i = sizeof(outs);
			msg += ADDWAY(""); // 先清除下原来的方向键
			msg += ADDWAY(implode(outs[0..i - 1], ";"));
		}
	}
	else
		msg += ADDWAY("");
	
	if ( me->query("env/myhp_show") )
		msg += ROOMNAME(filter_color(ob->query("short")));

	tell_object(me ,msg);
	return 1;
}