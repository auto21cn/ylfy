// rmdir.c
inherit F_CLEAN_UP;
int help(object me);
int main(object me, string arg)
{
	string dir;
	if(!arg) return help(me);
	dir = resolve_path(me->query("cwd"), arg);
   if (! (int)SECURITY_D->valid_write(dir,me,"write") )
		return notify_fail("你没有删除这个目录的权利。\n");
	seteuid(geteuid(me));
	if( rmdir(dir) )
		write("Ok.\n");
	else
		write("删除失败。\n");
	return 1;	
}
int help(object me)
{
	write(@HELP
指令格式 : rmdir <子目录名>
删除一个子目录。
HELP
	);
	return 1;
}
