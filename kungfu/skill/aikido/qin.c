
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;
string* buwei = (
{
	"右手肘部",
	"手腕",
	"左手关节",
	"颈部",
	"肩部关节",
	"背心要穴",
	"膝关节",
	"命门"
});
int perform(object me, object target)
{
	string msg;
	int extra;
	string bw;


	bw = buwei[random(sizeof(buwei))];
	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("合气道.擒只能对战斗中的对手使用。\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("合气道.擒必须空手。\n");
	if( (int)me->query("max_neili") < 200 )
		return notify_fail("你的内力不够！\n");
	if ((int)me->query_skill("shayi-xinfa", 1) < 30)
		return notify_fail("你的杀意心法火候不够。\n");

	extra = me->query_skill("aikido",1);
	if(extra <= 3 ) return notify_fail("你的［合气道］不够熟练！\n");
	if( target->is_busy() )
		return notify_fail(target->name() + "目前已经手忙脚乱了，放胆攻击吧ⅵ\n");

	if( (int)me->query("neili") < 200  )
		return notify_fail("你的内力不够。\n");

	msg = HIG "$N双眉一扬，一错身用合气道擒拿法斗然间抓住了$n的"+bw+"!\n";

	if( random(me->query("xyzx_sys/level")) > target->query("xyzx_sys/level")/3 || random(me->query("unarmed")) > target->query("dodge")/3 )
	{
		msg += HIW " 结果$p被$P抓住顿时不能动弹！\n" NOR;
		target->start_busy( (int)me->query_skill("aikido",1) / 50 + 2 );
	}
	else
	{
		msg += HIC"可是$p看破了$P的企图，没有给抓住。\n"NOR NOR;
		me->start_busy(2);
	}
	message_vision(msg, me, target);
	me->add("neili", - 60);
	if(!target->is_fighting(me)) target->fight_ob(me);

	return 1;
}

