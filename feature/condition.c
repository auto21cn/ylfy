
#include <condition.h>

mapping conditions;

mapping query_conditions()
{
	return conditions;
}

//随心跳逐渐清除中毒状态，
nomask int update_condition()
{
	mixed *cnd, err;
	int i, flag, update_flag;
	object cnd_d;
	
	if( !mapp(conditions) || !(i=sizeof(conditions)) )
		return 0;
	
	cnd = keys(conditions);
	update_flag = 0;
	cnd -= ({ "0" }); //消除 cnd = 0 的bug.
	while(i--)
	{
		//以下一句防止condition = 0 的bug. 
        if( !cnd[i] ) continue;
		cnd_d = find_object(CONDITION_D(cnd[i]));
		
		if( !cnd_d )
		{
			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
			cnd_d = find_object(CONDITION_D(cnd[i]));
			
			if( err || !cnd_d )
			{
				log_file("condition.err",sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n",CONDITION_D(cnd[i]), this_object(), err));
				map_delete(conditions, cnd[i]);
				continue;
			}
		}
		
		flag = call_other(cnd_d, "update_condition", this_object(), conditions[cnd[i]]);
		
		if( conditions[cnd[i]] < 1 )
			map_delete(conditions, cnd[i]);
		
		update_flag |= flag;
	}
	
	if( !sizeof(conditions) )
		conditions = 0;
	
	return update_flag;
}

//形成中毒状态
nomask void apply_condition(string cnd, mixed info)
{
	object env;
	string env_name;

	if ( file_size(CONDITION_D(cnd)+".c")<1 
		&& file_size("/binaries"+CONDITION_D(cnd)+".b")<1 )
	{
		if ( objectp(env=environment()) ) env_name=base_name(env);
		else env_name="无环境";
		log_file("condition.err", "错误: "+this_object()->query("id")+" 在 "+env_name+" 中毒 "+cnd+"\n");
		return;
	}

	if( !mapp(conditions) )
		conditions = ([ cnd : info ]);
	else
		conditions[cnd] = info;
}

//中毒状况
nomask mixed query_condition(string cnd)
{
	if( !mapp(conditions) || undefinedp(conditions[cnd]) )
		return 0;
	
	return conditions[cnd];
}
 
//死亡清除的中毒状态
nomask void clear_condition(int flag)
{
	int i, over;
	string *cnd;
	
	if ( !mapp(conditions) || !(i=sizeof(conditions)) )
		return;
	
	cnd = keys(conditions);
	while (i--)
	{
		//投票限制不被清除
		if ( cnd[i]=="vote_clear" || cnd[i]=="vote_suspension" )
			continue;
		//非死亡不能清除的部分中毒，死亡时“flag = 1”
		if ( !flag )
		{
			if (cnd[i]=="killer" 
				|| cnd[i]=="bonze_drug" 
				|| cnd[i]=="bonze_jail")
				continue;
		}
		// 每死亡一次只减去杀人一次的记录
		if ( cnd[i] == "killer" )
		{
			over = conditions["killer"]-500;
			if ( over > 0 ) conditions["killer"] = over;
			else map_delete(conditions, cnd[i]);
			continue;
		}
		
		map_delete(conditions, cnd[i]);
	}
}

