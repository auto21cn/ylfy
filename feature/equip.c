// equip.c
// 修改支持动态 By Wenwu On 2006.7.17

#include <dbase.h>
#include <weapon.h>

inherit F_SAVE;

void suit_temp(object owner)
{
      mapping applied_prop=([]);
      mapping sum_eff=([]);  //套装效果
      mapping suit_eff=([]);
      string *apply;
   //套装属性附加实现-------------------------------------------------------------------------------
         //八大天赋
        if(mapp(suit_eff=owner->suit(owner,"suit_eff"))) 
           {
              applied_prop=([]);
              sum_eff=owner->sum_eff(owner,suit_eff);
              apply=keys(sum_eff);
              for(int i = 0; i<sizeof(apply); i++)
		if( undefinedp(applied_prop[apply[i]]) )  //如果applied_prop中无法找到apply[i]
			applied_prop[apply[i]] = sum_eff[apply[i]];   //则将防具效果添加进applied_prop中
		else
			applied_prop[apply[i]] += sum_eff[apply[i]];  //能找到，就合并数据
           }
           owner->set_temp("suit_eff",applied_prop);
           //附加技能
           if(mapp(suit_eff=owner->suit(owner,"suit_skill"))) 
           {
              applied_prop=([]);
              sum_eff=owner->sum_eff(owner,suit_eff);
              apply=keys(sum_eff);
              for(int i = 0; i<sizeof(apply); i++)
		if( undefinedp(applied_prop[apply[i]]) )  //如果applied_prop中无法找到apply[i]
			applied_prop[apply[i]] = sum_eff[apply[i]];   //则将防具效果添加进applied_prop中
		else
			applied_prop[apply[i]] += sum_eff[apply[i]];  //能找到，就合并数据
           }
           owner->set_temp("suit_skill",applied_prop);
}

int wear()
{
	mixed item_ob;
	object owner;
	mapping armor_prop, applied_prop, default_armor_prop, is_bind;
	string *apply, type;
	int sx_add;
	
	// Only character object can wear armors.
	if( !owner = environment())
		return 0;
	if( !owner->is_character() )
		return 0;
	// If already worn, just recognize it.
	if( query("equipped") )
		return 1;
	// Check if we have "armor_prop" defined.
	if( mapp(armor_prop = query("weapon_prop")) )
		return notify_fail(this_object()->name()+"是武器，不是护具，你只能穿戴可当作护具的东西。\n");
	if( !mapp(armor_prop = query("armor_prop")) )
		return notify_fail("你只能穿戴可当作护具的东西。\n");
	
	type = query("armor_type");
	
	if( owner->query_temp("armor/" + type) )
		return notify_fail("你已经穿戴了同类型的护具了。\n");
	// 必须空出一手才能装备盾牌
	if ( type == "shield" 
		&& owner->query_temp("secondary_weapon") )
		return notify_fail("你必须空出一只手来装备盾牌。\n");
	// 绑定的装备别人无法装备上
	if ( mapp(is_bind=query("bind_master_level")) 
		&& !is_bind[owner->query("id")] )
		return notify_fail("这是别人的私有防具你无法装备上。\n");
	
	owner->set_temp("armor/" + type, this_object());

	// 动态支持相关设置
	//-------------------------------------------------------------------
	if ( item_ob = this_object()->query_default_object() )
	{
		default_armor_prop = item_ob->query("armor_prop");
		armor_prop = maps_compose(armor_prop, default_armor_prop);
	}
	//-------------------------------------------------------------------

	apply = keys(armor_prop);
	applied_prop = owner->query_temp("apply");
	
	if( !mapp(applied_prop) )
		applied_prop = ([]);
	
	for(int i = 0; i<sizeof(apply); i++)
	{

	   switch (query("xyzx_item/pinji"))  // 装备品级
	   {
		case 5:sx_add = armor_prop[apply[i]]*70/100; break;
		case 4:sx_add = armor_prop[apply[i]]*50/100; break;
		case 3:sx_add = armor_prop[apply[i]]*30/100; break;
		case 2:sx_add = armor_prop[apply[i]]*20/100; break;
		case 1:sx_add = armor_prop[apply[i]]*10/100; break;
		default:sx_add = 0;
	   }

        //write(HIY"增加数值是"+sx_add+" 来源于"+armor_prop[apply[i]]+"。\n"NOR);

		if( undefinedp(applied_prop[apply[i]]) )
			applied_prop[apply[i]] = armor_prop[apply[i]] + sx_add;
		else
			applied_prop[apply[i]] += (armor_prop[apply[i]] + sx_add);
	}
	
	owner->set_temp("apply", applied_prop);
        //套装属性附加调用
        //---------------------------------
           suit_temp(owner);
        //---------------------------------
	set("equipped", "worn");
	// 装备绑定
	if ( query("xyzx_sys/bind_type") && playerp(owner) )
	{
		set("bind_master_level/"+owner->query("id"), 2);
		set("owner_id", 1);
		set("xyzx_save_item", 1);
	}
	
	return 1;
}

