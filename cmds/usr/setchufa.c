// 离线闭关指令集 By 龙云梦(Wenwu) On 2006年1月21日

#include <ansi.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str, *str_list, msg, chufa_msg, chufa_cmds;
	int i, line;

	if ( !arg || arg == "" )
	{
		if ( file_size(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__) > 0 )
		{
			write(HIC"您目前已设定有的触发如下：\n"NOR);
			str = read_file(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__);
			msg = HIW"";

			str_list = explode(str,"\n");
			for (i = 0; i < sizeof(str_list); i++)
			{
				if ( sscanf(str_list[i], "%s:%s", chufa_msg, chufa_cmds) )
				{
					chufa_cmds = replace_string(chufa_cmds, "-", ";");
					msg += "-----------------------------------------------\n";
					msg += "(" + chinese_number(i+1) + ")\n";
					msg += HIY"触发字符："HIW + chufa_msg + "\n";
					msg += HIY"触发指令："HIW + chufa_cmds + "\n";
					msg += "-----------------------------------------------\n";
				}
			}

			msg += "\n"NOR;
			me->start_more(msg);

			return 1;
		}
		else
			return notify_fail(HIW"指令格式：setchufa 触发字符:执行指令\n"HIY"[提示：如需设置多个指令，每个指令之间用一横[-]间隔开]\n"NOR);
	}
	
	if ( arg == "-r" )
	{
		if ( file_size(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__) >= 0 )
		{
			rm(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__);
			write(HIW"成功清除触发设置。\n"NOR);
			return 1;
		}
		else
		{
			write(HIW"你并没有设置触发。\n"NOR);
			return 1;
		}
	}

	if ( sscanf(arg, "-r %d", line) )
	{
		if ( file_size(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__) > 0 )
		{
			str = read_file(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__);
			str_list = explode(str,"\n");
			
			if ( line > sizeof(str_list) )
				return notify_fail(HIY"第 " + chinese_number(line) +" 条触发设置不存在。\n"NOR);

			msg = "";

			for (i = 0; i < sizeof(str_list); i++)
			{
				if ( i + 1 == line )
				{
					if ( sscanf(str_list[i], "%s:%s", chufa_msg, chufa_cmds) )
					{
						chufa_cmds = replace_string(chufa_cmds, "-", ";");
						write(HIR"你成功删除第" + chinese_number(line) + "条触发如下：\n");
						write("-----------------------------------------------\n");
						write(HIY"触发字符："HIW + chufa_msg + "\n");
						write(HIY"触发指令："HIW + chufa_cmds + "\n");
						write("-----------------------------------------------\n");
					}

					continue;
				}

				msg += str_list[i] + "\n";
			}

			write_file(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__, msg, 1);
			return 1;
		}
		else
			return notify_fail(HIY"你目前并没有触发设置。\n"NOR);
	}

	if ( arg == "-stop" )
	{
		if ( me->query("xyzx_chufa_stop") )
			return notify_fail(HIY"你并没有开启触发功能，不需要再关闭。\n"NOR);

		me->set("xyzx_chufa_stop", 1);
		write(HIR"你关闭了触发功能。\n"NOR);
		return 1;
	}

	if ( arg == "-run" )
	{
		if ( !me->query("xyzx_chufa_stop") )
			return notify_fail(HIY"你并没有关闭触发功能，不需要再开启。\n"NOR);

		me->delete("xyzx_chufa_stop");
		write(HIG"你开启了触发功能。\n"NOR);
		return 1;
	}

	if ( strlen(arg) > 300 )
		return notify_fail(HIY"你的触发设定太长了，请控制在300个字节以内，\n"NOR);

	if ( file_size(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__) > 0 )
	{
		str = read_file(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__);
		str_list = explode(str,"\n");

		if ( sizeof(str_list) >= CHUFA_CMD_SIZE )
			return notify_fail(HIY"你只能设置" + chinese_number(CHUFA_CMD_SIZE) + "条触发，需要删除一些触发才能继续设置。\n"NOR);
	}

	if ( sscanf(arg, "%s:%s", chufa_msg, chufa_cmds) )
	{
		if ( write_file(DATA_DIR + "chufa/" + me->query("id") + __SAVE_EXTENSION__, chufa_msg + ":" + chufa_cmds + "\n") )
		{
			chufa_cmds = replace_string(chufa_cmds, "-", ";");
			write(HIG"你成功增加了一条触发如下：\n");
			write("-----------------------------------------------\n");
			write(HIY"触发字符："HIW + chufa_msg + "\n");
			write(HIY"触发指令："HIW + chufa_cmds + "\n");
			write("-----------------------------------------------\n");
		}
		else
			write(HIW"增加触发失败。\n");
	}
	else
		return notify_fail(HIW"指令格式：setchufa 触发字符:执行指令\n"HIY"[提示：如需设置多个指令，每个指令之间用一横[-]间隔开]\n"NOR);

	return 1;
}

int help()
{
	write(@TEXT
指令格式：
[一]、增加一条触发：setchufa 触发字符:执行指令
      例如：我想触发“运功完毕”，也就是屏幕上出现“运功完毕”，我就
      让他打坐练内，那么我们可以如下面这么设置：
      setchufa 运功完毕:dazuo 100
      执行看看，你会发现只要屏幕上一出现“运功完毕”这些字，系统就会
      自动帮你用100点内力打坐。
      也许你会问：如果我想屏幕上出现“运功完毕”就先读书一次再打坐，
      也就是屏幕上出现“运功完毕”时同时执行两个指令，那怎么设置呢？
      很简单，你只需要把各个指令之间用一横[-]间隔开就可以了。如下：
      setchufa 运功完毕:study book-dazuo 100
      系统就会在屏幕上出现“运功完毕”时就先帮你读书读书一次再打坐了。
      当然也同离线计划练功一样也是支持 alias 简化指令的。
[二]：查看设置的所有触发：setchufa
[三]：删除一条触发：setchufa -r 数字
      说明：这个数字就是你要删除的那条触发的位置，可以通过setchufa
      查看你要删除的那条触发的位置。
[四]：删除所有触发：setchufa -r
[五]：关闭触发：setchufa -stop
[六]：启动触发：setchufa -run
注意：离线练功时，系统只能帮你执行一种练功模式，要么就是触发练功，要不
      就是计划定时器模式练功。计划定时器模式练功请参考help setcmds
      另外每条触发执行的指令最多只能5条，就算你设置超过5条系统执行时
      也会抛掉。特别注意，触发默认是开启的，只要你设置了触发，触发就
      会运行的。
TEXT
	);
	return 1;
}