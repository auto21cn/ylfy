#include <help.h>
#include <liebiao.h>
inherit F_CLEAN_UP;

string *default_search = DEFAULT_SEARCH_PATHS;
string *wizard_search = DEFAULT_WIZARD_PATHS;

int main(object me, string arg)
{
	int i;
	string file, show, *search;
	// If no topic specified, give the topics.
	if ( !arg ) 
	{
		show = read_file(HELP_DIR + "main0.txt");
                show = trans_color(show, 2);
                write(show);
                input_to("select");
		return 1;
	}
	// Else, try if a command name is specified.
	seteuid(getuid());
	if ( stringp(file = me->find_command(arg)) ) 
	{
		notify_fail("有这个指令存在，但是并没有详细的说明文件。\n");
		return file->help(me);
	}
	// Search the individual search path first.
	if ( pointerp(search = me->query("help_search_path")) ) 
	{
		i = sizeof(search);
		while (i--) 
		{
			if ( file_size(file=search[i]+arg+".txt") > 0 ) 
			{
				show = read_file(file);
				show += "\n";
				show = trans_color(show, 2);
				me->start_more(show);
				return 1;
			}
		}
	}
	// Finally, search the default search paths.
	if ( pointerp(default_search) ) 
	{
		i = sizeof(default_search);
		while (i--) 
		{
			if ( file_size(file=default_search[i]+arg+".txt") > 0 ) 
			{
				if ( default_search[i]=="/doc/skill/" && !wizardp(me) )
				{
					if ( !me->query_skill(arg, 1) ) 
						return notify_fail("你不会这种技能。\n");
				}
				show = read_file(file);
				show += "\n";
				show = trans_color(show, 2);
				me->start_more(show);
				return 1;
			}
		}
	}
	// Support efun/lfun help with same name as other topics such as
	// ed() and ed command.
	if ( wizardp(me) )
	{
		sscanf(arg, "%s()", arg);
		if ( pointerp(wizard_search) ) 
		{
			i = sizeof(wizard_search);
			while (i--) 
			{
				if ( file_size(file=wizard_search[i]+arg+".txt") > 0 ) 
				{
					show = read_file(file);
					show += "\n";
					show = trans_color(show, 2);
					me->start_more(show);
					return 1;
				}
			}
		}
	}
	return notify_fail("没有针对这项主题的说明文件。\n");
}

void select(string num,object me)
{
   string show="",arg;
   if(num=="1")
   {
       show = read_file(HELP_DIR + "main1.txt"); 
   }
   else if(num=="2")
   {
       show = read_file(HELP_DIR + "main2.txt"); 
   } 
   else if(num=="3")
   {
       show = read_file(HELP_DIR + "main3.txt"); 
   }
   else if(num=="4")
   {
       show = read_file(HELP_DIR + "main4.txt"); 
   }
   else if(num=="5")
   {
       show = read_file(HELP_DIR + "main5.txt"); 
   }
   else if(num=="6")
   {
       return; 
   }
   else
   { 
        write(" 无效的数字，请选择 1-4 数字选择！！！\n");
        main(me,arg);
   }
   show = trans_color(show, 2);
   write(show);
}

int help(object me)
{
        write(@HELP
指令格式：help <主题>              例如：> help cmds
<wizard>  help <函数名称>()        例如：> help call_out()
这个指令提供你针对某一主题的详细说明文件，若是不指定主题，则提供你有关
主题的文件。
HELP
        );
        return 1;
}
