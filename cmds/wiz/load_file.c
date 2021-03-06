inherit F_SKILL_OB;

int help(object me);

int main(object me, string arg)
{
	if ( !arg )
		return notify_fail("你要加载哪个文件？\n");

	if ( arg[0..0] != "/" )
		arg = "/" + arg;

	if ( arg[(sizeof(arg)-1)..(sizeof(arg)-1)] == "/" )
	{
		load_skill_ob(arg);
		return 1;
	}

	if ( file_size("/binaries" + arg + ".b") > 0 )
	{
		if ( !find_object(arg) )
		{
			if ( load_object(arg) )
			{
				write("成功加载文件 " + arg + " 。\n");
				return 1;
			}
			else
				return 0;
		}
		else
			return notify_fail("加载失败，文件 " + arg +" 已存在于内存。\n");
	}
	else
		return notify_fail(arg + " 的二进制文件不存在。\n");
}

int help(object me)
{
	write(@HELP
指令格式 : load_file string
载入文件文件名[string]。
string 最后一个字符为 '/' 时则为载入目录。
HELP
);
	return 1;
}