int wield()
{
	mixed item_ob;
	object owner, old_weapon;
	mapping weapon_prop, default_weapon_prop, is_bind;
	string *apply;
	int flag, sx_add;
	
	// Only character object can wear armors.
	if( !owner = environment())
		return 0;
	if( !owner->is_character() )
		return 0;
	// If already wielded, just recognize it.
	if( query("equipped") )
		return 1;
	// Check if we have "weapon_prop" defined.
	if( !mapp(weapon_prop = query("weapon_prop")) )
		return notify_fail("你只能装备可当作武器的东西。\n");
	// 绑定的装备别人无法装备上
	if ( mapp(is_bind=query("bind_master_level")) 
		&& !is_bind[owner->query("id")] )
		return notify_fail("这是别人的私有武器你无法装备上。\n");
	
	flag = query("flag");
	
	// 双手武器标志 1:必须双手才能装备,2:可以不同手装备
    if( flag & TWO_HANDED )
	{
		if( owner->query_temp("weapon")
			||  owner->query_temp("secondary_weapon")
			||  owner->query_temp("armor/shield") )
			return notify_fail("你必须空出双手才能装备双手武器。\n");
		
		owner->set_temp("weapon", this_object());
		owner->set_temp("secondary_weapon",this_object());
	}
	else
	{
		// If we are are using any weapon?
		if( !(old_weapon = owner->query_temp("weapon")) )
			owner->set_temp("weapon", this_object());
		// If we still have a free hand? 
		else if( !owner->query_temp("secondary_weapon") 
			&& !owner->query_temp("armor/shield") )
		{
			// If we can wield this as secondary weapon?
            if(flag & SECONDARY)
			{
				owner->set_temp("secondary_weapon", this_object());
			}
			// If we can switch our old weapon to secondary weapon ?
			else if( (int)old_weapon->query("flag") & SECONDARY )
			{
				old_weapon->unequip();
				owner->set_temp("weapon", this_object());
				old_weapon->wield();
			}
			// We need unwield our old weapon before we can use this one.
			else
				return notify_fail("你必须先放下你目前装备的武器。\n");
		}
		// We have both hands wearing something.
		else
			return notify_fail("你必须空出一只手来使用武器。\n");
	}

	// 动态支持相关设置
	//------------------------------------------------------------------
	if ( item_ob = this_object()->query_default_object() )
	{
		default_weapon_prop = item_ob->query("weapon_prop");
		weapon_prop = maps_compose(weapon_prop, default_weapon_prop);
	}
	//------------------------------------------------------------------
	
	apply = keys(weapon_prop);
	for(int i = 0; i<sizeof(apply); i++)
	{
		switch (query("xyzx_item/pinji")) // 装备品级
	   {
		case 5:sx_add = weapon_prop[apply[i]]*70/100; break;
		case 4:sx_add = weapon_prop[apply[i]]*50/100; break;
		case 3:sx_add = weapon_prop[apply[i]]*30/100; break;
		case 2:sx_add = weapon_prop[apply[i]]*20/100; break;
		case 1:sx_add = weapon_prop[apply[i]]*10/100; break;
		default:sx_add = 0;
	   }
		owner->add_temp("apply/" + apply[i], weapon_prop[apply[i]] + sx_add);
	}
	
	owner->reset_action();
        //套装属性附加调用
        //---------------------------------
           suit_temp(owner);
        //---------------------------------
	set("equipped", "wielded");
	// 装备绑定
	if ( query("xyzx_sys/bind_type") && playerp(owner) )
	{
		set("bind_master_level/"+owner->query("id"), 2);
		set("owner_id", 1);
		set("xyzx_save_item", 1);
	}
    
	return 1;
}

int unequip()
{
	mixed item_ob;
	object owner,s_weapon;
	mapping prop, applied_prop, default_weapon_prop, default_armor_prop;
	string *apply, equipped;
	int sx_add;
	
	if( !(owner = environment())->is_character() )
		return 0;
	if( !stringp(equipped = query("equipped")) )
		return notify_fail("你目前并没有装备这样东西。\n");
	
	if( equipped=="wielded" )
	{
		if( (object)owner->query_temp("weapon") == this_object() )
		{
			owner->delete_temp("weapon");
			if( (object)owner->query_temp("secondary_weapon") == this_object() )
				owner->delete_temp("secondary_weapon");
			if (objectp(s_weapon=owner->query_temp("secondary_weapon")))
			{
				s_weapon->unequip();
				s_weapon->wield();
			}
		}
		else if( (object)owner->query_temp("secondary_weapon") == this_object() )
			owner->delete_temp("secondary_weapon");
		
		prop = query("weapon_prop");

		// 动态支持相关设置
		//---------------------------------------------------------------------
		if (item_ob = this_object()->query_default_object() )
		{
			default_weapon_prop = item_ob->query("weapon_prop");
			prop = maps_compose(prop, default_weapon_prop);
		}
		//---------------------------------------------------------------------

		owner->reset_action();
	}
	else if( equipped=="worn" )
	{
		owner->delete_temp("armor/" + query("armor_type") );
		prop = query("armor_prop");

		// 动态支持相关设置
		//-------------------------------------------------------------------
		if ( item_ob = this_object()->query_default_object() )
		{
			default_armor_prop = item_ob->query("armor_prop");
			prop = maps_compose(prop, default_armor_prop);
		}
		//-------------------------------------------------------------------
	}
	
	apply = keys(prop);
	applied_prop = owner->query_temp("apply");
	
	for(int i = 0; i<sizeof(apply); i++)
	{	
	switch (query("xyzx_item/pinji"))  // 装备品级
	   {
		case 5:sx_add = prop[apply[i]]*70/100; break;
		case 4:sx_add = prop[apply[i]]*50/100; break;
		case 3:sx_add = prop[apply[i]]*30/100; break;
		case 2:sx_add = prop[apply[i]]*20/100; break;
		case 1:sx_add = prop[apply[i]]*10/100; break;
		default:sx_add = 0;
	   }
		// To support array apply, we cannot add_temp() here.
		applied_prop[apply[i]] -= (prop[apply[i]] + sx_add);
	}
	 //套装属性附加调用
        //---------------------------------
           suit_temp(owner);
        //---------------------------------

	delete("equipped");
    
    return 1;
}