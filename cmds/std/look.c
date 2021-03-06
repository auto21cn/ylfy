
#include <room.h>
#include <color.h>
#include <liebiao.h>

inherit F_CLEAN_UP;
inherit F_MAP_XY;

#include <item_sx.h>

mapping weapon_skill_type = ([
"sword"   :  "剑法",
"blade"   :  "刀法",
"axe"     :  "斧法",
"club"    :  "棍法",
"dagger"  :  "矛法",
"fork"    :  "叉法",
"hammer"  :  "锤法",
"staff"   :  "杖法",
"whip"    :  "鞭法",
"spear"   :  "枪法",
"unarmed" :  "拳套",
"throwing":  "暗器"
]);

mapping armor_type = ([
"cloth"   :  "衣服",
"armor"   :  "铠甲",
"boots"   :  "靴子",
"finger"  :  "戒指",
"hands"   :  "护手",
"head"    :  "帽子",
"neck"    :  "项链",
"shield"  :  "盾牌",
"surcoat" :  "披风",
"waist"   :  "腰带",
"wrists"  :  "护腕",
"pants"  :   "护腿"
]);

nosave string *all_exits = ({
	"east",
	"south",
	"west",
	"north",
	"eastup",
	"southup",
	"westup",
	"northup",
	"eastdown",
	"southdown",
	"westdown",
	"northdown",
	"northeast",
	"northwest",
	"southeast",
	"southwest",
	"up",
	"down",
	"enter",
	"out",
});

string *look_level_boy = ({
	BLU "眉歪眼斜，瘌头癣脚，不象人样" NOR,
 	BLU "呲牙咧嘴，黑如锅底，奇丑无比" NOR,
 	BLU "面如桔皮，头肿如猪，让人不想再看第二眼" NOR,
	HIB "贼眉鼠眼，身高三尺，宛若猴状" NOR,
	HIB "肥头大耳，腹圆如鼓，手脚短粗，令人发笑" NOR,
 	NOR "面颊凹陷，瘦骨伶仃，可怜可叹" NOR,
 	NOR "傻头傻脑，痴痴憨憨，看来倒也老实" NOR,
 	NOR "相貌平平，不会给人留下什么印象" NOR,
 	YEL "膀大腰圆，满脸横肉，恶形恶相" NOR,
 	YEL "腰圆背厚，面阔口方，骨格不凡" NOR,
 	RED "眉目清秀，端正大方，一表人才" NOR,
 	RED "双眼光华莹润，透出摄人心魄的光芒" NOR,
 	HIY "举动如行云游水，独蕴风情，吸引所有异性目光" NOR,
 	HIY "双目如星，眉梢传情，所见者无不为之心动" NOR,
 	HIR "粉面朱唇，身姿俊俏，举止风流无限" NOR,
 	HIR "丰神如玉，目似朗星，令人过目难忘" NOR,
 	MAG "面如美玉，粉妆玉琢，俊美不凡" NOR,
 	MAG "飘逸出尘，潇洒绝伦" NOR,
 	MAG "丰神俊朗，长身玉立，宛如玉树临风" NOR,
 	HIM "神清气爽，骨格清奇，宛若仙人" NOR,
 	HIM "一派神人气度，仙风道骨，举止出尘" NOR,
});

string *look_level_girl = ({
	BLU "丑如无盐，状如夜叉" NOR,
	BLU "歪鼻斜眼，脸色灰败，直如鬼怪一般" NOR,
	BLU "八字眉，三角眼，鸡皮黄发，让人一见就想吐" NOR,
	HIB "眼小如豆，眉毛稀疏，手如猴爪，不成人样" NOR,
	HIB "一嘴大暴牙，让人一看就没好感" NOR,
  	NOR "满脸疙瘩，皮色粗黑，丑陋不堪" NOR,
  	NOR "干黄枯瘦，脸色腊黄，毫无女人味" NOR,
  	YEL "身材瘦小，肌肤无光，两眼无神" NOR,
  	YEL "虽不标致，倒也白净，有些动人之处" NOR,
  	RED "肌肤微丰，雅淡温宛，清新可人" NOR,
  	RED "鲜艳妍媚，肌肤莹透，引人遐思" NOR,
  	HIR "娇小玲珑，宛如飞燕再世，楚楚动人" NOR,
  	HIR "腮凝新荔，肌肤胜雪，目若秋水" NOR,
  	HIW "粉嫩白至，如芍药笼烟，雾里看花" NOR,
  	HIW "丰胸细腰，妖娆多姿，让人一看就心跳不已" NOR,
  	MAG "娇若春花，媚如秋月，真的能沉鱼落雁" NOR,
  	MAG "眉目如画，肌肤胜雪，真可谓闭月羞花" NOR,
  	MAG "气质美如兰，才华馥比山，令人见之忘俗" NOR,
  	HIM "灿若明霞，宝润如玉，恍如神妃仙子" NOR,
  	HIM "美若天仙，不沾一丝烟尘" NOR,
  	HIM "宛如"+HIW+"玉雕冰塑"+HIM+"，似梦似幻，已不再是凡间人物" NOR,
});

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);

void create()
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	object obj;
	int result;
	
	if( !arg )
		result = look_room(me, environment(me));
	else if( (obj = present(arg, environment(me))) ||  (obj = present(arg, me)) )
	{
		if( obj->is_character() )
			result = look_living(me, obj);
		else
			result = look_item(me, obj);
	}
	else
		result = look_room_item(me, arg);
	
	return result;
}

int sort_exits(string str1,string str2)
{
	int i, j;
	
	if ( strcmp(str1,"a") < 0 && strcmp(str2,"a")<0 )
	{
		if (strlen(str1) < strlen(str2))
			return -1;
		
		if ( strlen(str1) == strlen(str2) )
			return strcmp(str1,str2);
		
		return 1;
	}
	else
	{
		i = member_array(str1, all_exits);
		j = member_array(str2, all_exits);
		
		if ( i > 0 && j > 0 )
			return i - j;
		else
			return strcmp(str1,str2);
	}
}

