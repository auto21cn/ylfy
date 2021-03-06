// sos.c
 
#include <ansi.h>
#include <command.h>
 
inherit F_CLEAN_UP;

#define BOARD get_object("/clone/board/bugs_b")
#define LOOK_CMD "/cmds/std/look"
 
int help(object me);

int main(object me, string arg)
{
        string arg2;
        
        if (! arg)
        {
                return help(me);
        }
        
        if (arg == "list")
        {
                LOOK_CMD->look_item(me, BOARD);
                return 1;
        } 
        
        if (sscanf(arg, "%s %s", arg, arg2) == 2) 
        {
                switch (arg) {
                case "post":
                        BOARD->do_post(arg2);
                        break;
                case "read":
                        BOARD->do_read(arg2);
                        break;
                case "re"  :
                        BOARD->do_re(arg2);
                        break;  
                case "search":
                        BOARD->do_search(arg2);
                        break; 
                default:
                        help(me);
                        break;
                        
                }
                return 1;
        } 

		return help(me);
}

int help(object me)
{
        write(@HELP
指令格式 :   
           sos post <标题>  留言        
           sos list         查看
           sos read next|new|<贴子编号>
           sos search title|author|document
           sos re <贴子编号>.<回复标题>
这个指令可以在系统出现臭虫时来向巫师求助。
玩家在这里应该将出现的情况和系统的提示尽量
详细地进行说明，以便巫师修改该臭虫。
HELP
        );

        return 1;
}

