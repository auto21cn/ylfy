// killer通缉 by Wenwu

inherit F_DBASE;

nosave mapping killer_ips = ([]);
nosave string killer_list = "";

int clean_up()
{
	return 1;
}
 
void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "PK统计精灵");
	CHANNEL_D->do_channel( this_object(), "sys", "PK统计系统已经启动。\n");
	set_heart_beat(300);
}

private void heart_beat()
{
	object *user, *killer_obs;
	string ip, *killer_ip, name;
	int i, n, m, max;

	if ( !mapp(killer_ips) ) killer_ips = ([]);
	killer_ip = keys(killer_ips);
	if ( !arrayp(killer_ip) ) killer_ip = ({});
	
	user = children(USER_OB);
	max = sizeof(user);
	for ( i=0; i<max; i++ )
	{
		if ( !objectp(user[i]) ) continue;
		if ( !clonep(user[i]) ) continue;
		if ( !environment(user[i]) ) continue;
		
		ip = query_ip_number(user[i]);
		if ( !ip ) ip = user[i]->query_temp("last_ip_number");

		if ( user[i]->query_condition("killer") )
		{
			if ( ip ) 
			{
				if ( !arrayp(killer_ips[ip]) ) killer_ips[ip]=({ user[i] });
				if ( member_array(ip, killer_ip) == -1 ) killer_ip += ({ ip });
			}
			CHANNEL_D->do_channel(this_object(),"rumor","据可靠消息，杀人犯"+user[i]->query("name")+"["+user[i]->query("id")+"]在"+environment(user[i])->query("short")+"一带流窜。\n");
		}

		if ( ip && member_array(ip, killer_ip) != -1 )
		{
			if ( !arrayp(killer_obs=killer_ips[ip]) ) killer_obs=({});
			if ( !wizardp(user[i]) && member_array(user[i], killer_obs) == -1 ) killer_obs += ({ user[i] });
			killer_obs -= ({ 0 });
			killer_ips[ip] = killer_obs;
		}
	}

	//双倍经验时间段时向玩家发送通告
	if ( atoi(CHINESE_D->chinese_time(9,ctime(time()))) > 19 )
		message("channel:chat", HIG"【镜花水月】"+HIM"现在的时间为 "HIG+CHINESE_D->chinese_time(9,ctime(time())) + "点 "HIM"系统正开放双倍经验的奖励。\n"NOR,users() );

	//______________________________通报杀人犯全部ID______________________________
	killer_list = "";
	for ( n=0; n<sizeof(killer_ip); n++ )
	{
		if ( !arrayp(killer_obs=killer_ips[killer_ip[n]]) )
		{
			map_delete(killer_ips, killer_ip[n]);
			continue;
		}
		killer_obs -= ({ 0 });
		if ( !sizeof(killer_obs) )
		{
			map_delete(killer_ips, killer_ip[n]);
			continue;
		}
		name = "";
		for ( m=0; m<sizeof(killer_obs); m++ )
		{
			if ( !objectp(killer_obs[m]) ) continue;
			if ( wizardp(killer_obs[m]) ) continue;
			name += HIY+killer_obs[m]->query("name")+"("HIR+killer_obs[m]->query("id")+HIY")";
			if ( m < sizeof(killer_obs)-1 ) name += "、";
		}
		killer_list += HIW"杀人通缉犯IP("HIR+killer_ip[n]+HIW")线上人物有："+name+HIW".\n"NOR;
	}
	//__________________________________End_______________________________________
	set_heart_beat(300+random(600)); // 重置心跳
}

// 增加新的杀人犯 IP 检索
void add_killer(object ob)
{
	string ip, *killer_ip;

	if ( !objectp(ob) || !playerp(ob) || wizardp(ob) ) return;
	
	ip = query_ip_number(ob);
	
	if ( !ip ) ip = ob->query_temp("last_ip_number");
	if ( !ip ) return;

	if ( !mapp(killer_ips) ) killer_ips = ([]);
	
	killer_ip = keys(killer_ips);
	
	if ( !arrayp(killer_ip) ) killer_ip = ({});
	if ( member_array(ip, killer_ip) != -1 ) return;

	killer_ips[ip] = ({ ob });
}

// 检查杀人犯与被杀者 IP 是否相同
int check_killer_ip(object killer, object ob)
{
	if ( query_ip_number(ob) == query_ip_number(killer) ) return 1;

	return 0;
}

// 返回killer统计
string get_killer_list()
{
	return killer_list;
}