// 即时地图
void realtime_map(object me,object env)
{
        object room_obj;
        mapping exits;
    int i;
        string map_room, map_room2,jiantou;
     string *dirs;
        mapping alldirs=([      
                        "northwest" : "          ",
                        "north"     : "          ",
                        "northup"   : "          ",
                        "northeast" : "          ",
                        "west"      : "          ",
                        "east"      : "          ",
                        "southeast" : "          ",
                        "south"     : "          ",
                        "southwest" : "          ",
                        "southdown" : "          ",
                        "eastup"    : "          ",
                        "southup"   : "          ",
                        "northdown" : "          ",
                        "eastdown"  : "          ",
                        "westup"    : "          ",
                        "westdown"  : "          ",
                        "enter"     : "          ",
                        "out"       : "          ",
                        "up"        : "          ",
                        "down"      : "          ",
                        "left"      : "          ",
                        "right"     : "          ",
                        ]);  
       if( mapp(exits = env->query("exits")) ) 
        {                       
                dirs = keys(exits);
		   
                for(i=0; i< sizeof(dirs); i++)
                {
                        if(!room_obj = find_object(exits[dirs[i]])) {
                                room_obj = load_object(exits[dirs[i]]);
				    }
                        if(room_obj){
                                if (room_obj->query("short"))
							alldirs[dirs[i]] = room_obj->query("short");
					}
        
                }
        
                jiantou="  ";
                map_room2=alldirs["enter"];
                if(alldirs["enter"]!="          ")
				{
                        map_room2=alldirs["enter"];
                        jiantou=HIR+"∧"+NOR;
                }
                if(alldirs["up"]!="          "){
                        map_room2=alldirs["up"];
                        jiantou=HIC"〓"+NOR;
                        }
                if(alldirs["northdown"]!="          "){
                        map_room2=alldirs["northdown"];
                        jiantou="↓";
                        }
                if(alldirs["northup"]!="          "){
                        map_room2=alldirs["northup"];
                        jiantou="↑";
                        }
                if(alldirs["north"]!="          "){
                        map_room2=alldirs["north"];
                        jiantou="｜";
                        }
                map_room=map_room2;
                for(i=0;i<(10-strlen(map_room2))/2;i++)
                        {
                                map_room =map_room+" ";
                                map_room =" "+map_room;
                        }
                printf("             %10s  %-10s  %-10s\n",
                alldirs["northwest"],map_room,alldirs["northeast"]);
                
                printf("                        %s   %s   %s\n",
                alldirs["northwest"]=="          " ? "  ":"＼",
                jiantou,
                alldirs["northeast"]=="          " ? "  ":"／");
                
                jiantou="  ";
                map_room2=alldirs["westdown"];
                if(map_room2!="          ")
                                jiantou="←";
                if(alldirs["left"]!="          "){
                        map_room2=alldirs["left"];
                        jiantou="〈";
                        }
                if(alldirs["westup"]!="          "){
                        map_room2=alldirs["westup"];
                        jiantou="←";
                        }
                if(alldirs["west"]!="          "){
                        map_room2=alldirs["west"];
                        jiantou="--";
                        }
                printf("             %10s%s",map_room2,jiantou);        
                map_room2=env->query("short") ? env->query("short"): "----------";
                map_room=HIG+map_room2+NOR;
                for(i=0;i<(10-strlen(map_room2))/2;i++)
                        {
                                if(alldirs["east"]=="          ")
                                map_room =map_room + " ";
                                else map_room=map_room + "-";
                                if(alldirs["west"]=="          ")
                                map_room =" "+ map_room;
                                else map_room ="-"+map_room;
                        }
                printf("%s",map_room);
                
                jiantou="  ";
                map_room2=alldirs["eastup"];
                if(map_room2!="          ")
                                jiantou="→";
                if(alldirs["right"]!="          "){
                        map_room2=alldirs["right"];
                        jiantou="〉";
                        }
                if(alldirs["eastdown"]!="          "){
                        map_room2=alldirs["eastdown"];
                        jiantou="→";
                        }
                if(alldirs["east"]!="          "){
                        map_room2=alldirs["east"];
                        jiantou="--";
                        }
                
                printf("%s%-10s\n",jiantou,map_room2);
                
                jiantou="  ";
                map_room2=alldirs["out"];
                if(alldirs["out"]!="          "){
                        map_room2=alldirs["out"];
                        jiantou=HIR+"∨"+NOR;
                        }
                if(alldirs["down"]!="          "){
                        map_room2=alldirs["down"];
                        jiantou=HIC+"〓"+NOR;
                        }
                
                if(alldirs["southdown"]!="          "){
                                map_room2=alldirs["southdown"];
                                jiantou="↓";
                                }
                if(alldirs["southup"]!="          "){
                        map_room2=alldirs["southup"];
                        jiantou="↑";
                        }
                if(alldirs["south"]!="          "){
                        map_room2=alldirs["south"];
                        jiantou="｜";
                        }
                map_room=map_room2;
                for(i=0;i<(10-strlen(map_room2))/2;i++)
                        {
                                map_room =map_room + " ";
                                map_room =" "+map_room;
                        }
                printf("                        %s   %s   %s\n",
                alldirs["southwest"]=="          " ? "  ":"／",
                jiantou,
                alldirs["southeast"]=="          " ? "  ":"＼");
                printf("             %10s  %-10s  %-10s\n",
                alldirs["southwest"],map_room,alldirs["southeast"]);
                
                        
        }       
        else
        {
                map_room2=env->query("short") ? env->query("short"): "----------";
                map_room=HIG+map_room2+NOR;
                for(i=0;i<(10-strlen(map_room2))/2;i++)
                        {
                                if(alldirs["east"]=="          ")
                                map_room =map_room + " ";
                                else map_room=map_room + "-";
                                if(alldirs["west"]=="          ")
                                map_room =" "+ map_room;
                                else map_room ="-"+map_room;
                        }
                printf("\n                            %s\n",map_room);
                
        }
        return;
}

