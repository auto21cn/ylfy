// 闭关系统 By Wenwu On 2006.7.22

#include <ansi.h>

inherit F_DBASE;
inherit F_SAVE;

// 心跳
#define MAX_HEART_DOING 1
// 每次的最大操作数
#define MAX_CMD_DOING_OB 5
// 离线练功指令执行间隔时间 (取随机值)
#define SPACE_TIME_SEC 2
#define BIGUN_DATA "/data/biguan/离线修炼.o"
#define XIULIAN_POT_COST 0

// 闭关玩家
mapping bg_users = ([]);
// biguan玩家
nosave object *biguan_obs = ({});
// 等待中队列
nosave object *lixian_wait = ({});
// 操作完成的队列
nosave object *lixian_finish = ({});
nosave int doing_flag = 0;

// 内部使用函数
int load_all_users();
void xiulian_doing();
int del_breaking_user(object ob);
int breaking(object me);
// 外部使用函数
int add_bg_user(object ob);
varargs int del_bg_user(object ob, int localcall);
int add_breaking_user(object ob);

string query_save_file()
{
	return BIGUN_DATA;
}

int clean_up()
{
	set_heart_beat(MAX_HEART_DOING);
	return 1;
}

void create()
{
	seteuid( ROOT_UID );
	set("channel_id", "修炼精灵");
	CHANNEL_D->do_channel( this_object(), "sys", "修炼精灵已经启动。\n"NOR);
	
	if ( file_size(BIGUN_DATA) > 0 )
		restore();

	load_all_users();
	/*remove_call_out("xiulian_doing");
	call_out("xiulian_doing", 3 + random(3));
	remove_call_out("breaking_doing");
	call_out("breaking_doing", 3);*/
	set_heart_beat(MAX_HEART_DOING);
}

int load_all_users()
{
	object user;
	string *bg_ob, room, xy_hy;
	int i;

	if ( !mapp(bg_users) )
	{
		bg_users = ([]);
		return 0;
	}

	if ( !sizeof(bg_users) ) return 0;

	if ( !arrayp(lixian_wait) ) lixian_wait = ({});

	CHANNEL_D->do_channel( this_object(), "sys", "开始读取离线修炼玩家列。\n"NOR);
	bg_ob = keys(bg_users);
	for ( i=0; i<sizeof(bg_ob); i++ )
	{
		if ( user = find_player(bg_ob[i]) )
		{
			if ( !user->query("lixian/biguan") )
			{
				del_bg_user(user);
			}
			else if ( objectp(user) ) 
				lixian_wait += ({ user });
			continue;
		}

		user = new(USER_OB);
		seteuid(bg_ob[i]);
		export_uid(user);
		
		user->set_name("玩家", ({ bg_ob[i] }));
		
		if ( !user->restore() )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}

		user->setup();

		if ( !user->query("lixian/biguan") )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}

		room = user->query("startroom");
		
		if ( user->move(room) )
			UPDATE_D->check_user(user, 3);
		else
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}

		if ( !playerp(user) )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}

		if ( user->query("block") )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}
		// 效验会员有效期
		if ( stringp(xy_hy = user->query("xy_huiyuan")) )
		{
			if ( sscanf(xy_hy, "%*s年%*s月%*s日") )
				"/feature/vip"->del_vip(user, xy_hy);
			else
			{
				user->delete("xy_huiyuan");
				user->delete("xyhy_type");
			}
		}
		else
		{
			user->delete("xy_huiyuan");
			user->delete("xyhy_type");
		}
		// 非会员不予离线练功资格
		if ( !user->query("xy_huiyuan") )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}
		// 免费会员不予离线练功资格
		/*if ( !user->query("xyhy_type") )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}*/
		// 杀人犯不让离线
		if ( user->query_condition("killer") )
		{
			del_bg_user(user);
			destruct(user);
			continue;
		}
		if ( objectp(user) ) lixian_wait += ({ user });
		user->delete("exp_jiacheng"); // 清除领取的双倍经验属性
	}
	
	save();
	CHANNEL_D->do_channel( this_object(), "sys", "读取完毕。\n"NOR);
	return 1;
}

int add_bg_user(object ob)
{
	string id;

	if ( !objectp(ob) ) return 0;
	if ( !playerp(ob) ) return 0;
	if ( !ob->query("lixian/biguan") ) return 0;
	if ( ob->query("block") ) return 0;

	if ( !mapp(bg_users) )
		bg_users = ([]);

	id = ob->query("id");
	bg_users[id] = 1;
	save();
	if ( !arrayp(lixian_wait) ) lixian_wait = ({});
	if ( member_array(ob, lixian_wait) == -1 ) lixian_wait += ({ ob });
	set_heart_beat(MAX_HEART_DOING);
	return 1;
}

