// 地图源文件

#define SHORT_NAME "迷雾森林"
#define LONG_NAME "迷雾森林一向是江湖人既向往而又畏惧的地方，这里到处充斥着死亡的气息，\n也不知道是哪朝哪代谁人发现的这里，也许远古的时候就已经有了吧。这里树木\n遮天难见光日，处处隐藏着杀机，传说中迷雾森林是通往精灵神界的必经之路。\n“精灵神界”？多么令人向往啊，可是迷雾森林路径繁杂宛如迷宫又怎么能走得\n出去呢？更甚之到处隐藏着各种妖魔猛兽，步步凶险，虽然如此来迷雾森林探险\n的人还是络绎不绝，毕竟这里的各种奇珍异宝都是江湖人梦寐以求的，更有传闻\n迷雾森林是魔法的开始，“魔法“...？？？又是一个诱人的新名词，有了魔法\n对江湖人来说不谓是如虎添翼，每天每时每刻都有各色江湖人物不断在迷雾森林，\n探险...伤残...死亡...情...仇...爱...恨...欢欣...忧悒...不断在迷雾森林\n里反复演义.....\n"

inherit ROOM;

void create()
{
	set("outdoors", "automap");
	set("short", SHORT_NAME);
	set("long", LONG_NAME);
	set("exits", ([
"east" : __DIR__"42",
"north" : __DIR__"44",
"west" : __DIR__"782",
"northeast" : __DIR__"755",
"northwest" : __DIR__"735",
]));
	set("objects", ([]));
	setup();
}

int valid_leave(object me, string dir)
{
	mapping exits;
	string file_name;

	exits = this_object()->query("exits");

	if ( mapp(exits) && sizeof(exits) )
	{
		if ( !stringp(file_name = exits[dir]) )
			return notify_fail("地图连接错误，请用 sos 通知管理员修改。\n");
		if ( strlen(file_name) < 10 )
			return notify_fail("连接的区域不正确，请用 sos 通知管理员修改。\n");
		if ( !playerp(me) && base_name(this_object())[0..9] != file_name[0..9] )
			return 0;
	}

	return ::valid_leave(me, dir);
}