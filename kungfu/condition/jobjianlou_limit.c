#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
        object room;
        object obb;
        int step;
        
        if( duration < 1 ) return 0;  
        me->apply_condition("jobjianlou_limit", duration - 1);  
        room = environment(me);     

        if ( me->query_temp("guo_jianlou/where")) 
        if ( me->query_temp("guo_jianlou/where") != room->query("site")
             && !me->query_temp("guo_jianlou/job_over") ) 
        {
          message_vision(HIY"一个宋兵跑过来对$N说道：你居然临阵脱逃，"
                         +"我去报告郭大人！\n"NOR,me);

          me->set("guo_shoucheng/failed",1);
          me->apply_condition("jobjianlou_limit",0);  
        }

        if ( me->query_temp("guo_jianlou/start_job")
             && me->query_temp("guo_jianlou/where") == room->query("site"))
        {
           if( duration % 2 == 0 && duration > 30)     
           {
             step=random(9)+1;
             message_vision(HIY"忽然$N从箭垛口似乎看到城下"HIW+chinese_number(step) +HIY"箭外有一名"HIR"蒙古箭手"HIY"在探头探脑。\n"NOR,me);
             obb=new("/quest/guojob/job2/robber4");
             obb->move("/d/xiangyang/"+room->query("site")+step);
             obb->change_ob(me);
             obb->set("where",room->query("site"));
           } else
                if( duration % 10 == 0 )  
             message_vision(HIY"$N通过箭垛口警惕地巡视着城外的情况，"+ "可是好象没有发现任何敌情。\n"NOR,me);
        }

        if( me->is_ghost() && !me->query_temp("linji/youming") )
        {
         me->delete_temp("guo_jianlou");
         me->apply_condition("jobjianlou_limit",0);
         return 0;
        }

        if( duration == 2
            && me->query_temp("guo_jianlou/where") == room->query("site") )
        {
         message_vision(CYN"\n一个守城宋兵跑过来说道：蒙古靼子暂时被击退了，" +"$N可以回去复命了！\n"NOR,me);
         if (me->query_temp("guo_jianlou/start_job")) 
         me->set_temp("guo_jianlou/job_over",1);
         me->delete_temp("guo_jianlou/start_job");
         me->apply_condition("jobjianlou_limit",0);     
        }
       return CND_CONTINUE;      
}

