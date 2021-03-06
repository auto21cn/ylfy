// no_enforce.c 不能加力加劲 受阻
// make by cigarman 2012

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

string query_msg_color()   { return YEL;         } 

string query_is_id  ()     { return "no_enforce";}   
                      
string query_msg_my()     { return "你双手双脚酸麻要命，一点力量都使用不出！";         }  
string query_msg_round()  { return "看上去虚弱无比，身体摇晃不已！";         }  
                                                                                                  
int update_condition(object me, int duration)
{
     
        tell_object(me, query_msg_color()+query_msg_my()+"\n"NOR);
        tell_room(environment(me), query_msg_color()+me->name()+query_msg_color()+query_msg_round()+"\n" NOR,({ me }));

	me->add_busy(3);
        if( duration < 1 ) {
                me->clear_condition(query_is_id());
                return 0;
        }
        else {
                me->apply_condition(query_is_id(), duration - 1);
                return CND_CONTINUE; 
        }
        
}

string query_type(object me) { return "busy"; }