// halt.c by.suimeng

int main(object me, string arg)
{

        if (me->is_fighting()) {
                me->remove_all_enemy();
                message_vision("$N身行向后一跃，跳出战圈不打了。\n", me); 
        }
        else if (!me->is_busy()) 
                return notify_fail("你现在不忙。\n");
        else if ((int)me->query_temp("pending/exercise") != 0) {
                message_vision("$N把正在运行的真气强行压回丹田，站了起来。\n", me);
                me->interrupt_me();
        }
        else if ((int)me->query_temp("pending/respirate") != 0){
                message_vision("$N把正在灵台中运行的先天之气徐徐吐出，睁眼站了起来。\n", me);
                me->interrupt_me();
        }
        if (me->query("doing"))
        {
                write(BLINK HIR"你正在闭关,如果halt的话会减少你");
                write(BLINK HIR"一半的潜能,你确定要脱离闭关状态");
                write(BLINK HIR"吗?(y/n)\n");
                input_to("closed",me);
                return 1;
        }

        me->interrupt_me();


        return 1;
}

int closed(string str,object me)
{
        str=lower_case(str); //传回小写字样

        if(str=="y"||str=="yes")   {
        write(BLINK HIG"你放弃了一半的潜能脱离了闭关状态!\n"NOR); 
        me->interrupt_me();
        return 1;
        }
        
        write(BLINK HIB"如果要脱离闭关状态请按yes或者y!\n");
        return 1;
}

     