// Tomud头像
string look_icon(object me, object ob)
{
	mixed tmp;
	string icon;

	if ( !objectp(ob) )
		return "";
	if ( me->query("xieyi/zmud") )
		return "";
	
	if ( tmp = ob->query("icon") )
	{
		if ( intp(tmp) )
			icon = sprintf("%d", tmp);
		else if ( stringp(tmp) )
			icon = tmp;
		else 
		{
			if ( living(ob) || ob->is_character() ) icon = "00901";
			else icon = "00961";
		}
	}
	else
	{
		if ( userp(ob) ) icon = (ob->query("gender") == "男性")?"1174":"1173";	
		else if ( living(ob) || ob->is_character() ) icon = "00901";
		else icon = "00961";
	}
	
	while ( strlen(icon) < 5 )
	{
		icon = "0" + icon;
	}
	
	return L_ICON(icon);
}

int look_room(object me, object env)
{
	int i, j, k, l, x, y, show_lvl;
	object *inv;
	mapping exits, *data;
	string str, *dirs, desc;
	mapping buffo = ([]), buffobj = ([]);
	string bfile, place_name;
    string short, short_xy, long, exit, msg;

    k = 0;
	data = allocate(3000);
	show_lvl = to_int(me->query("env/brief"));
	
	if( me->query("position") == "webuser" )
	{
		if( !env ) 
		{
			write("你的四周灰蒙蒙地一片，什么也没有。\n");
			return 1;
		}
		
		short = sprintf(WEBBLK "【" WEBNOR WEBRED " %s"  WEBNOR WEBBLK "】" + WEBNOR, env->query("short"));
		short += wizardp(me)? file_name(env): "";
		desc = env->query("long");
		long = desc + "<br>　　" + WEBYEL + implode(explode((env->query("outdoors")?"":"窗外：") + NATURE_D->outdoor_room_description(), "\n"), "")  + WEBNOR;
		exit = "";
		
		if( mapp(exits = env->query("exits")) )
		{
			dirs = keys(exits);
			for(i=0; i<sizeof(dirs); i++)
			{
				if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
					dirs[i] = 0;
			}
			
			dirs -= ({ 0 });
			
			if( sizeof(dirs)==0 )
				exit = "    这里没有任何明显的出路。";
			else if( sizeof(dirs)==1)
				exit = "    这里唯一的出口是 <a target=nothing href=\\\"/Command/go "  + dirs[0] + "\\\"" + WEBRED + dirs[0]  + "</a>" + WEBNOR + "。";
			else
			{
				exit = "    这里明显的出口是 ";
				for (i = 0; i < sizeof(dirs) - 2; i++)
				{
					exit += sprintf("<a target=nothing href=\\\"/Command/go %s\\\">%s</a>、", dirs[i], dirs[i]);
				}
				
				exit += sprintf("<a target=nothing href=\\\"/Command/go %s\\\">%s</a>和", dirs[sizeof(dirs) - 2], dirs[sizeof(dirs) - 2]);
				exit += sprintf("<a target=nothing href=\\\"/Command/go %s\\\">%s</a>", dirs[sizeof(dirs) - 1], dirs[sizeof(dirs) - 1]);
			}
		}
		
		inv = all_inventory(env);
		str = "";
		for(i=0; i<sizeof(inv); i++)
		{
			if( inv[i]==me ) continue;
			if( inv[i]->query("no_shown")) continue;
			if( !me->visible(inv[i]) ) continue;
			
			bfile=base_name(inv[i]);
			
			if ( member_array(bfile,keys(buffo)) == -1 )
			{
				buffo[bfile]=1;
				buffobj[bfile]=inv[i];
				str += sprintf("<a target=nothing href=\\\"/Command/look %s\\\">%s</a><br><br>",inv[i]->query("id"), inv[i]->short());
			}
			else
			{
				buffo[bfile] ++;
				str += sprintf("<a target=nothing href=\\\"/Command/look %s %d\\\">%s</a><br><br>",inv[i]->query("id"), buffo[bfile], inv[i]->short());
			}
		}
		
		printf(JSP "parent.show_inv(\"%s\")" NSP, str);
		printf(JSP "parent.look_room(\"%s\", \"%s\", \"%s\")" NSP, short, long, exit);
		
		return 1;
	}
	else
	{
		if ( !me->query("xieyi/zmud") )
		{
			msg = "";

			if ( me->is_fighting() || me->query("env/map_xy_msg") || me->query("env/map_xy_msg") > 0 )
			{
				if ( me->query("xysys_map_xy/x") > 1 )
					msg += "west;";
			
				if ( me->query("xysys_map_xy/x") < 6 )
					msg += "east;";

				if ( me->query("xysys_map_xy/y") > 1 )
					msg += "north;";

				if ( me->query("xysys_map_xy/y") < 6 )
					msg += "south;";

				if ( me->query("xysys_map_xy/x") > 1 && me->query("xysys_map_xy/y") > 1 )
					msg +="northwest;";

				if ( me->query("xysys_map_xy/x") > 1 && me->query("xysys_map_xy/y") < 6 )
					msg +="southwest;";

				if ( me->query("xysys_map_xy/x") < 6 && me->query("xysys_map_xy/y") > 1 )
					msg +="northeast;";

				if ( me->query("xysys_map_xy/x") < 6 && me->query("xysys_map_xy/y") < 6 )
					msg +="southeast;";
			}
		}

		if( !env )
		{
			write("你的四周灰蒙蒙地一片，什麽也没有。\n");
			return 1;
		}
		
		if ( virtualp(env) && sscanf(base_name(env), "/adm/daemons/vrm_server/%s/%d/%d", place_name, x, y)==3 ) 
		{
			short_xy = HIY"[坐标：Ｘ="HIG+x+HIY"，Ｙ="HIC+y+HIY"]";
		}
		else
			short_xy = "";
		
		if ( env->query("outdoors") )
		{
			if ( wizardp(me) && !me->query("env/show_room") )
				str = sprintf( HIR +"「"+HIG"%s"+HIR"」%s"NOR + " - %s\n    %s%s", env->query("short"), short_xy, SECURITY_D->valid_read(file_name(env),me)? file_name(env): "", show_lvl>3?"":env->query("long"), (env->query("outdoors")&&show_lvl<4)? NATURE_D->outdoor_room_description() : "" );
			else
				str = sprintf( HIR +"「"+HIG"%s"+HIR"」%s"NOR + "\n    %s%s", env->query("short"), short_xy, show_lvl>3?"":env->query("long"), (env->query("outdoors")&&show_lvl<4)? NATURE_D->outdoor_room_description() : "" );
		}
		else
		{
			if (wizardp(me) && !me->query("env/show_room"))
				str = sprintf( HIC +"「"+NOR HIR"%s"+HIC"」%s"NOR + " - %s\n    %s%s", env->query("short"), short_xy, SECURITY_D->valid_read(file_name(env),me)? file_name(env): "", show_lvl>3?"":env->query("long"), (env->query("outdoors")&&show_lvl<4)? NATURE_D->outdoor_room_description() : "" );
			else str = sprintf( HIC +"「"+HIR"%s"+HIC"」%s"NOR + "\n    %s%s", env->query("short"), short_xy, show_lvl>3?"":env->query("long"), (env->query("outdoors")&&show_lvl<4)? NATURE_D->outdoor_room_description() : "" );
		}
		
		if ( !me->query("xieyi/zmud") )
			str += CLEAN0;
		
		if( mapp(exits = env->query("exits")) )
		{
			dirs = keys(exits);
			for(i=0; i<sizeof(dirs); i++)
			{
				if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
					dirs[i] = 0;
			}
			
			dirs -= ({ 0 });
			
			if( sizeof(dirs)==0 )
			{
				str += NOR CYN"    这里没有任何明显的出路。\n";

				if(!me->query("xieyi/zmud"))
					str += ADDWAY(msg);
			}
			else if( sizeof(dirs)==1 )
			{
				if(!me->query("xieyi/zmud"))
					str +=ADDWAY(msg + dirs[0]);
				
				str += "    "+HIC"唯一的"+HIY"〖"+HIW" 出口 "NOR+HIY"〗"NOR+": " + HIR + dirs[0] + NOR + "。\n";
			}
			else
			{
				dirs = sort_array(dirs,"sort_exits");
				str += sprintf("    "+HIY"〖"+HIW" 出口 "NOR+HIY"〗"NOR+": "+ HIW + "%s" + HIY" 和 "NOR + HIW"%s" +NOR + "。\n", implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
				
				if(!me->query("xieyi/zmud"))
					str += sprintf(ADDWAY(msg + implode(dirs[0..sizeof(dirs)-1], ";")));
			}
		}
		else
		{
			str += NOR CYN"    这里没有任何明显的出路。\n"+NOR;
			
			if(!me->query("xieyi/zmud"))
				str += ADDWAY(msg);
		}
		
		inv = all_inventory(env);
		for (i = 0; i < sizeof(inv); i++)
		{
			reset_eval_cost();
			if ( inv[i]!=me 
				&& me->visible(inv[i]) 
				&& !inv[i]->query("money_id") 
				&& !inv[i]->query_temp("check_only") 
				&& !inv[i]->is_character() )
			{
				data[k]=([]);
				for(j = i; j < sizeof(inv); j++ )
				{
					if ( inv[i]->query("name")==inv[j]->query("name") 
						&& inv[i]->query("id")==inv[j]->query("id")
						&& !inv[j]->query_temp("check_only") )
					{
						data[k]["id"]=inv[i]->short();
						data[k]["unit"]=inv[i]->query("unit");
						data[k]["num"]= data[k]["num"] + 1;
						inv[j]->set_temp("check_only", 1);
					}
					else
						continue;
				}
				
				k++;
			}
			else
				continue;
		}
		
		for (i = 0; i < sizeof(inv); i++)
		{
			reset_eval_cost();
			if ( !inv[i]->query_temp("check_only") && inv[i]!=me && me->visible(inv[i]) )
				str += sprintf("%s%s\n", "  ", inv[i]->short());
			
			if (inv[i]!=me && !me->query("xieyi/zmud"))
			{
				if(!(wizardp(inv[i]) && inv[i]->query("env/invisibility") == 10))
				{
					if ( i > 50 )
					{
						if ( inv[i]->is_character() || inv[i]->query("startroom") == base_name(env) )
							str += ADD0(inv[i]);
					}
					else
						str += ADD0(inv[i]);
				}
			}
		}

		for (i = 0; i < sizeof(inv); i++)
			if ( inv[i]->query_temp("check_only") )
				inv[i]->delete_temp("check_only");

		if (k > 0)
		{
			for (l = 0; l < k; l++)
				str = sprintf("%s%s%s\n", str,  (data[l]["num"]==1)? "  ":"  "+ chinese_number(data[l]["num"])+data[l]["unit"], data[l]["id"]);
		}

		// 即时地图
		if( !me->query("temp_time_map") && show_lvl<5 )
		{
			if ( base_name(env) != "/d/migong/migong1" && base_name(env) != "/d/migong/migong2" )
				realtime_map(me, env);
		}

		if ( !me->query("xieyi/zmud") && me->query("env/myhp_show") )
			str += ROOMNAME(filter_color(env->query("short")));
		
		write(str);

		return 1;
	}
}

int look_item(object me, object obj)
{
	mapping is_bind;
    mixed *inv;
    string prep, *bind_ids;
	int i, v_num, lvl;

    if (!me->visible(obj)) { write("你要看什么？\n"); return 1; }
    if( me->query("position") == "webuser" )
	{
		//开光魔法戒指描述特殊处理
		if ( obj->query("old_copy_log") && obj->query("diablo/only_me") != me->query("id") )
			write(obj->query("old_copy_log"));
		else
			write(obj->long());

	inv = all_inventory(obj);
	if( !obj->is_closed() && sizeof(inv)) {
		switch( (string)obj->query("prep") ) {
			case "on":
				prep = "上";
				break;
			case "under":
				prep = "下";
				break;
			case "behind":
				prep = "后";
				break;
			case "inside":
				prep = "里";
				break;
			default:
				prep = "里";
				break;
                        }
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("%s面有：\n  %s\n", prep,
			implode(inv, "\n  ") ), me);
	}
	return 1;
} else {
	// Add By Wenwu
	//------------------------------------------------------
	write(HIW"【名称】："+NOR+obj->query("name")+NOR+"("+obj->query("id")+")\n");
	//------------------------------------------------------
	//开光魔法戒指描述特殊处理
	if ( obj->query("old_copy_log") && obj->query("diablo/only_me") != me->query("id") )
		write(HIY"【描述】："+NOR+obj->query("old_copy_log"));
	else
		write(HIY"【描述】："+NOR+obj->long());
	if (obj->query("item_t")){
			write("时效："+ CHINESE_D->chinese_period(obj->query("item_t")-time())+"\n");
		}
	// 属性显示
	// 兵器
	if ( obj->query("weapon_prop") )
	{
		v_num = 0;
		for (i = 0; i < sizeof(weapon_shuxing); i++)
		{
			if ( obj->query("weapon_prop/" + keys(weapon_shuxing)[i]) )
				v_num++;
		}
		write(HIM"\t属性品阶：  "+chinese_number(v_num)+"阶\n"NOR);
		write(YEL"\t优劣等级：  "+chinese_number(obj->query("weapon_prop/level"))+"级\n"NOR);

			if ( obj->query("flag") & 1 )
				write(HIY"\t使用类型："HIY"  双手\n"NOR);
			else 
				write(HIY"\t使用类型："HIY"  单手\n"NOR);

		write(HIM"\t应用类型：  "HIB+weapon_skill_type[obj->query("skill_type")]+"\n"NOR);

		// 绑定的装备别人无法装备上
		if ( mapp(is_bind=obj->query("bind_master_level")) )
		{	
			bind_ids = keys(is_bind);
			write(HIC"\t绑定类型：  "HIR"已绑定("+bind_ids[0]+")\n"NOR);
			
		} else if ( lvl = obj->query("xyzx_sys/bind_type") ) {
			if ( lvl == 1 ) 
				write(HIC"\t绑定类型：  "HIY"装备绑定\n"NOR);
			else if ( lvl == 2 ) 
				write(HIC"\t绑定类型：  "HIY"拾取绑定\n"NOR);
			else
				write(HIC"\t绑定类型：  "HIW"未知\n"NOR);
		}
		else
			write(HIC"\t绑定类型：  "HIW"不绑定\n"NOR);

		if ( obj->query("weapon_prop/damage") )
			write(HIW"\t物理攻击："HIG"+ "HIW+obj->query("weapon_prop/damage")+"\n"NOR);

		if ( obj->query("weapon_prop/strength") )
			write(HIB"\t臂力增幅："HIG"+ "HIW+obj->query("weapon_prop/strength")+"\n"NOR);

		if ( obj->query("weapon_prop/intelligence") )
			write(HIM"\t悟性增幅："HIG"+ "HIW+obj->query("weapon_prop/intelligence")+"\n"NOR);

		if ( obj->query("weapon_prop/constitution") )
			write(HIY"\t根骨增幅："HIG"+ "HIW+obj->query("weapon_prop/constitution")+"\n"NOR);

		if ( obj->query("weapon_prop/dexerity") )
			write(HIG"\t身法增幅："HIG"+ "HIW+obj->query("weapon_prop/dexerity")+"\n"NOR);

		if ( obj->query("weapon_prop/karma") )
			write(YEL"\t福缘增幅："HIG"+ "HIW+obj->query("weapon_prop/karma")+"\n"NOR);

		if ( obj->query("weapon_prop/personality") )
			write(MAG"\t容貌增幅："HIG"+ "HIW+obj->query("weapon_prop/personality")+"\n"NOR);

		if ( obj->query("weapon_prop/dodge") )
			write(HIG"\t轻功提升："HIG"+ "HIW+obj->query("weapon_prop/dodge")+"\n"NOR);

		if ( obj->query("weapon_prop/unarmed") )
			write(HIY"\t拳脚提升："HIG"+ "HIW+obj->query("weapon_prop/unarmed")+"\n"NOR);

		if ( obj->query("weapon_prop/force") )
			write(YEL"\t内功提升："HIG"+ "HIW+obj->query("weapon_prop/force")+"\n"NOR);

		if ( obj->query("weapon_prop/parry") )
			write(HIB"\t招架提升："HIG"+ "HIW+obj->query("weapon_prop/parry")+"\n"NOR);

		if ( obj->query("weapon_prop/sword") )
			write(HIW"\t剑法提升："HIG"+ "HIW+obj->query("weapon_prop/sword")+"\n"NOR);

		if ( obj->query("weapon_prop/blade") )
			write(HIY"\t刀法提升："HIG"+ "HIW+obj->query("weapon_prop/blade")+"\n"NOR);

		if ( obj->query("weapon_prop/axe") )
			write(HIB"\t斧法提升："HIG"+ "HIW+obj->query("weapon_prop/axe")+"\n"NOR);

		if ( obj->query("weapon_prop/stick") )
			write(YEL"\t棒法提升："HIG"+ "HIW+obj->query("weapon_prop/stick")+"\n"NOR);

		if ( obj->query("weapon_prop/staff") )
			write(CYN"\t杖法提升："HIG"+ "HIW+obj->query("weapon_prop/staff")+"\n"NOR);

		if ( obj->query("weapon_prop/spear") )
			write(HIB"\t枪法提升："HIG"+ "HIW+obj->query("weapon_prop/spear")+"\n"NOR);

		if ( obj->query("weapon_prop/fork") )
			write(HIB"\t叉法提升："HIG"+ "HIW+obj->query("weapon_prop/fork")+"\n"NOR);

		if ( obj->query("weapon_prop/club") )
			write(HIB"\t棍法提升："HIG"+ "HIW+obj->query("weapon_prop/club")+"\n"NOR);

		if ( obj->query("weapon_prop/throwing") )
			write(HIR"\t暗器提升："HIG"+ "HIW+obj->query("weapon_prop/throwing")+"\n"NOR);

		if ( obj->query("weapon_prop/hammer") )
			write(GRN"\t锤法提升："HIG"+ "HIW+obj->query("weapon_prop/hammer")+"\n"NOR);

		if ( obj->query("weapon_prop/taoism") )
			write(HIM"\t道学心法："HIG"+ "HIW+obj->query("weapon_prop/taoism")+"\n"NOR);

		if ( obj->query("weapon_prop/whip") )
			write(HIG"\t鞭法提升："HIG"+ "HIW+obj->query("weapon_prop/whip")+"\n"NOR);

		if ( obj->query("weapon_prop/strike") )
			write(HIG"\t掌法提升："HIG"+ "HIW+obj->query("weapon_prop/strike")+"\n"NOR);

		if ( obj->query("weapon_prop/finger") )
			write(HIG"\t指法提升："HIG"+ "HIW+obj->query("weapon_prop/finger")+"\n"NOR);

		if ( obj->query("weapon_prop/magic") )
			write(HIM"\t法术提升："HIG"+ "HIW+obj->query("weapon_prop/magic")+"\n"NOR);

		if ( obj->query("weapon_prop/spells") )
			write(HIM"\t咒文提升："HIG"+ "HIW+obj->query("weapon_prop/spells")+"\n"NOR);

		if ( obj->query("weapon_prop/poison") )
			write(HIG"\t毒功提升："HIG"+ "HIW+obj->query("weapon_prop/poison")+"\n"NOR);

		if ( obj->query("weapon_prop/hand") )
			write(HIW"\t手法提升："HIG"+ "HIW+obj->query("weapon_prop/hand")+"\n"NOR);

		if ( obj->query("weapon_prop/cuff") )
			write(HIY"\t拳法提升："HIG"+ "HIW+obj->query("weapon_prop/cuff")+"\n"NOR);

		if ( obj->query("weapon_prop/claw") )
			write(HIW"\t爪法提升："HIG"+ "HIW+obj->query("weapon_prop/claw")+"\n"NOR);
	}
	else if ( obj->query("armor_prop") ) // 防具
	{
		v_num = 0;
		for (i = 0; i < sizeof(armor_shuxing); i++)
		{
			if ( obj->query("armor_prop/" + keys(armor_shuxing)[i]) )
				v_num++;
		}
		write(HIM"\t属性品阶：  "+chinese_number(v_num)+"阶\n"NOR);
		write(YEL"\t优劣等级：  "+chinese_number(obj->query("armor_prop/level"))+"级\n"NOR);

		if ( obj->query("armor_type") )
			write(HIY"\t使用类型：  "HIY+armor_type[obj->query("armor_type")]+"\n"NOR);

		if ( obj->query("female_only") )
			write(HIC"\t使用类别：  "HIM"女性\n"NOR);
		else
			write(HIC"\t使用类别：  "HIG"通用\n"NOR);

		// 绑定的装备别人无法装备上
		if ( mapp(is_bind=obj->query("bind_master_level")) )
		{
			bind_ids = keys(is_bind);
			write(HIC"\t绑定类型：  "HIR"已绑定("+bind_ids[0]+")\n"NOR);
			
		} else if ( lvl = obj->query("xyzx_sys/bind_type") ) {
			if ( lvl == 1 ) 
				write(HIC"\t绑定类型：  "HIY"装备绑定\n"NOR);
			else if ( lvl == 2 ) 
				write(HIC"\t绑定类型：  "HIY"拾取绑定\n"NOR);
			else
				write(HIC"\t绑定类型：  "HIW"未知\n"NOR);
		}
		else
			write(HIC"\t绑定类型：  "HIW"不绑定\n"NOR);

		if ( obj->query("armor_prop/armor") )
			write(HIW"\t物理防御："HIG"+ "HIW+obj->query("armor_prop/armor")+"\n"NOR);

		if ( obj->query("armor_prop/strength") )
			write(HIB"\t臂力增幅："HIG"+ "HIW+obj->query("armor_prop/strength")+"\n"NOR);

		if ( obj->query("armor_prop/intelligence") )
			write(HIM"\t悟性增幅："HIG"+ "HIW+obj->query("armor_prop/intelligence")+"\n"NOR);

		if ( obj->query("armor_prop/constitution") )
			write(HIY"\t根骨增幅："HIG"+ "HIW+obj->query("armor_prop/constitution")+"\n"NOR);

		if ( obj->query("armor_prop/dexerity") )
			write(HIG"\t身法增幅："HIG"+ "HIW+obj->query("armor_prop/dexerity")+"\n"NOR);

		if ( obj->query("armor_prop/karma") )
			write(YEL"\t福缘增幅："HIG"+ "HIW+obj->query("armor_prop/karma")+"\n"NOR);

		if ( obj->query("armor_prop/personality") )
			write(MAG"\t容貌增幅："HIG"+ "HIW+obj->query("armor_prop/personality")+"\n"NOR);

		if ( obj->query("armor_prop/armor_vs_force") )
			write(HIY"\t真气护体："HIG"+ "NOR+YEL+obj->query("armor_prop/armor_vs_force")+"\n"NOR);

		if ( obj->query("armor_prop/dodge") )
			write(HIG"\t轻功提升："HIG"+ "HIW+obj->query("armor_prop/dodge")+"\n"NOR);

		if ( obj->query("armor_prop/unarmed") )
			write(HIY"\t拳脚提升："HIG"+ "HIW+obj->query("armor_prop/unarmed")+"\n"NOR);

		if ( obj->query("armor_prop/force") )
			write(YEL"\t内功提升："HIG"+ "HIW+obj->query("armor_prop/force")+"\n"NOR);

		if ( obj->query("armor_prop/parry") )
			write(HIB"\t招架提升："HIG"+ "HIW+obj->query("armor_prop/parry")+"\n"NOR);

		if ( obj->query("armor_prop/sword") )
			write(HIW"\t剑法提升："HIG"+ "HIW+obj->query("armor_prop/sword")+"\n"NOR);

		if ( obj->query("armor_prop/blade") )
			write(HIY"\t刀法提升："HIG"+ "HIW+obj->query("armor_prop/blade")+"\n"NOR);

		if ( obj->query("armor_prop/axe") )
			write(HIB"\t斧法提升："HIG"+ "HIW+obj->query("armor_prop/axe")+"\n"NOR);

		if ( obj->query("armor_prop/stick") )
			write(YEL"\t棒法提升："HIG"+ "HIW+obj->query("armor_prop/stick")+"\n"NOR);

		if ( obj->query("armor_prop/staff") )
			write(CYN"\t杖法提升："HIG"+ "HIW+obj->query("armor_prop/staff")+"\n"NOR);

		if ( obj->query("armor_prop/spear") )
			write(HIB"\t枪法提升："HIG"+ "HIW+obj->query("armor_prop/spear")+"\n"NOR);

		if ( obj->query("armor_prop/fork") )
			write(HIB"\t叉法提升："HIG"+ "HIW+obj->query("armor_prop/fork")+"\n"NOR);

		if ( obj->query("armor_prop/club") )
			write(HIB"\t棍法提升："HIG"+ "HIW+obj->query("armor_prop/club")+"\n"NOR);

		if ( obj->query("armor_prop/throwing") )
			write(HIR"\t暗器提升："HIG"+ "HIW+obj->query("armor_prop/throwing")+"\n"NOR);

		if ( obj->query("armor_prop/hammer") )
			write(GRN"\t锤法提升："HIG"+ "HIW+obj->query("armor_prop/hammer")+"\n"NOR);

		if ( obj->query("armor_prop/taoism") )
			write(HIM"\t道学心法："HIG"+ "HIW+obj->query("armor_prop/taoism")+"\n"NOR);

		if ( obj->query("armor_prop/whip") )
			write(HIG"\t鞭法提升："HIG"+ "HIW+obj->query("armor_prop/whip")+"\n"NOR);

		if ( obj->query("armor_prop/strike") )
			write(HIG"\t掌法提升："HIG"+ "HIW+obj->query("armor_prop/strike")+"\n"NOR);

		if ( obj->query("armor_prop/finger") )
			write(HIG"\t指法提升："HIG"+ "HIW+obj->query("armor_prop/finger")+"\n"NOR);

		if ( obj->query("armor_prop/magic") )
			write(HIM"\t法术提升："HIG"+ "HIW+obj->query("armor_prop/magic")+"\n"NOR);

		if ( obj->query("armor_prop/spells") )
			write(HIM"\t咒文提升："HIG"+ "HIW+obj->query("armor_prop/spells")+"\n"NOR);

		if ( obj->query("armor_prop/poison") )
			write(HIG"\t毒功提升："HIG"+ "HIW+obj->query("armor_prop/poison")+"\n"NOR);

		if ( obj->query("armor_prop/hand") )
			write(HIW"\t手法提升："HIG"+ "HIW+obj->query("armor_prop/hand")+"\n"NOR);

		if ( obj->query("armor_prop/cuff") )
			write(HIY"\t拳法提升："HIG"+ "HIW+obj->query("armor_prop/cuff")+"\n"NOR);

		if ( obj->query("armor_prop/claw") )
			write(HIW"\t爪法提升："HIG"+ "HIW+obj->query("armor_prop/claw")+"\n"NOR);
	} else {
		// 绑定的装备别人无法装备上
		if ( mapp(is_bind=obj->query("bind_master_level")) )
		{
			bind_ids = keys(is_bind);
			write(HIC"\t绑定类型：  "HIR"已绑定("+bind_ids[0]+")\n"NOR);
			
		} else if ( lvl = obj->query("xyzx_sys/bind_type") ) {
			if ( lvl == 1 ) 
				write(HIC"\t绑定类型：  "HIY"装备绑定\n"NOR);
			else if ( lvl == 2 ) 
				write(HIC"\t绑定类型：  "HIY"拾取绑定\n"NOR);
			else
				write(HIC"\t绑定类型：  "HIW"未知\n"NOR);
		}
	}

    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        inv = map_array(inv, "inventory_look", this_object() );
        message("vision", sprintf("里面有：\n  %s\n",
            implode(inv, "\n  ") ), me);
    }
    return 1;
             }
}
int look_living(object me, object obj)
{
    int per_temp,i,j;
    string pro,*skills_name, str;
    mixed *inv;
    mapping my_fam, fam,skills;

	int my_lvl, your_lvl;
	string color ;

    if( me!=obj ){
    	if((int)me->query("shen") < 0)
        message("vision", me->name() + "正眯着一双贼眼，不怀好意的盯着你看。\n"NOR, obj);
        else if((int)me->query("shen") > 5000) 
        message("vision", me->name() + "正眯着双眼，笑眯眯的看着你。\n"NOR, obj);
        else if(random(10)>5) message("vision", me->name() + "正盯着你看,不知道有什么企图\n"NOR, obj);
        else message("vision", me->name() + "正盯着你看,不知道在打些什么主意！\n"NOR, obj);
                  }
    if (!objectp(present("fire", me))  && environment(me)->query("outdoors") && NATURE_D->outdoor_room() && !wizardp(me) ){
    str = sprintf( HIC"\n    你看到前面似乎有个人影，可天太黑了，看不清。\n"NOR);
        write(str);
        return 1;
    }
    str = look_icon(me, obj) + obj->long();
    pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));
	
    if( (string)obj->query("race")=="人类" &&  intp(obj->query("age")) )
        str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10));
	
    per_temp= (obj->query_per()>=30)?20:(obj->query_per()-10);
    if (per_temp<0) per_temp=0;
    if ( (string)obj->query("race")=="人类" ) {
    if ( (string)obj->query("gender") == "女性")
        str += sprintf("%s长的%s。\n", pro, look_level_girl[per_temp]);
    else
        str += sprintf("%s长的%s。\n", pro, look_level_boy[per_temp]);
	
	// 显示等级
	my_lvl = me->query("xyzx_sys/level");
	your_lvl = obj->query("xyzx_sys/level");
	color = NOR;
	if ( your_lvl-my_lvl < -5 ) color = WHT;
	else if ( your_lvl-my_lvl == 0 ) color = HIW;
	else if ( your_lvl-my_lvl < 5 ) color = HIG;
	else if ( your_lvl-my_lvl < 30 ) color = HIY;
	else if ( your_lvl-my_lvl < 100 ) color = HIR;
	else color = HIM;
	if ( your_lvl-my_lvl > 100 || (playerp(obj) && wizardp(me) && obj!=me) )
		str += sprintf("%s看起来似乎已修炼到了"+color+" %s级"NOR"\n", pro, "？？？");
	else
		str += sprintf("%s看起来似乎已修炼到了"+color+"%s级"NOR"\n", pro, chinese_number(your_lvl));

    skills=obj->query_skills();
    if (!sizeof(skills))
        str+=sprintf("%s看起来似乎不会任何武功。\n", pro);
    else{
        skills_name=sort_array( keys(skills), (: strcmp :) );
        i=random(sizeof(skills_name));
                if (SKILL_D(skills_name[i])->type()=="knowledge")
            str+=sprintf("%s看起来似乎不会任何武功。\n", pro);
        else
            str+=sprintf("%s的武功看起来似乎%s。\n", pro,"/cmds/usr/skills"->skill_level(SKILL_D(skills_name[i])->type(), skills[skills_name[i]]));
    }
    }
    // If we both has family, check if we have any relations.
