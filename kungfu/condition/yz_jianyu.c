// jail.c

#include <ansi.h>
#include <login.h>

inherit F_DBASE;

int update_condition(object me, int duration)
{
	duration = duration - 1;

	if ( duration < 1 && sscanf(base_name(environment(me)), "/d/city/jianyu%*s") )
	{
		message_vision(HIY"哐当一声，一个狱卒打开牢门，一脚把$N踢了出去：想在这里白吃白喝？没门！\n"NOR, me);
		me->move("/d/city/wumiao");
		message("vision", HIY "只听乒地一声，你吓了一跳，定睛一看，原来是一个昏昏沉沉的家伙从衙门里被扔了出来！\n" NOR, environment(me), me);
		tell_object(me, HIY "只觉一阵腾云驾雾般，你昏昏沉沉地被扔出扬州监狱！\n" NOR);
		me->set("startroom", "/d/city/wumiao");
		me->unconcious();
	}

	me->apply_condition("yz_jianyu", duration);
	return 1;
}