varargs int del_bg_user(object ob, int localcall)
{
	string id;

	if ( !mapp(bg_users) )
	{
		bg_users = ([]);
		return 0;
	}
	if ( !sizeof(bg_users) ) return 0;
	if ( !objectp(ob) ) return 0;
	if ( ob->query("lixian/biguan") )
	{
		ob->delete("lixian/biguan");
		ob->save();
	}

	id = ob->query("id");
	map_delete(bg_users, id);
	save();
	if ( !localcall && arrayp(lixian_wait) ) lixian_wait -= ({ ob });
	return 1;
}

void xiulian_doing()
{
	string cmd, xy_hy;
	int i, max, grant;

	if ( !arrayp(lixian_wait) ) lixian_wait = ({});
	if ( !arrayp(lixian_finish) ) lixian_finish = ({});
	lixian_wait += lixian_finish;
	lixian_finish = ({});
	lixian_wait -= ({ 0 });
	if ( !(max=sizeof(lixian_wait)) ) return;
	if ( max < MAX_CMD_DOING_OB ) grant = max;
	else grant = MAX_CMD_DOING_OB;

	for ( i=0; i<grant; i++ )
	{
		if ( i >= sizeof(lixian_wait) ) break;
		if ( !objectp(lixian_wait[i]) ) continue;
		else lixian_finish += ({ lixian_wait[i] });
		if ( !environment(lixian_wait[i]) )
		{
			del_bg_user(lixian_wait[i], 1);
			destruct(lixian_wait[i]);
			continue;
		}
		if ( interactive(lixian_wait[i]) )
		{
			del_bg_user(lixian_wait[i]);
			continue;
		}
		// 不是修炼的
		if ( !lixian_wait[i]->query("lixian/biguan") ) 
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 无心跳的
		if ( !query_heart_beat(lixian_wait[i]) )
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 关监的
		if ( lixian_wait[i]->query("block") )
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 杀人犯
		if ( lixian_wait[i]->query_condition("killer") )
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 效验会员有效期
		if ( stringp(xy_hy = lixian_wait[i]->query("xy_huiyuan")) )
		{
			if ( sscanf(xy_hy, "%*s年%*s月%*s日") )
				"/feature/vip"->del_vip(lixian_wait[i], xy_hy);
			else
			{
				lixian_wait[i]->delete("xy_huiyuan");
				lixian_wait[i]->delete("xyhy_type");
			}
		}
		else
		{
			lixian_wait[i]->delete("xy_huiyuan");
			lixian_wait[i]->delete("xyhy_type");
		}
		// 非会员不予离线练功资格
		if ( !lixian_wait[i]->query("xy_huiyuan") )
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 免费会员需要消耗潜能
		if ( !lixian_wait[i]->query("xyhy_type") 
			&& lixian_wait[i]->query("potential") < XIULIAN_POT_COST )
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 在线多长时间就只能离线挂多少时间，心跳算
		if ( lixian_wait[i]->query("biguan_is_online") < 1 
			/*&& lixian_wait[i]->query("xyhy_type") != 2*/ )//解决无法离线的问题
		{
			del_bg_user(lixian_wait[i], 1);
			lixian_wait[i]->save();
			destruct(lixian_wait[i]);
			continue;
		}
		// 有busy的
		if ( lixian_wait[i]->is_busy() ) continue;
		// 无法活动的
		if ( lixian_wait[i]->query_temp("block_msg") ) continue;
		if ( !living(lixian_wait[i]) ) continue;
		// 缓存区有未执行完的指令
		if ( stringp(cmd=lixian_wait[i]->query_temp("chufa_buffer")) )
		{
			lixian_wait[i]->do_xyzx_chufa(cmd);
			continue;
		}
		// 如果有触发执行触发
		if ( lixian_wait[i]->query_temp("xyzx_sys_chufa") )
		{
			if ( !stringp(cmd = lixian_wait[i]->query_temp("xyzx_sys_chufa")) )
			{
				lixian_wait[i]->delete_temp("xyzx_sys_chufa");
				continue;
			}

			lixian_wait[i]->delete_temp("xyzx_sys_chufa");
			lixian_wait[i]->do_xyzx_chufa(cmd);
			continue;
		}
		// 执行计划
		lixian_wait[i]->do_xyzx_xiulian();
		// 免费会员消耗潜能
		if ( lixian_wait[i]->query("xyhy_type")!=2 )
			lixian_wait[i]->add("potential", -XIULIAN_POT_COST);
	}

	lixian_wait -= lixian_finish;
	lixian_wait -= ({ 0 });
	/*remove_call_out("xiulian_doing");
	call_out("xiulian_doing", random(SPACE_TIME_SEC));*/
	return;
}

int add_breaking_user(object ob)
{
	if ( !interactive(ob) ) return 0;
	if ( ob->query("breakup") ) return 0;
	if ( ob->query_temp("breakuping") ) return 0;

	if ( !pointerp(biguan_obs) )
		biguan_obs = ({});
	
	biguan_obs += ({ ob });
	ob->set_temp("breakuping", 1);
	set_heart_beat(MAX_HEART_DOING);
	return 1;
}

