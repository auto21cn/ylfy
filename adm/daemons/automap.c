// 动态地图自动生成器 By 龙云梦(Wenwu) On 2006年1月6日
/* -----------------------------------------------
---  随手写的个动态地图生成系统，写得很简单，当初之
---  所以写这个代码是因为我懒，懒得一个个去写每个房
---  房的细节。：）这个系统很简单，创建一个大小为
---  MAX_SIZE 个Room的地图，其中在第一个Room和最后
---  一个Room之间生成一条绝对的路径，然后再随机创建
---  MAX_OUTS 个出口。定义 MAKE_AUTO_MAP_NPCS 则在
---  其中放置 NPC。
-------------------------------------------------- */

#define MAKE_AUTO_MAP_NPCS

// 原始地图文件
#define THIS_MAP_FILE "/clone/map/map.c"
// 入口接口文件
#define ENTER_MAP_FILE "/d/migong/migong1"
// 出口接口文件
#define OUT_MAP_FILE "/d/migong/migong2"
// NPC文件
// -------------------------------------------
#define MAP_NPC_ONE   "/clone/map/npc/guai"
#define MAP_NPC_TWO   "/clone/map/npc/jinlong"
#define MAP_NPC_THREE "/d/migong/lev15/npc/boss"
#define MAP_NPC_FOUR  "/clone/map/npc/guai_boss"
#define MAP_NPC_FIVE  "/clone/map/npc/char_boss"
// -------------------------------------------
// 入口方向
#define ENTER_MAP_OUT "east"
// 出口方向
#define OUT_MAP_OUT "east"

#include <ansi.h>

inherit F_DBASE;

void create()
{
	seteuid( ROOT_UID );
	set("channel_id","地图创建精灵");
	set("fs_xx_msg",1);
	CHANNEL_D->do_channel( this_object(), "sys", HIM"地图创建精灵已经启动。\n"NOR);
	set_heart_beat(9);
}

// 出口
string *direc = ({"north", "south", "east", "west", /*"northup", "southup", "eastup", "westup", "northdown", 
	"southdown", "eastdown", "westdown",*/ "northeast", "northwest", "southeast", "southwest", /*"up", "down",
	"enter", "out"*/
	});

// 相应接口
mapping pairs = ([
	"north":     "south",
	"south":     "north",
	"east":      "west",
	"west":      "east",
	"northup":   "southdown",
	"southup":   "northdown",
	"eastup":    "westdown",
	"westup":    "eastdown",
	"northdown": "southup",
	"southdown": "northup",
	"eastdown":  "westup",
	"westdown":  "eastup",
	"northeast": "southwest",
	"northwest": "southeast",
	"southeast": "northwest",
	"southwest": "northeast",
	"up":        "down",
	"down":      "up",
	"enter":     "out",
	"out":       "enter",
	]);

string set_room_outs(string out1, string out2, int room);

