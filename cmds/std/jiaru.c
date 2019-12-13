// team.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	if(!arg || !objectp(obj = present(arg, environment(me))))
	{
return notify_fail("你要加谁入你的帮派？\n");	
	}
	if (obj->query("party/id"))
	{
		return notify_fail("他已经入了一个帮派了，如果想换帮，请先退出原帮派!\n");
	}
if (!me->query("party/zhu") && !me->query("party/zhanglao"))    	
	{
return notify_fail("你并非一帮之主,也不是帮内长老。\n");	
	}
	if (me->query_temp("askfor_join")==obj->query("id"))
	{
		return notify_fail("你正等着"+obj->query("name")+"的回答！\n");
	}
	if (obj->query_temp("askfor_join")==me->query("id"))
	{
		obj->set("party/id",me->query("party/id"));
		obj->set("party/name",me->query("party/name"));
		obj->delete_temp("askfor_join");
		tell_room(environment(me),"恭喜"+obj->query("name")+"成功加入"+me->query("name")+"的"+me->query("party/name")+"帮！\n");
//   CHANNEL_D->do_channel(me, "chat","恭喜"+obj->query("name")+"成功加入"+me->query("name")+"的"+me->query("partyname")+"帮!\n");       
message("channel:chat", HIY"【帮派精灵】"+HIM"："+obj->query("name")+"加入"+me->query("name")+"摩下，效忠于"+me->query("party/name")+"帮。\n"NOR,users());              	

	}
	else 
	{
		if (me->query_temp("askfor_join") && me->query_temp("askfor_join")!=obj->query("id"))
		{
			tell_object(me,"你放弃了加入的打算!\n");
		}
		me->set_temp("askfor_join",obj->query("id"));
		tell_room(environment(me),me->query("name")+"邀请"+obj->query("name")+"加入自己的"+me->query("party/name")+"帮！\n");
	}
	return 1;
}

int help(object me)
{
	write( @HELP
jiaru id

这个命令可以让你加和你在同一个房间的玩家入你的帮派。	
注：你必须为该帮派的帮主。
HELP
   );
   return 1;
}
