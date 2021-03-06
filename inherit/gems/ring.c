
#include <ansi.h>
#include <armor.h>

inherit FINGER;
inherit F_GEMS;

void init_sockets(object me)
{
	//设置可开光的接口上限
	set("max_sockets", 1);
	
	if ( me->query("combat_exp") > 10000000 )
		add("max_sockets", 1);
	
	if ( (int)query("sockets/max")>3 )
		set("sockets/max",3);
	
	if ( me->query("combat_exp") > 100000000 )
		add("max_sockets", 1);
	
	//检查开光时玩家增加的相关参数
	if ( me->query("diablo/" + TYPE_FINGER + "/id") != query("id") 
		|| me->query("diablo/" + TYPE_FINGER + "/file_name") != base_name(this_object()) )
		return;
	
	//将玩家开光次数标志赋数给戒指的接口值
	set("sockets", me->query("diablo/" + TYPE_FINGER + "/sockets"));
	//增加个人拥有识别参数
	set("diablo/only_me",me->query("id"));
	//更新戒指的长描述
	set_ring_desc();
}

void setup()
{
	if ( objectp(this_player()) ) init_sockets(this_player());
	::setup();
}

void spec_prop(object me, string socket, int socket_level, int mode)
{
	//检查所嵌宝石的类型和等级是否正确
	if (!valid_gem(socket, socket_level))
		return;
	
	//再次检查开光时玩家增加的相关参数
	if ( me->query("diablo/" + TYPE_FINGER + "/id") != query("id") || 
		me->query("diablo/" + TYPE_FINGER + "/file_name") != base_name(this_object()) )
		return;

	if ( query("diablo/only_me") != me->query("id") )
		return;
	
	//根绝所嵌宝石的种类获得不同的效果
	switch (socket)
	{
		case "ruby":	
		if ( mode == 1 )
			message_vision(HIR + query("name") + HIR"射出一道耀眼的红光，$N在神光的沐浴下感到体力异常的充沛！\n"NOR, me);
		else
			message_vision(HIR"随着神光渐渐的隐去，$N的体力又恢复正常了。\n"NOR, me);
		me->add("max_qi", me->query("max_neili") * socket_level * mode / 30);
		me->add("eff_qi", me->query("max_neili") * socket_level * mode / 30);
		me->add("qi", me->query("max_neili") * socket_level * mode / 30);
		break;
		
		case "topaz":
		if (mode == 1)
			message_vision(HIY + query("name") + HIY"射出一道夺目的黄光，$N在神光的沐浴下感到精力异常的充沛！\n"NOR, me);
		else
			message_vision(HIY"随着神光渐渐的隐去，$N的精力又恢复正常了。\n"NOR, me);
		me->add("max_jing", me->query("max_neili") * socket_level * mode / 30);
		me->add("eff_jing", me->query("max_neili") * socket_level * mode / 30);
		me->add("jing", me->query("max_neili") * socket_level * mode / 30);
		break;
		
		case "sapphire":
		if (mode == 1)
			message_vision(HIB + query("name") + HIB"射出一道柔和的蓝光，$N在神光的沐浴下感到内力异常的充沛！\n"NOR, me);
		else
			message_vision(HIB"随着神光渐渐的隐去，$N的内力又恢复正常了。\n"NOR, me);
		me->add("neili", me->query("max_neili") * socket_level * mode / 10);
		break;
		
		case "emerald":
		if (mode == 1)
			message_vision(HIG"忽然从" + query("name") + HIG"里幻化出一个身披绿纱的幸运女神围绕着$N的身边！\n"NOR, me);
		else
			message_vision(HIG"绿光一闪，$N的幸运女神就不见了。\n"NOR, me);
		me->add_temp("apply/karma", 10 * socket_level * mode);
		break;
		
		case "amethyst":
		if (mode == 1)
			message_vision(MAG"一片紫色云雾迅速从" + query("name") + MAG"中涌出，转眼间就已经把$N托了起来！\n"NOR, me);
		else
			message_vision(MAG"紫色云雾被风吹散了，$N的身形又显现了出来。\n"NOR, me);
		me->add_temp("apply/dexerity", 10 * socket_level * mode);
		break;
		
		case "diamond":
		if (mode == 1)
			message_vision(HIW"「哗」，" + query("name") + HIW"划出一道闪电直冲天际，$N刹时感到体内充满了力量！\n"NOR, me);
		else
			message_vision(HIW"渐渐的$N的神色又恢复了正常。\n"NOR, me);
		me->add_temp("apply/strength", 10 * socket_level * mode);
		break;
		
		case "skull":
		if (mode == 1)
			message_vision(WHT"$N忽然感到一股奇异的力量围绕着$P，隐隐之间只觉得充斥着莫明的魔力！\n"NOR, me);
		else
			message_vision(WHT"$N" + query("name") + WHT"中的咒语渐渐失去了效用！\n"NOR, me);
		me->add_temp("apply/magic", 10 * socket_level * mode);
		break;
	}
	return;
}

//装备戒指时的参数变化构成特殊效果
int wear()
{
	int i, sockets, ret;
	object me = environment();
	
	if (!(ret = ::wear()))
		return 0;
	
	sockets = query("sockets/max");
	for (i = 1; i <= sockets; i++)
		spec_prop(me, query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)), 1);
	return ret;
}

//解除装备时清除其特殊效果
int unequip()
{
	int i, sockets, ret;
	object me = environment();

	if (!(ret = ::unequip())) return 0;

	sockets = query("sockets/max");
	for (i = 1; i <= sockets; i++)
		spec_prop(me, query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)), -1);
	return ret;
}
