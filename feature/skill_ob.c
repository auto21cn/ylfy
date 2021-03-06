
#include <ansi.h>
inherit F_DBASE;

// 系统启动时读取 skill
int load_skill_ob(string str)
{
	mixed *dir;
	int i, v = 0;

	if ( str[0..0] != "/" )
		str = "/" + str;

	if ( str[(sizeof(str)-1)..(sizeof(str)-1)] != "/" )
		str = str + "/";

	dir = get_dir("/binaries" + str, -1);
	
	for (i = 0; i < sizeof(dir); i++)
	{
		if ( file_size("/binaries" + str + dir[i][0]) < 0 )
			continue;

		if ( !find_object(str + dir[i][0][0..<3]) )
		{
			if ( load_object(str + dir[i][0][0..<3]) )
				v++;
		}
	}

	if ( v > 0 )
	{
		write("加载成功。\n");
		return 1;
	}
	
	write("加载失败。\n");
	return 0;
}