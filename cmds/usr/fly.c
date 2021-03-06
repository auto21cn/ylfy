//write file by lisa on 2003.6.27
//update end 
#include <liebiao.h>
inherit F_CLEAN_UP;

int help (object me) ;
mapping places=([	
"bt" : "/d/baituo/dating.c",
"hm" : "/d/heimuya/road1.c",
"bj" : "/d/city2/wenmiao.c",
"tl" : "/d/tianlongsi/damen.c",
"yz" : "/d/city/kedian.c",
"lj" : "/d/lingjiu/damen.c",
"sl" : "/d/shaolin/guangchang1.c",
"wd" : "/d/wudang/sanqingdian.c",
"xy" : "/d/xiaoyao/qingcaop.c",
"xx" : "/d/xingxiu/xxh2.c",
"hhh": "/d/honghua/damen.c",	
"hs" : "/d/huashan/square.c",
"ssl": "/d/shashou/enterance.c",	
"lx" : "/d/lingxiao/shanya.c",	
"xs" : "/d/xueshan/dadian.c",
"kl" : "/d/gaochang/room63.c",
"ny" : "/d/nanyang/nanyang.c",
"tm" : "/d/tangmen/damen.c",	
"tz" : "/d/tiezhang/shanmen.c",	
"qc" : "/d/qingcheng/jianfugong.c",	
"qz" : "/d/quanzhou/zhongxin.c",
"cd" : "/d/city3/guangchang.c",
"hh" : "/d/huanhua/podi.c",	
"ca" : "/d/changan/ca.c",
"dl" : "/d/dali/guangchang.c",
"wu" : "/d/wudujiao/damen.c",
"em" : "/d/emei/guangchang.c",
"mj" : "/d/mingjiao/guangchang1.c",
"gm" : "/d/gumu/rukou.c",
"hsc": "/d/village/sexit.c",
"qzj": "/d/quanzhen/guangchang.c",
"ss" : "/d/songshan/chanyuan.c",
"ts" : "/d/taishan/daizong.c",
"th" : "/d/taohua/haitan.c",
"mz" : "/d/meizhuang/gate.c", 	
"jq" : "/d/jqg/wx.c",   
"sc" : "/d/xiangyang/guangchang.c",
"mw" : "/d/migong/migong1.c",
"bya": "/d/hainan/baiyunan",
"xt" : "/d/xuantian/dongxue",
"shs": "/d/shushan/shanmen",
"tc" : "/d/tongchi/damen",
"xh" : "/d/xuehepai/gate",
"dwm": "/d/wudie/jm",
"cx" : "/d/cxwxm/damen",
"ftyjl" : "/d/feitian/guangchang",
"mf" : VRM_SERVER + "/hades/entry"
]);

int main(object me,string arg)
{
	object room, ob, *obj, env;
	int i;
	if ( !arg )
        {
          return help(me);
        }
	if ( !objectp(env=environment(me)) ) 
		return notify_fail("你四周灰蒙蒙的一片，看不见任何东西。\n");	
	if ( !stringp(places[arg] ) && arg != "home") 
		return notify_fail("你要去哪里？\n");	
	if ( me->is_busy() ) 
		return notify_fail("你上一个动作还没有完成,无法穿越时空之门！\n");	
	if ( me->is_fighting() ) 
		return notify_fail("战斗中无法穿越时空之门！\n");		
	if ( me->is_ghost() ) 
		return notify_fail("鬼魂到处乱飞,会吓着人的！\n");	
	if ( !me->query("xy_huiyuan")) 
		return notify_fail("你要去哪里？\n");	
	if ( !me->query("xy_huiyuan") && arg == "home" ) 
		return notify_fail("你要去哪里？\n");
	if ( !wizardp(me) && env->query("no_fly") ) 
		return notify_fail("这里无法使用 fly 进行传送！\n");
	if ( me->query_temp("gamble") ) 
		return notify_fail("你还是先下完这把再走吧!\n");	
	if ( file_size("d/" + "party/" + me->query("party/id") + "/dating.c") <= 0 && arg == "home" ) 
		return notify_fail("你还没有加入任何帮派。\n");	
	//if ( me->query("combat_exp")>50000000 && arg == "new" ) 
	//	return notify_fail("你在江湖中已德高望重，不用再去新手练功场了。\n");
	//if (present("biao yin",me)) 
		//return notify_fail("你身上带着镖银，无法穿越时空之门！\n");
	//if ( !wizardp(me) && virtualp(env) ) 
		//return notify_fail("你目前正在副本里，你只能从副本出口走出去！\n");
	if ( me->query_condition("killer") ) 
		return notify_fail("通缉犯也想使用时空之门？\n");
	
	obj=deep_inventory(me);
	for ( i=0; i<sizeof(obj); i++ )
	{
		if ( obj[i]->id("illicit salt") ) return notify_fail("你身上带着私盐，无法穿越时空之门！\n");
		if ( obj[i]->is_character() && !obj[i]->is_corpse() && arg == "new" )
			return notify_fail(obj[i]->name()+"不能和你一起穿越时空之门！\n");
	}	
	ob=first_inventory(me);
	while ( ob )
	{
		if ( ob->is_character() && !ob->is_corpse() ) return notify_fail(ob->name()+"不能和你一起穿越时空之门！\n");
		ob=next_inventory(ob);
	}
	
	message_vision(YEL+"只见一阵烟雾过後，$N的身影已经不见了。\n"+NOR, me);
	
	if ( arg=="home" )
	{
		if ( arg=="home" ) me->move("d/" + "party/" + me->query("party/id") + "/dating.c");
		
	}
	else
	{
		if ( !room=find_object(places[arg]) ) room=load_object(places[arg]);
		
		me->move(room);
	}
	
	message_vision(YEL+"$N的身影突然出现在一阵烟雾之中。\n"+NOR, me);
	
	me->receive_damage("jing", 10);
	me->delete_temp("pended");
	return 1;
}

int help (object me)
{
write(@HELP
指令格式: fly <地点>: 这个指令能让你直接到达一些常用的地方：
------------------------------------------------------------------
  yz  : 扬州       hsc : 华山村      dl  : 大理       bj  : 北京
  hm  : 黑木崖     ca  : 长安        hs  : 华山       ny  : 南阳
  lj  : 灵鹫宫     sl  : 少林寺      wd  : 武当山     qz  : 泉州
  xy  : 逍遥派     xx  : 星宿海      xs  : 雪山寺     kl  : 昆仑
  wu  : 五毒教     tl  : 天龙寺      tz  : 铁掌帮     em  : 峨嵋
  cd  : 成都       bt  : 白驼山      new : 练功场     gm  : 古墓 
  dwm : 蝶舞门     mj  : 明教        th  : 桃花岛     ss  : 嵩山
  jq  : 绝情谷     ts  : 泰山        ssl : 杀手楼     tm  : 唐门
  lx  : 凌霄城     qc  : 青城派      hhh : 红花会     mz  : 梅庄        
  qzj : 全真教     bya : 白云庵      tc  : 通吃帮     mf  : 冥府
  xt  : 玄天派     mw  : 迷雾森林    xh  : 血河派     shs : 蜀山
  hh  : 浣花剑派   cx  : 痴心妄想门  home: 帮会大厅   sc  : 襄阳
  ftyjl : 飞天御剑流     
------------------------------------------------------------------
HELP);
return 1;
}
