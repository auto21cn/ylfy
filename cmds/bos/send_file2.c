// send_file

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	
	if ( !interactive(me) )
		return 0;

	seteuid(getuid());

	if ( !arg )
		return notify_fail("你要连接哪里？\n");

	//if ( file_size(file) < 0 )
		//return notify_fail("你要发送的文件不存在。\n");

	"/adm/daemons/network/server_bf"->connect_to(arg);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式: send_file Ip Port@File#pass

这个指令可以让你向远端服务器(ip port)传送文件(File)

HELP );
        return 1;
}
