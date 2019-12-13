// vote jail
// bbb 99.1.25

#include <vote.h> 
#include <ansi.h>
#define V_JAIL 9

inherit F_CONDITION;

int clear_vote(object me);

int vote(object me, object victim)
{
  int reason; // vote for what?
  int vv;	// valid voter numbers
  int vc; 	// vote count;
  int df;
  string *juror, my_id;

  if (me == victim)
  {
	if (random(2)) me->add("vote/abuse", 10);
  	return notify_fail("�㲻�ǿ���Ц�ɣ����ı��������Ȩ��\n");
  }

/*
  if ((reason = (int)victim->query("vote/reason"))>0 && (reason!=V_JAIL))
  {
  	return notify_fail("Ҫ�ѵ�ǰ�ı�������Ժ�ſ������µĶ��顣\n");
  }
*/

if( victim->query("block") ) 	
  {
  	return notify_fail(victim->name()+"�Ѿ����͵���������ȥ�ˡ�\n");
  }

  if (reason <= 0)
  {
  	victim->set("vote/reason", (int)V_JAIL); 
  }
  
  my_id = me->query("id");

  // dont allow me to vote twice for the same issue
  juror = victim->query("vote/juror");
  
  if( !pointerp(juror) )
  {
 	victim->set("vote/juror", ({ my_id }) );
  } else if( member_array(my_id, juror) == -1 ) 
  {
 	victim->set("vote/juror", juror+({ my_id }) );
  } else
  {
	me->add("vote/abuse", 10);
  	return notify_fail("һ��һƱ�����ñ���Ȩ��Ҫ�ܳͷ��ģ�\n");
  }

//  vv = (int) ("/cmds/std/vote")->valid_voters(me)/6;  	
vv = (int) ("/cmds/std/vote")->valid_voters(me);      	
  vc = victim->add("vote/count", 1);

  df = vv - vc;
  if (vv < 4) df = 4 - vc;

  if (df>0)
  { 
        shout( HIG "��������"+me->name(1)+"ͶƱ��"+victim->name(1)+"("+capitalize(victim->query("id"))+")"
			+"Ͷ�����������"+chinese_number(df)+"Ʊ��\n" NOR);
	write( HIG "��������"+me->name(1)+"ͶƱ��" +victim->name(1)
			+"Ͷ�����������"+chinese_number(df)+"Ʊ��\n" NOR);
	victim->apply_condition("vote_clear", 10);
  } else 
  {
        shout( HIG "��������"+me->name(1)+"ͶƱ��" +victim->name(1)+"("+capitalize(victim->query("id"))+")"
			+"Ͷ�������"+victim->name(1)+"���͵���������ȥ�ˣ�\n" NOR);
	write( HIG "��������"+me->name()+"ͶƱ��" +victim->name()
			+"Ͷ�������"+victim->name(1)+"���͵���������ȥ�ˣ�\n" NOR);
			
	victim->apply_condition("vote_clear", -10);
//     victim->set("jail_on", 1);	
victim->set("block", 1);	
victim->move("/clone/misc/block.c");	
  } 
  
  return 1;
}