if(obj!=me && obj->query("id")==me->query("couple/couple_id")){	
if(me->query("gender")=="女性") str+=pro+"是你的老公。\n";	
else if (me->query("gender")=="男性") str+=pro+"是你的老婆。\n";	
}
    if( obj!=me
    &&  mapp(fam = obj->query("family"))
    &&  mapp(my_fam = me->query("family")) 
    &&  fam["family_name"] == my_fam["family_name"] ) {
    
        if( fam["generation"]==my_fam["generation"] ) {
            if( (string)obj->query("gender") == "男性" )
                str += sprintf( pro + "是你的%s%s。\n",
                    my_fam["master_id"] == fam["master_id"] ? "": "同门",
                    my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
            else
                str += sprintf( pro + "是你的%s%s。\n",
                    my_fam["master_id"] == fam["master_id"] ? "": "同门",
                    my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
        } else if( fam["generation"] < my_fam["generation"] ) {
            if( my_fam["master_id"] == obj->query("id") )
                str += pro + "是你的师父。\n";
            else if( my_fam["generation"] - fam["generation"] > 1 )
                str += pro + "是你的同门长辈。\n";
            else if( fam["enter_time"] < my_fam["enter_time"] )
                str += pro + "是你的师伯。\n";
            else
                str += pro + "是你的师叔。\n";
        } else {
            if( fam["generation"] - my_fam["generation"] > 1 )
                str += pro + "是你的同门晚辈。\n";
            else if( fam["master_id"] == me->query("id") )
                str += pro + "是你的弟子。\n";
            else
                str += pro + "是你的师侄。\n";
        }
    }
    if( obj->query("max_qi") )
        str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_qi") * 100 / (int)obj->query("max_qi")) + "\n";
    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
        inv -= ({ 0 });
        if( sizeof(inv) )
            str += sprintf( obj->is_corpse() ? "%s的遗体上有:\n%s\n" : "%s%s\n",
                            pro, implode(inv, "\n") );
        if (!obj->query_temp("armor/cloth") && obj->query("race")=="人类" )
            str+=pro+"光着"+YEL+"身子"+NOR+"，什么也没穿！\n";
    }   else    str += sprintf( obj->is_corpse() ? "%s的遗体上什么也没有。\n" : (obj->query("race")=="人类"?"%s光着"+YEL+"身子"+NOR+"，什么也没穿！\n":"它的身上没有任何东西。\n"),pro);
if( me->query("position") == "webuser" ) {
printf(JSP "parent.look_living(\"%s\", \"%s\")" NSP, str,obj->query("id"));
} else {
    if (strlen(str)>8192)
    me->start_more(str);
    else     message("vision", str, me);
}
    if( obj!=me && living(obj)){
        i=obj->query("shen");
        j=me->query("shen");
        if ((i<-5000 && j>5000 ) || (i>5000 && j<-5000 ) ){
            write( obj->name() + "突然转过头来瞪你一眼。\n");
            COMBAT_D->auto_fight(obj, me, "berserk");
        }
    }
    return 1;
}
string inventory_look(object obj, int flag)
{
    string str;
     if( !flag )
        return "      "+obj->short();
    if( obj->query("equipped") ){
            switch( obj->query("armor_type") ) {
                case "cloth":
                case "armor":   str = "身穿";
				break;
                case "boots":   str = "脚蹬";
				break;
                case "head":    str = "头戴";
				break;
                case "neck":    str = "颈围";
				break;
                case "wrists":  str = "腕戴";
				break;
                case "finger":  str = "指戴";
				break;
                case "hands":   str = "手穿";
				break;
                case "waist":   str = "腰缠";
				break;
				case "surcoat":   str = "肩披";
				break;
				case "pants":   str = "腿穿";
				break;
                default:    
				if ( environment(obj)->query_temp("weapon")==obj ) 
					str = "右手执";
                 else 
					str = "左手执";
            }
    str += "一" + obj->query("unit")+obj->query("name")+"。";
    }
    return str;
}
int look_room_item(object me, string arg)
{
    object env;
    mapping item, exits;
    if( !objectp(env = environment(me)) )
        return notify_fail("这里只有灰蒙蒙地一片，什麽也没有。\n");
    if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
        if( stringp(item[arg]) )
            write(item[arg]);
        else if( functionp(item[arg]) )
            write((string)(*item[arg])(me));
            
        return 1;
    }
    if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
        if( objectp(env = find_object(exits[arg])) )
        {
            look_room(me, env);
            tell_room(env,"有人探头探脑地向这边张望了几眼。\n");
         }
        else {
            call_other(exits[arg], "???");
            look_room(me, find_object(exits[arg]));
        }
        return 1;
    }
    return notify_fail("你要看什麽？\n");
}
int help (object me)
{
    write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
    return 1;
}
