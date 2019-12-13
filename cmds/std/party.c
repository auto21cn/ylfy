// bh.c

#include <ansi.h>;
inherit F_CLEAN_UP;

int main(object me, string arg)
{
object *ob;
if (!me->query("party/id"))	
return notify_fail(YEL"你还没有加入任何帮派！\n"NOR);
if(!arg) arg = ". . .";
ob=filter_array( users() , "party_listener", this_object(), (me->query("party/id") || wizardp(me)) );           	
message("party", HIW"【"+me->query("party/name")+"】"+me->query("name")+"("+me->query("id")+")"+HIW"："+ arg + "\n"NOR,ob);         	
return 1;
}
int party_listener(object ppl, string str)
{
if( !environment(ppl)) return 0;
if(wizardp(ppl) || ppl->query("party/id")==str ) return 1;	
else return 0;
}
int help(object me)
{
write(@HELP
指令格式 : party <讯息>	
这个指令让你将 <讯息> 传送出去, 所有正在帮派中的人都
会听见你的话.
see also : tune
HELP
);
return 1;
}
