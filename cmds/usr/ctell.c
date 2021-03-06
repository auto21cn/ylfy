//write 

#include <ansi.h>
#include <net/dns.h>
#include <liebiao.h>
inherit F_CLEAN_UP;
#define DEBUG "suimeng"
#ifdef DEBUG

void debug(string x)
{
    object monitor;
    if (!stringp(x) || !stringp(DEBUG))
		return;

    monitor=find_player(DEBUG);

    if(monitor && monitor->query("env/debug"))
		tell_object(monitor,x+"\n");
}

#else
#define debug(x)
#endif

object find_player(string target)
{
    int i;
    object *str;
    str=users();
    for (i=0;i<sizeof(str);i++)
		if (str[i]->query("id")==target)
		{
		if (!environment(str[i]))
			return 0;
		else
			return str[i];
		}
    return 0;
}

int help(object me);
    void create()
	{
		seteuid(getuid());
	}

int main(object me, string arg)
{
    string target, msg, mud;
    object obj,*wiz;

    if( !arg || sscanf(arg, "%s %s", target, msg)!=2 )
		return help(me);

    if(me->query("xieyi/zmud"))
	    {
	    write(HIY"你的客户端不支持Tomud协议，发送失败。\n"NOR);
	    return 1;
	    }

    if( userp(me) && !wizardp(me))
		{
		if (me->query("chblk_tell")+300>time())
			{
			write(ALERT("你现在喉咙嘶哑,半句话也说不出了。\n"));
			return  1;
			}
			me->add_temp("tell_msg_cnt", 1);

			if(time()-me->query_temp("tell_time") > 2)
            me->set_temp("tell_time",time());

			if(me->query_temp("tell_msg_cnt")>5 && time()-me->query_temp("tell_time")<2)
				me->set("chblk_tell",time());
			else
				me->delete_temp("tell_msg_cnt");
		}

   if( sscanf(target, "%s@%s", target, mud)==2 )
	    {
	   GTELL->send_gtell(mud, target, me, msg);
	   write(ALERT("网路讯息已送出，可能要稍候才能得到回应。\n"));
	   return 1;
	    }
	   
	   obj = find_player(target);
	   
   if (obj && !userp(me))
	    {
	    tell_object(obj,TMI("ctell name="+me->query("name")+";ID="+me->query("id")+";icon="+me->query("icon")+";"+msg));
	    return  1;
	    }
			
   if (!obj)
	    {
	    write(ALERT("没有这个人。\n"));
	    return  1;
	    }

   if (!me->visible(obj))
	    {
	    write(ALERT("没有这个人。\n"));
	    return  1;
		}

   if (!interactive(obj))
	   {
	   write(ALERT("没有这个人。\n"));
	   return  1;
	   }

   if (obj==me)
	   {
	   write(ALERT("你在自言自语的不知道在说什么。\n"));
	   return 1;
	   }

   if (obj->query("xieyi/zmud"))
	   {
	   write(ALERT("对方的客户端不支持Tomud协议，发送失败。\n"));
	   return 1;
	   }
	   
	   debug(sprintf( YEL "%s(%s)告诉%s(%s)：%s" NOR,me->name(1),me->query("id"),obj->name(1),obj->query("id"), msg));

   if ( member_array("tell", me->query("channels"))==-1)
	   {
	   me->set("channels", me->query("channels") + ({ "tell" }) );
	   write(ALERT("你的 tell 频道被打开！\n"));
	   //return 1;
	   }

    if ( (pointerp(obj->query("channels")) && member_array("tell", obj->query("channels"))==-1) && !wizardp(me))
	   {
		write(ALERT(obj->name(1)+"已经把私聊频道关掉了。\n"));
        return 1;
	   }

    if (me->id(obj->query("env/no_tell")) )
	   {
		write(ALERT(obj->name(1)+"在生你的闷气，不想和你说话。\n"));
        return 1;
	   }
	   
	   tell_object(obj,TMI("ctell name="+me->query("name")+";ID="+me->query("id")+";icon="+me->query("icon")+";"+msg));
	   write(ALERT("你说的话已成功传送到"+obj->query("name")+"耳边。\n"));
	   wiz=filter_array( users() , "party_listener", this_object(), (wizardp(me)) );
	   message("rumor",HIW"〖TELL监听〗："HIG+me->query("name")+NOR"("HIY+me->query("id")+NOR")"HIW"→"HIG+obj->query("name")+NOR"("HIY+obj->query("id")+NOR")"HIW"："HIB+msg+NOR"\n",wiz);

    if (query_idle(obj)>120)
	   {
		write(ALERT(obj->name(1)+"已经发呆"+query_idle(obj)/60+"分钟，看来不会马上回答你哟！\n"));
	   }

    if (in_edit(obj))
	   {
		write(ALERT(obj->name(1)+"好像正在编辑档案！\n"));
	   }

	   obj->set_temp("reply", me->query("id"));
	   return 1;
}
string remote_tell(string cname, string from, string mud, string to, string msg)
{
    object ob;
    if( ob = find_player(to) )
	   {
		if( cname )
			tell_object(ob, sprintf(BOLD "%s(%s@%s)千里传音你：%s\n" NOR,cname, capitalize(from), mud, msg ));
        else
			tell_object(ob, sprintf(BOLD "%s@%s 千里传音你：%s\n" NOR,capitalize(from), mud, msg ));
		ob->set_temp("reply", from + "@" + mud);
        return ob->name(1);
	   } else
		   return 0;
}

int party_listener(object ppl)
{
	if( !environment(ppl))
		return 0;
	if(wizardp(ppl))
		return 1;
	else
		return 0;
}

int help(object me)
{
    write(@HELP
指令格式：tell <某人> <讯息>
你可以用这个指令和其他地方的使用者说话。
其他相关指令：reply
HELP
    );
    return 1;
}