int del_breaking_user(object ob)
{
	if ( !pointerp(biguan_obs) )
	{
		biguan_obs = ({});
		return 0;
	}

	if ( !sizeof(biguan_obs) ) return 0;
	if ( !objectp(ob) ) return 0;
	
	biguan_obs -= ({ ob });
	return 1;
}

void breaking_doing()
{
	int i;

	if ( !arrayp(biguan_obs) )
	{
		biguan_obs = ({});
		/*remove_call_out("breaking_doing");
		call_out("breaking_doing", 3);*/
		return;
	}

	if ( !sizeof(biguan_obs) )
	{
		/*remove_call_out("breaking_doing");
		call_out("breaking_doing", 3);*/
		return;
	}

	for ( i = 0; i < sizeof(biguan_obs); i++ )
	{
		if ( !objectp(biguan_obs[i]) ) continue;
		if ( !biguan_obs[i]->query_temp("breakuping") ) continue;
		if ( biguan_obs[i]->query("breakup") ) continue;
		breaking(biguan_obs[i]);
		
	}

	/*remove_call_out("breaking_doing");
	call_out("breaking_doing", 3);*/
	return;
}

int breaking(object me)
{
	string msg;
	
	if ( !interactive(me) )
	{
		me->delete_temp("breakuping");	
		del_breaking_user(me);
		return 0;
	}
	if ( me->query("block") )
	{
		me->delete_temp("breakuping");	
		del_breaking_user(me);
		return 0;
	}
	if ( me->is_ghost() )
	{
		me->delete_temp("breakuping");	
		del_breaking_user(me);
		return 0;
	}
	if ( me->query("potential") < 15 )               	
	{
		tell_object(me, "你的潜能不够了。\n");	
		me->delete_temp("breakuping");	
		me->set("potential",0);
		del_breaking_user(me);
		message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
		message("channel:chat", HIY"【镜花水月】"+HIM"听说"+me->query("name")+HIM"闭关结束,似乎没有太大的进展！\n"NOR,users() );
		return 0;
	}
	if ( me->query_temp("netdead") || me->query("lixian/biguan") )               	
	{
		me->delete_temp("breakuping");	
		//me->set("potential",0);
		del_breaking_user(me);
		message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
		message("channel:chat", HIY"【镜花水月】"+HIM"听说"+me->query("name")+HIM"闭关中途突然复出,似乎没有太大的进展！\n"NOR,users() );
		return 0;
	}

	me->add("potential",-5);	

	if (random(500000) < me->query("con") && !me->query("breakup"))
	{
		message_vision(HIW "只见$N" HIW "头上白雾腾腾、浑身如同笼罩在云中，看来已经到了三花聚顶、五气朝元、龙虎相济、天人交会的紧要关头！\n" NOR, me);
		tell_object(me, HIR "你觉得内力在丹田源源而生，不断冲击诸处大穴，浑身燥热难当，几欲大声呼喊。\n" NOR);
		message_vision(HIC "突然$N" HIC "大喝一声，一股无形气浪陡然散布开来，四周空气登时变得燥热。\n" NOR, me);
		tell_object(me, HIG "你顿时觉得浑身一阵轻松，一股清凉之意油然而起，心灵一片空明，内力没有丝毫阻滞，舒泰之极。\n" NOR);
		me->delete_temp("breakuping");
		me->set("breakup", 1);
		message("channel:chat", HIY"【镜花水月】"+HIM"听说"+me->query("name")+HIM"经过闭关苦修,终于打通了任督二脉,窥视到了无上的武学境界！\n"NOR,users() );	
		me->add("max_jingli",me->query("max_jingli")/10);             	
		me->add("max_neili",me->query("max_neili")/10);
		me->set_skill("force",me->query_skill("force",1)+100);
		del_breaking_user(me);
		return 1;
	}

	switch ( random(5) ) 	
	{
		case 0:
				msg = "你默默运转内力，隐隐有些感觉。\n";    	
				break;
		case 1:
				msg = "你将内力运出丹田，过紫宫、入泥丸、透十二重楼，遍布奇筋八脉，然后收回丹田。\n";  	
				break;
		case 2:
				msg = "你将内力运经诸穴，抵四肢百赅，然后又回收丹田。\n"; 	
				break;
		case 3:
				msg = "你在丹田中不断积蓄内力，只觉得浑身燥热。\n";
				break;
		default:
				msg = "你缓缓呼吸吐纳，将空气中水露皆收为己用。\n";
	}
	
	me->start_busy(15);
	tell_object(me, msg);
	return 1;
}

object *query_all_lixian_wait()
{
	return lixian_wait;
}

object *query_all_lixian_finish()
{
	return lixian_finish;
}

void remove()
{
	/*remove_call_out("xiulian_doing");
	remove_call_out("breaking_doing");*/
}

private void heart_beat()
{
	doing_flag++;

	if ( !(doing_flag%1) ) xiulian_doing();
	if ( !(doing_flag%3) ) breaking_doing();
}
