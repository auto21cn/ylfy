// find
#include <ansi.h>

int main(object me, string arg)
{
	string file, *list, file_name, str, old_msg;
	int i;

	if ( !arg ) return notify_fail("指令格式：find 文件名,查找的字串\n");
	if ( sscanf(arg, "%s,%s", file_name, str) != 2 ) return notify_fail("指令格式：find 文件名,查找的字串\n");
	if ( file_size(file_name) < 1 ) return notify_fail("没有这个文件("+arg+")。\n");

	file = read_file(file_name);
	if ( strsrch(file, "\n") == -1 ) return notify_fail("文件("+arg+")只有一行。\n");
	list = explode(file, "\n");
	for ( i = 0; i < sizeof(list); i++ )
	{
		old_msg = replace_string(list[i], list[i], lower_case(list[i]));
		if ( sscanf(old_msg, "%*s"+lower_case(str)+"%*s") )
		{
			list[i] = replace_string(list[i], str, HIY+str+HIW);
			if ( i > 0 )
				write("第"HIY+i+NOR"行："NOR+list[i-1]+"\n"NOR);
			write(HIG"第"HIY+(i+1)+HIG"行："HIW+list[i]+"\n"NOR);
			if ( i < sizeof(list) - 1 )
				write("第"HIY+(i+2)+NOR"行："NOR+list[i+1]+"\n"NOR);
			write("----------------------------------------------------------------------\n");
		}
	}

	return 1;
}