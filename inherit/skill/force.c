// force.c

inherit SKILL;
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
    int damage;
    me->add("neili", - factor );
    damage = (int)me->query("neili")/100 + factor - (int)victim->query("neili")/100;
    if( damage < 0 )
	{  //降低空手被反震的概率，降低到个合理的地步
		if ( !me->query_temp("weapon") && me->query_skill("force") + random(me->query_skill("force")*2) < victim->query_skill("force") ) 
		{
			damage = - damage;
			me->receive_damage( "qi", damage * 2,victim );
			me->receive_wound( "qi", damage ,victim);
			if( damage < 20 ) return "$N受到$p的内力反震，闷哼一声。\n";
			else if( damage < 80 ) return "$N被$p以内力反震，「嘿」地一声退了两步。\n";
			else if( damage < 200 ) return "$N被$p以内力一震，胸口有如受到一记重锤，连退了五六步！\n";
			else return "$N被$p的内力一震，眼前一黑，身子向后飞出丈许！！\n";
		}
		else
			return damage_bonus + factor;
	}
	else
		return damage;
}

int valid_learn_ob(object ob) {return 1;} //返回1,内功不能和玩家学

varargs mixed armor_ob(object me, object victim, int damage_bonus,int force_armor, int combat_msg)
{
    if ( !living(victim) || damage_bonus < 1 ) 
		return damage_bonus;
	if ( force_armor < 0 ) force_armor = 0;
    if ( victim->query("neili") >= force_armor+damage_bonus )
	{
        if ( force_armor > damage_bonus)
		{
            victim->add("neili",-damage_bonus*2);
            return BOLD "$p用"+to_chinese(victim->query_skill_mapped("force"))+"的护体真气化解了$N的伤害！\n" NOR;
        }
		else
		{
			if ( combat_msg < 4 )
				message_vision( BOLD "$p催动"+to_chinese(victim->query_skill_mapped("force"))+"的护体真气试图削弱$N的伤害！\n" NOR,me,victim);
            victim->add("neili",-(force_armor/3)*2);
            return damage_bonus-force_armor;
        }
	}
	return damage_bonus;
}
