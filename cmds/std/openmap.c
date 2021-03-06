// webuser.c


inherit F_CLEAN_UP;

int main( object me,string arg )
{
	if(!arg || arg != "None")
		arg = "";

	if( me->is_busy() )
		return notify_fail("你的上一个动作还未完成。\n");
	
	if( me->is_fighting() )
		return notify_fail("你正在战斗中。\n");

	if( me->query("temp_time_map") && arg == "None" )
		return notify_fail("你的即时地图功能已是关闭的。\n");

	if( !me->query("temp_time_map") && arg != "None" )
		return notify_fail("你的即时地图功能已是打开的。\n");
	
	if(arg == "None")
	{
		me->set("temp_time_map",1);
		write("你关闭了即时地图功能。\n");
	}
	else
	{
		me->delete("temp_time_map");
		write("你打开了即时地图功能。\n");
	}
	return 1;
}

int help( object me)
{
	write(@HELP
指令格式: openmap None|xxx
该指令可以让你关闭或打开即时地图功能。

HELP
	);
        return 1;
}
