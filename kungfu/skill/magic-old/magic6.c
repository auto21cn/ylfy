// 闪电术

#include <ansi.h>

inherit F_SSERVER;

int thunderspell(object me, object obj)
{
	int	damage, spells;

        if ((int)me->query_skill("magic-old", 1) < 100)
                return notify_fail(WHT"你的古代魔法不够娴熟，还使不出「七键守护神」。\n"NOR);
	message_vision(HIR "\n一个巨大的毁灭冲击波向$N"HIR"的身上打来，\n" NOR, obj);
	obj->receive_damage("jing", 0, me);
	spells = me->query_skill("spells");
//me->start_busy(0);
	if(obj->is_ghost()==1) {
		message_vision(HIB "$N"HIB"惨叫了一声，化为了灰烬！\n" NOR, obj);
		obj->die();
		return 1;
	}
	if(obj->is_zombie()==1) {
		message_vision(HIB "$N"HIB"惨叫了一声，化为了一滩血水！\n" NOR, obj);
		obj->die();
		return 1;
	}
	if(obj->query("race")=="野兽") {
//		kar = obj->query("qi");
//		spi = obj->query("jing");
                damage = (int)me->query_skill("magic-old", 15);
                damage = damage + random(damage)+2000;
//		damage = (31 - spi)*(spells/4)*(random(31-kar)+1)+100;
		if(damage <= 20) damage = 0;
		if(damage > 3500) damage = 3500;
		if(damage != 0) {
			message_vision(HIB "$N"HIB"的全身都被毁灭之光笼罩了！\n" NOR, obj);
  		            obj->receive_damage("qi", obj->query("eff_qi")/4);
               		    obj->receive_damage("jing", obj->query("eff_jing")/4);
                            obj->receive_wound("qi", obj->query("eff_qi")/4);               		    
//                            obj->start_busy(2);
	 		COMBAT_D->report_status(obj);
			if( !obj->is_fighting(me) ) {
                		if( living(obj) ) {
                        		if( userp(obj) ) 
						obj->fight_ob(me);
					else
						obj->kill_ob(me);
                		}
                		me->kill_ob(obj);
        		}
		} else 
			message_vision(HIC "但被$N"HIC"躲过了！\n" NOR, obj);
		return 1;
	}
//	kar = obj->query("qi");
//	spi = obj->query("jing");
                damage = (int)me->query_skill("magic-old", 15);
                damage = damage + random(damage);
//	damage = (31 - spi)*(spells/10)*(random(30-kar)+1);
	if(damage < 0) damage = 10;
	if(random(2)==1) {
			message_vision(HIB "$N"HIR"的全身都被毁灭之光笼罩了！\n" NOR, obj);
  		            obj->receive_damage("qi", obj->query("eff_qi")/4);
               		    obj->receive_damage("jing", obj->query("eff_jing")/4);
                            obj->receive_wound("qi", obj->query("eff_qi")/4);               		    
//                            obj->start_busy(2);
 		COMBAT_D->report_status(obj);
		if( !obj->is_fighting(me) ) {
               		if( living(obj) ) {
                       		if( userp(obj) ) 
					obj->fight_ob(me);
				else
					obj->kill_ob(me);
               		}
               		me->kill_ob(obj);
       		}
	} else 
			message_vision(HIC "但被$N"HIC"躲过了！\n" NOR, obj);
	return 1;
	
}
int perform(object me)
{
	string 	msg;
	object	env;
	object	*inv;
	int	i, full, max_qi, max_jing, eff_qi, eff_jing;

	if((int)me->query_skill("spells") < 200 )
		return notify_fail("你的法术不够高！\n");

	if((int)me->query("neili") < 200 )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("qi") < 500 )
		return notify_fail("你的体力不够！\n");

	if((int)me->query("jing") < 100 )
		return notify_fail("你的精神没有办法有效集中！\n");

	me->add("neili", -1500);
	me->receive_damage("jing", 100);
	max_qi = me->query("max_qi");
	eff_qi = me->query("eff_qi");
	max_jing = me->query("max_jing");
	eff_jing = me->query("eff_jing");

	if ( eff_qi < max_qi || eff_jing < max_jing ) 
	{
		full = max_qi/3;
		me->receive_curing("qi", full);
		me->receive_heal("qi", full);
		full = max_jing/3;
		me->receive_curing("jing", full);
		me->receive_heal("jing", full);
		message_vision(HIW "\n巨大的咒语声过后,$N"HIW"全身笼罩着圣洁的光芒，全身的伤好像好多了！\n" NOR, me);
	}

	msg = YEL "$N"YEL"脚踩五芒星，双手握成伏魔印，口中喃喃地念著咒文，\n" NOR;
       msg += HIB"$N"HIM"念到 圣血的圣杯,不会会来的冤魂...\n"NOR;
       msg += HIB"$N"HIM"继续念到 召换风的五芒.召换火的五芒.召换水的五芒...\n"NOR;
       msg += HIC"$N"HIW"大叫一声  冥界的贤者啊!用七把钥匙打开地狱的大门吧！「七键守护神」！\n"NOR;
	message_vision(msg, me);
	env = environment(me);
	inv = all_inventory(env);
	for(i=0; i<sizeof(inv); i++) 
	{
		if( !playerp(me) && !playerp(inv[i]) && !inv[i]->fighting(me) ) continue;
		if( inv[i]==me ) continue;
		if( !inv[i]->is_character() || inv[i]->is_corpse() ) continue;
		thunderspell(me, inv[i]);
	}
	me->start_busy(1);
	return 1;
}


