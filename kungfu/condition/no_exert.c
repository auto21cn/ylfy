// no_exert.c 不能运功yun  内息受制
// make by cigarman 2012
                                                   
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

string query_msg_color()   { return YEL;         } 

string query_is_id  ()     { return "no_exert";}      
                      
string query_msg_my()     { return "你丹田内的真气一阵乱翻，顿时手脚酸软无法运功！";         }  
string query_msg_round()  { return "突然全身好像泄了气一样，不停的喘着粗气！";         }  
                                                                                                  
int update_condition(object me, int duration)
{

        tell_object(me, query_msg_color()+query_msg_my()+"\n"NOR);
        tell_room(environment(me), query_msg_color()+me->name()+query_msg_color()+query_msg_round()+"\n" NOR,({ me }));

	me->add_busy(3);

        if( duration < 2 ) {
                me->clear_condition(query_is_id());
                return 0;
        }
        else {
                me->apply_condition(query_is_id(), duration - 1);
                return CND_CONTINUE; 
        }
        
}

string query_type(object me) { return "busy"; }