private void heart_beat()
{
	string this_file, this_enter, this_out, this_outs, *direc_new, this_room_file, this_npc;
	mixed *file;
	object obj, *ob;
	int i, k, rooms;

	rooms = 0;

	if ( time() - query("update_map_time") < 3600 * get_system_config(DATA_CONFIG_DIR "auto_map.h", "UPDATE_MAP_TIME") )
	{
		add("fs_xx_msg",1);

		if ( query("fs_xx_msg") % 20 == 1 )
		{

#ifdef XYZX_AUTO_MAP_DEBUG

			CHANNEL_D->do_channel( this_object(), "sys", HIW"距离动态地图更新时间还有 "HIY+((3600 * UPDATE_MAP_TIME)-(time()-query("update_map_time")))/3600+HIW" 小时 "HIG+(((3600 * UPDATE_MAP_TIME)-(time()-query("update_map_time")))%3600)/60+HIW" 分。\n"NOR);

#endif

			message("channel:chat", HIY"【镜花水月】"+HIM"动态地图[迷雾森林]距离下次更新时间还有 "HIW+((3600 * get_system_config(DATA_CONFIG_DIR "auto_map.h", "UPDATE_MAP_TIME"))-(time()-query("update_map_time")))/3600+HIM" 小时 "HIG+(((3600 * get_system_config(DATA_CONFIG_DIR "auto_map.h", "UPDATE_MAP_TIME"))-(time()-query("update_map_time")))%3600)/60+HIM" 分。\n"NOR,users() );
		}
		
		return;
	}

	file = get_dir(get_system_config(DATA_CONFIG_DIR "auto_map.h", "AUTO_MAP"), -1);

	// 检查创建地图文件所需的目录
	if ( !sizeof(file) )
	{
		if ( file_size(get_system_config(DATA_CONFIG_DIR "auto_map.h", "AUTO_MAP")) != -2 )
		{
			CHANNEL_D->do_channel( this_object(), "sys", HIY"未指定创建目录，动态地图创建失败。\n"NOR);
			return;
		}
	}
	else
	{
		// 删除地图文件
		for (i = 0; i < sizeof(file); i++)
		{
			if ( i == 0 )
			{
				CHANNEL_D->do_channel( this_object(), "sys", HIY"开始清除原有动态地图。\n"NOR);
				message("channel:chat", HIY"【镜花水月】"+HIM"动态地图[迷雾森林]开始重新组建更新。\n"NOR,users() );	
			}

			obj = find_object( get_system_config(DATA_CONFIG_DIR "auto_map.h", "AUTO_MAP") + file[i][0] );

			if ( obj )
			{
				ob = all_inventory(obj);

				if ( sizeof(ob) )
				{
					for (k = 0; k < sizeof(ob); k++)
					{
						if ( userp(ob[k]) )
						{
							tell_object(ob[k],HIY"迷雾森林已更新，迷迷糊糊中您又回到了入口处。\n"NOR);
							ob[k]->move(ENTER_MAP_FILE);
						}
						else
							destruct(ob[k]);
					}
				}

				destruct(obj);
				rooms++;
			}

			if ( file_size(get_system_config(DATA_CONFIG_DIR "auto_map.h", "AUTO_MAP") + file[i][0]) != -1 )
				rm(get_system_config(DATA_CONFIG_DIR "auto_map.h", "AUTO_MAP") + file[i][0]);

			if ( i == sizeof(file) -1 )
				CHANNEL_D->do_channel( this_object(), "sys", HIY"原有动态地图清除完毕，其中销毁 "HIR + rooms +HIY" 个ROOM，删除 "HIW + (i+1) + HIY" 个文件\n"NOR);
		}

		return;
	}

	if ( file_size(THIS_MAP_FILE) != -1 )
	{
		CHANNEL_D->do_channel( this_object(), "sys", HIG"开始创建大小为 "HIW + get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_SIZE") + HIG" 个房间的动态地图。\n"NOR);
		this_file = read_file(THIS_MAP_FILE);
		
		for ( i = 0; i < get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_SIZE"); i++ )
		{
			// 入口房间
			if ( i == 0 )
			{
				this_enter = pairs[ENTER_MAP_OUT];
				direc_new = direc - ({this_enter});
				this_out = direc_new[random(sizeof(direc_new))];
				this_outs = "\n\"" + this_enter + "\" : \"" + ENTER_MAP_FILE +"\",\n" + 
					"\"" + this_out + "\" : __DIR__\"" + (i + 1) +"\",\n";
			}
			else if ( i == get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_SIZE") -1 ) // 出口房间
			{
				this_enter = pairs[this_out];
				this_out = OUT_MAP_OUT;
				this_outs = "\n\"" + this_enter + "\" : __DIR__\"" + (i - 1) +"\",\n" + 
					"\"" + this_out + "\" : \"" + OUT_MAP_FILE +"\",\n";
			}
			else // 中间房间
			{
				this_enter = pairs[this_out];
				direc_new = direc - ({this_enter});
				this_out = direc_new[random(sizeof(direc_new))];
				this_outs = "\n\"" + this_enter + "\" : __DIR__\"" + (i - 1) +"\",\n" + 
					"\"" + this_out + "\" : __DIR__\"" + (i + 1) +"\",\n";
			}

			if ( get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_OUTS") )
				this_outs += set_room_outs(this_enter, this_out, i);

			this_room_file = replace_string(this_file, "set(\"exits\", ([", "set(\"exits\", ([" + this_outs);

#ifdef MAKE_AUTO_MAP_NPCS
			
			// 第一种怪
			if ( i > 4 && i % 5 == 0 )
			{
				this_npc = "\n\"" + MAP_NPC_ONE +"\" : 1,\n";
				this_room_file = replace_string(this_room_file, "set(\"objects\", ([", "set(\"objects\", ([" + this_npc);
			}

			// 第二种怪
			if ( i > 149 && i % 150 == 0 )
			{
				this_npc = "\n\"" + MAP_NPC_TWO +"\" : 1,";
				this_room_file = replace_string(this_room_file, "set(\"objects\", ([", "set(\"objects\", ([" + this_npc);
			}

			// 第三种怪
			if ( i > 498 && i % 499 == 0 )
			{
				this_npc = "\n\"" + MAP_NPC_THREE +"\" : 1,";
				this_room_file = replace_string(this_room_file, "set(\"objects\", ([", "set(\"objects\", ([" + this_npc);
			}

			// 第四种怪
			if ( i > 49 && i % 50 == 0 )
			{
				this_npc = "\n\"" + MAP_NPC_FOUR +"\" : 1,";
				this_room_file = replace_string(this_room_file, "set(\"objects\", ([", "set(\"objects\", ([" + this_npc);
			}

			// 第五种怪
			if ( i > 299 && i % 300 == 0 )
			{
				this_npc = "\n\"" + MAP_NPC_FIVE +"\" : 1,";
				this_room_file = replace_string(this_room_file, "set(\"objects\", ([", "set(\"objects\", ([" + this_npc);
			}

#endif
			
			write_file(get_system_config(DATA_CONFIG_DIR "auto_map.h", "AUTO_MAP") + i + ".c", this_room_file, 1);

			if ( i == get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_SIZE") - 1 )
			{
				CHANNEL_D->do_channel( this_object(), "sys", HIM"动态地图创建完毕。\n"NOR);
				message("channel:chat", HIY"【镜花水月】"+HIM"动态地图[迷雾森林]更新完毕，江湖有志之士又可以来阅历一番了。\n"NOR,users() );	
				set("update_map_time",time());
			}
		}
	}
	else
	{
		CHANNEL_D->do_channel( this_object(), "sys", HIY"未找到原始地图文件，动态地图创建失败。\n"NOR);
		return;
	}

	return;

}

// 生成随机接口
string set_room_outs(string out1, string out2, int room)
{
	string outs, msg, *direc_gx;
	int j;

	direc_gx = direc - ({out1});
	direc_gx -= ({out2});

	for (j = 0; j < get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_OUTS"); j++)
	{
		msg = direc_gx[random(sizeof(direc_gx))];
		direc_gx = direc_gx - ({msg});

		if ( j == 0 )
			outs = "\"" + msg + "\" : __DIR__\"" + random((int)get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_SIZE")*2/3) +"\",\n";
		else
			outs += "\"" + msg + "\" : __DIR__\"" + random((int)get_system_config(DATA_CONFIG_DIR "auto_map.h", "MAX_SIZE")*2/3) +"\",\n";
	}

	return outs;
}