#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() )
		return notify_fail(HIY"��ҪΪ˭ʹ���¹�����\n"NOR);

     //  if( !me->query("zhuanbest",1))
      //  return notify_fail("��û���ʸ�ʹ������ܣ�\n");

	if((int)me->query("neili")< 600)
	     return notify_fail("��ķ���̫���ˣ�\n");

    if ( me->is_busy() )
        return notify_fail("��������æ���޷�ʹ���¹���");
	
	if((int)me->query("neili")< 1000)
	return notify_fail("��ķ���̫���ˣ�\n");
	if((int)me->query_skill("magic-light",1)< 250)
	return notify_fail("��Ĺ���ħ��̫���ˣ�\n");

	if((int)target->query("qi") > (int)target->query("max_qi")-(int)target->query("max_qi")/3)
	return notify_fail("Ŀ�����ڲ���Ҫʹ���¹�����\n");

	msg = HIY "$N����� �Ȱ����ܵ������������е������������������ɣ�����\n";
	msg += HIY "$N����� ����� �Ź����ߣ�������!!����\n";
	msg += HIW "$n�����ϣ�������ʥ֮�¹⣬���ϵ������˲���!��\n";
	me->add("neili",-500);
	me->start_busy(2);

	if((int)target->query("qi") < (int)target->query("max_qi")+(int)target->query("max_qi")/3)
        {
        target->add("qi",target->query("eff_qi")/3);
        target->add("eff_qi",target->query("eff_qi")/3);
if (target->query("qi") > target->query("max_qi")+1000)
target->set("qi",target->query("max_qi")+1000);
if (target->query("eff_qi") > target->query("max_qi"))
target->set("eff_qi",target->query("max_qi"));
        }
	if((int)target->query("jing") < (int)target->query("max_jing")+(int)target->query("max_jing")/3)
        {
        target->add("jing",target->query("eff_jing")/3);
        target->add("eff_jing",target->query("eff_jing")/3);
if (target->query("jing") > target->query("max_jing")+1000)
target->set("jing",target->query("max_jing")+1000);
if (target->query("eff_jing") > target->query("max_jing"))
target->set("eff_jing",target->query("max_jing"));

         }
		message_vision(msg, me, target);
	return 1;
}