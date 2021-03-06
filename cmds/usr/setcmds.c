// 离线闭关指令集 By 龙云梦(Wenwu) On 2006年1月21日

#include <ansi.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

int set_biguan_cmds(object ob, string cmds);

int main(object me, string arg)
{
	string str, *str_list, msg;
	int i;

	if ( !arg || arg == "" )
	{
		if ( file_size(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__) != -1 )
		{
			write(HIW"你设定的离线修炼指令集如下：\n"NOR);
			str = read_file(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__);
			msg = "\n";

			str_list = explode(str,"\n");
			for (i = 0; i < sizeof(str_list); i++)
			{
				msg += (HIW"第 "HIG + (i + 1) + HIW" 条指令 - "HIY + str_list[i] + "\n"NOR);
			}

			me->start_more(msg);

			return 1;
		}
		else
			return notify_fail(HIY"离线修炼指令集不能为空，\n"NOR);
	}
	if ( arg == "-r" )
	{
		if ( file_size(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__) != -1 )
		{
			rm(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__);
			write(HIW"成功清除离线修炼指令集。\n"NOR);
			return 1;
		}
		else
		{
			write(HIW"你并没有设置离线修炼指令集。\n"NOR);
			return 1;
		}
	}

	if ( strlen(arg) > 300 )
		return notify_fail(HIY"你设定的离线修炼指令集太长了，请控制在300个字节以内，\n"NOR);

	if ( file_size(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__) != -1 )
	{
		write(HIW"你以前已设定有离线修炼指令集：\n"NOR);
		str = read_file(DATA_DIR + "biguan/" + me->query("id") + __SAVE_EXTENSION__);
		msg = "\n";

		str_list = explode(str,"\n");
		for (i = 0; i < sizeof(str_list); i++)
		{
			msg += (HIW"第 "HIG + (i + 1) + HIW" 条指令 - "HIY + str_list[i] + "\n"NOR);
		}

		msg += HIC"\n你是否要覆盖原有指令集？["HIG"Y"HIW" / "HIR"N"HIY"]："NOR;
		write(msg);
		input_to("get_biguan_cmds", 1, me, arg);
	}
	else
		set_biguan_cmds(me, arg);

	return 1;
}

int get_biguan_cmds(string arg, object ob, string str)
{
	if ( strsrch(arg,"Y") != -1 || strsrch(arg,"y") != -1 )
	{
		set_biguan_cmds(ob, str);
		return 1;
	}
	else
	{
		write(HIY"\n你取消了覆盖操作，依旧使用原有离线修炼指令集。\n"NOR);
		return 0;
	}
}

int set_biguan_cmds(object ob, string cmds)
{
	string msg, str, *str_list, *args, *arg, msg_list, cmd_msg = "";
	int i = 0, j = 0, cmds_num = 0, list = 0;

	args = explode(cmds, "|");
	cmds_num = sizeof(args);
	for (i = 0; i < cmds_num; i++)
	{
		if ( strsrch(args[i],"#") != -1 )
		{
			msg_list = "";
			arg = explode(args[i], " ");
			list = atoi(replace_string(arg[0], "#", ""));
			if ( list < 0 )
				list = 1;
			else if ( list > 10)
				list = 10;
			cmd_msg = replace_string(args[i], arg[0] + " ", "");
			for (j = 0; j < list; j++)
			{
				msg_list = msg_list + cmd_msg;

				if ( j < list - 1 )
					msg_list += "|";
			}
			cmds = replace_string(cmds, args[i], msg_list);
		}
	}

	msg = replace_string(cmds, "|", "\n");
	
	if ( write_file(DATA_DIR + "biguan/" + ob->query("id") + __SAVE_EXTENSION__, msg, 1) )
	{
		write(HIG"\n你成功设定了离线修炼指令集：\n"NOR);
		str = read_file(DATA_DIR + "biguan/" + ob->query("id") + __SAVE_EXTENSION__);
		msg = "\n";

		str_list = explode(str,"\n");
		for (i = 0; i < sizeof(str_list); i++)
		{
			msg += (HIW"第 "HIG + (i + 1) + HIW" 条指令 - "HIY + str_list[i] + "\n"NOR);
		}

		ob->start_more(msg);
		return 1;
	}
	else
	{
		write(HIR"\n离线修炼指令集设定失败。\n"NOR);
		return 0;
	}
}

int help()
{
	write(@TEXT
指令格式：setcmds AAA|AAA|AAA|BBB|BBB|CCC
      或：setcmds #3 AAA|#2 BBB|CCC
          [AAA和BBB及CCC都代表一个指令]
使用这个指令可以设定你离线修炼时让系统定时帮你执行的指令。
   
例如：
[1]、 你想在离线修炼时系统帮你定时打坐修炼内力，你可以设定为：
      setcmds exercise 100
      这样在你离线修炼时系统就会定时帮你打坐练内了。	
[2]、 如果你想在离线修炼时系统帮你循环执行两条指令，则可以用
      竖号[|] 把两个指令间隔开来，例如：你想让系统帮你先读书
      后再用内力恢复精神就可以设定为：
      setcmds study book|exert regenerate
      这样系统就会帮你先读书一次，然后用内力恢复精神了。
[3]、 当然，你想让系统在你离线修炼时帮你循环执行更多指令，可以
      像以上例子一样把每个指令之间都用 竖号[|] 间隔开来。
[4]、 当然也支持#10这种格式，意思就是一个指令循环10次。
      如：你想让系统帮你读书三次，然后用内力恢复精神。那么可以
      像下面这么设置：
      setcmds #3 study book|exert regenerate
      如你不想用#3的格式，像下面这样效果也是一样的
      setcmds study book|study book|study book|exert regenerate
[5]、 注意：也许你会发现设置的指令集长度会受到限制，是的，指令集
      的长度限制在300个字符以内。别担心这足够你用了的，系统支持
      解析通过 alias 设置的简化指令。
      例如：如果原形的读书指令设置如下
      setcmds #3 study book|exert regenerate
      那么我们可以通过 alias 把指令简化后再来设置，如下：
      alias du study book;
      alias xj exert regenerate;
      setcmds #3 du|xj
      好了，我们来看看
      setcmds #3 du|xj
      是不是比
      setcmds #3 study book|exert regenerate
      在长度上短了很多呢。
[6]、 如果你想删除离线练功指令集可以使用如下指令
      stecmds -r
注意：离线练功时，系统只帮你执行一种练功模式，要么就是你现在设置的这个
      定时器模式的计划练功，要么就是另一种触发练功模式，触发练功模式
      请参考 help setchufa
      特别注意，触发练功模式的优先级比你目前设置的这个定时器计划练功
      模式要高，如你想使用定时器计划练功模式，务必要关闭触发练功模式，
      关闭触发功能的指令：setchufa -stop
TEXT
	);
	return 1;
}