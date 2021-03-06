// /adman/daemons/logind.c
// 2003.7.24 lisa
// 禁止恶意代码的载入 2004.7.29
// 增加用户协议的端口识别 2004.8.7
// 采用Mysql验证网间各站点同ID，Mysql网间数据漫游
// 增加WIZ登陆二级密码 2004.8.20
// 增加web转码
// 完善tomud协议的login部分(更新行囊、人物、who列表)
// 2.0 增加人物身份标识
// 由原来的MD5系统转换成常规，增加两个密码参数识别原玩家密码
// 增加对客户端版本识别，Tomud进入端口默认：5555 9999，WEB进入端口为2001，其他为：2003 8888
// 改用常用ASCII码对照表验证Tomud客户端版本
//2015.10.10删除一些和本游戏无关的一些设置

#define ZMUD_1 get_system_config(DATA_CONFIG_DIR "system.h", "WEB")
#define ZMUD_2 get_system_config(DATA_CONFIG_DIR "system.h", "ZMUD_1")
#define ZMUD_3 get_system_config(DATA_CONFIG_DIR "system.h", "ZMUD_2")
#define TOMUD_1 get_system_config(DATA_CONFIG_DIR "system.h", "TOMUD_1")
#define TOMUD_2 get_system_config(DATA_CONFIG_DIR "system.h", "TOMUD_2")
#define XYZX_PORT_MSG ""+ZMUD_2+"|"+ZMUD_3+"|"+TOMUD_1+"|"+TOMUD_2
#define MAX_USERS_PER_IP 8

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <liebiao.h>
#include <mudlib.h>
#include <net/daemons.h>

inherit F_DBASE;
inherit F_ASCII;

int lock_age = LOCK_AGE;
int wiz_lock_level = WIZ_LOCK_LEVEL;
int mad_lock = 0;

string Rname;

string *banned_name = ({
	"你", "你的", "我","我的","自己","屁", "他", "他的","她", "她的","它", "它的",
	"鬼王","风云","流氓","爸","新闻发布使"," ","　","妈","祖先","祖宗","爷","奶",
	"毛泽东","邓小平","江泽民","【","】","马克思","恩格斯","列宁","抄","手淫","老百姓",
	});

string *start_room = ({
	"/d/city3/kedian",
	"/d/city2/kedian",
	"/d/dali/kezhan",
	"/d/nanyang/kedian1",
	});

string *banned_id = ({
	"mudos","admin","arch","wizard","manager","president","apprentice","immortal",
	"player","genie","fuck","manager","ceo","boss","root","book","staff","sword",
	"noname","blade","silver","coin","look","gold","angel","newer","out","talk",
	"none","corpse","Skeleton","club","hammer",
		});

protected void get_version(string arg, object ob,int ip_cnt);//客户端版本识别
protected void get_id(string arg, object ob,int ip_cnt);
protected void confirm_id(string yn, object ob,int ip_cnt);
object make_body(object ob);
protected void init_new_player(object user);
void get_resp(string arg, object ob);
protected void new_biaoshi(string biaoshi,object ob); // 设定标识
protected void confirm_biaoshi(string biaoshi,object ob); //检查标识
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string random_name();

void random_gift(mapping my, int select)
{
	int i = 10, j;
	int tmpstr, tmpint, tmpcon, tmpdex;

	tmpstr = tmpint = tmpcon = tmpdex = 10;

	switch (select)
	{
		case 1: tmpstr = i = my["str"]; break;
		case 2: tmpint = i = my["int"]; break;
		case 3: tmpcon = i = my["con"]; break;
		case 4: tmpdex = i = my["dex"];
	}

	i = 50 - i;

	while (i--)
	{
		j = random(4);

		if (j == select - 1)
		{
			i++;
			continue;
		}

		switch (j)
		{
			case 0: tmpstr++; break;
			case 1: tmpint++; break;
			case 2: tmpcon++; break;
			case 3: tmpdex++; break;
		}
	}

	if (tmpstr <= 30) my["str"] = tmpstr; else my["str"] = 30;
	if (tmpint <= 30) my["int"] = tmpint; else my["int"] = 30;
	if (tmpcon <= 30) my["con"] = tmpcon; else my["con"] = 30;
	if (tmpdex <= 30) my["dex"] = tmpdex; else my["dex"] = 30;

	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);
}

void create() 
{
    seteuid(getuid());
    set("channel_id", "连线精灵");
}

protected void logfile(string str)
{
    mixed *local =localtime(time());

    string file=sprintf("login/login%d%d.log",local[5],local[4]+1);
    log_file(file,str);
}

void logon(object ob) 
{
	object *usr;
	int i, wiz_cnt, ppl_cnt,ip_cnt,ban_cnt,login_cnt,i_user,online_num,a_port,b_port,c_port,d_port;
	string str, user_num, Rasc;
	/*if (uptime() < 60)
	{
	        write(RED"游戏正在启动过程中，请稍候再login。\n"NOR);
	        destruct(ob);
	        return;
	}*/
	str=query_ip_number(ob);

	Rasc = random_all_char();
	write(TMI("connect " + Rasc) + "\n");
	ob->set_temp("tomud_version", Rasc);
	
	if (BAN_D->is_banned(str) == 1)
	{
		write(HIW"    ◇◆◇◆◇ "HIR"你的地址在本"HIG" MUD "HIR"不受欢迎，如有疑问至"HIW" ◇◆◇◆◇"HIY"\n               http://lovexyzx.getbbs.com\n"HIW"               ————————"HIC"申述"HIW"————————\n"NOR);
		destruct(ob);
		return;
	}
	
	if( mad_lock == 1 )
	{
		write(HBRED+HIY"档案处理中.....，时空已被封闭，请稍候再行连线！！！ \n"NOR);
		destruct(ob);
		return;
	}

	if ( !DNS_MASTER->query_doing_end() )
	{
		write(HBRED+HIY+CHINESE_MUD_NAME + "正与主站同步中。。。，请稍候再行连线！！！ \n"NOR);
		destruct(ob);
		return;
	}
	
	write("\n");
	write(NOR"欢迎光临 "+BBLU+HIM+get_system_config(DATA_CONFIG_DIR "system.h", "XYZX_NAME_1")+BBLU+HIW" 之 "+BBLU+HIR+get_system_config(DATA_CONFIG_DIR "system.h", "XYZX_NAME_2")+NOR);
	write("\n\n");
	write(CYN"夕阳再现"HIW"论坛"NOR" : " + get_system_config(DATA_CONFIG_DIR "system.h", "XYZX_BBS") + "\n"NOR);
	write(CYN"「驱动版本」"NOR" : " HIW +  __VERSION__ + "\n"NOR);
	//if ( !"/cmds/bos/mudlist-login"->main() )
	write("\n");
	
	usr = get_all_user();
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	ban_cnt = 0;
	ip_cnt=0;
	a_port=0;
	b_port=0;
	c_port=0;
	d_port=0;
	
	for(i=0; i<sizeof(usr); i++)
	{
		if(query_ip_port(usr[i]) == ZMUD_2) a_port++;
		if(query_ip_port(usr[i]) == TOMUD_1) b_port++;
		if(query_ip_port(usr[i]) == ZMUD_3) c_port++;
		if(query_ip_port(usr[i]) == TOMUD_2) d_port++;
		if (str==query_ip_number(usr[i])) ip_cnt++;
		if( str==query_ip_number(usr[i]) && !environment(usr[i]) ) ban_cnt++;
		
		if( !environment(usr[i]) ) 
			login_cnt++;
		else if( wizardp(usr[i]))
		{
			if (!usr[i]->query("env/invisibility"))
				wiz_cnt++;
		}
		else
			ppl_cnt++;
	}
	
	user_num=read_file(__DIR__"users",1);
	i_user=atoi(user_num);
	i_user=i_user+1;
	user_num=sprintf("%d", i_user); 
	write_file(__DIR__"users",user_num,1);
	user_num=read_file(__DIR__"iduser",1);
	i_user=atoi(user_num);
	online_num = atoi(read_file(__DIR__"maxonline",1));
	
	if (ip_cnt-1 > 0)
	{
		printf("你现在从%s连线进入。",CYN+str+NOR);
		printf("在这个地址上，还有"+YEL+chinese_number(ip_cnt-1)+NOR+"位其他玩家。\n");
	}
	else
		printf("你现在从%s连线进入。\n",CYN+str+NOR);
	printf("目前共有"+ HIY"%s"NOR+ "位神仙、"+HIW"%s"NOR+"位江湖人士在江湖中，以及"+HIB"%s"NOR+ "位朋友正在步入途中。\n",
	chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) );
	printf(HIY"本站支持多端口连接，请选择人数较少的端口连线，以提高您的游戏速度\n"NOR);//添加多个端口
	printf(	HIW"『"+ZMUD_2+" %s人"+"』『"+ZMUD_3+" %s人"+"』『"+TOMUD_1+" %s人"+ "』『"+TOMUD_2+" %s人"+ "』\n"NOR,chinese_number(a_port),chinese_number(b_port),chinese_number(c_port),chinese_number(d_port),);
	
	if(ppl_cnt > online_num)
	{
		user_num = sprintf("%d",ppl_cnt);
		write_file(__DIR__"maxonline",user_num,1);
	}
	
	if (ban_cnt > 10 )
	{
		write(HIY"这个IP上同时正在连线的玩家太多了，请稍候再尝试！！ \n"NOR);
		destruct(ob);
		return;
	}
	//添加多个端口
	write(BRED+HIW"ZMud端口["HIY+ZMUD_2+HIW"],ZMud端口["HIY+ZMUD_3+HIW"],ToMud端口["HIG+TOMUD_1+HIW"],ToMud端口["HIG+TOMUD_2+HIW"],请选择适合的端口连接\n"NOR+YEL"请输入您的英文名字：\n"NOR);
	input_to( (: get_version :), ob,ip_cnt );
}

protected void get_id(string arg, object ob,int ip_cnt)
{
	object ppl;
	object *usr;
	int i, wiz_cnt,usr_cnt;
	arg = lower_case(arg);
    
	if( !check_legal_id(arg))
	{
		write(YEL"请输入您的英文名字：\n"NOR);
		input_to("get_id", ob,ip_cnt);
		return;
	}

	// 清空所有列表
	if ( query_ip_port(ob) == TOMUD_1 || query_ip_port(ob) == TOMUD_2 )
	{
		write(CLEAN2);
		write(CLEAN0);
		write(CLEAN1);
	}
	
	usr = users();
	wiz_cnt = 0;
	
	for(i=0; i<sizeof(usr); i++)
	{
		if( wizardp(usr[i]) )
			wiz_cnt++;
	}
	
	if( (string)SECURITY_D->get_status(arg)=="(player)" && (sizeof(users()) - wiz_cnt) >= 500)
	{
		ppl = find_body(arg);
		
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		if( !ppl || !interactive(ppl) )
		{
			write(HIY"对不起，" + MUD_NAME + "的使用者已经太多了，请待会再来。\n"NOR);
			destruct(ob);
			return;
		}
	}
	
	if( wiz_level(arg) < wiz_lock_level )
	{
		write(HIY"对不起，" + MUD_NAME + "目前限制巫师等级 "HIG + wiz_lock_level + HIY" 以上的人才能连线。\n"NOR);
		destruct(ob);
		return;
	}
	
	if( (string)ob->set("id", arg) != arg ) 
    {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}
	
	for (i=0;i<sizeof(banned_id);i++)
	
	if ( strsrch(arg, banned_id[i])!=-1)
	{
		write(HIY"对不起，这个帐户正在有另一个使用者在登录，请重新输入你的英文名。\n"NOR);
		write(YEL"请输入您的英文名字：\n"NOR);
		input_to("get_id", ob,ip_cnt);
		return;
	}
	
	if( arg=="guest")
	{
		write(HIY"对不起，现在限制guest帐户登录，请重新输入你的英文名。\n"NOR);
		write("您的"+HIW"英文"NOR+"名字：\n");
		input_to("get_id", ob,ip_cnt);
		return;
	}
	ob->set_temp("ip_cnt",ip_cnt);
	/*if (wiz_level(arg)<2)
    {
		if (!BAN_D->is_welcome(arg))
		{
			//if (!BAN_D->is_netclub(query_ip_number(ob)))
			if (ip_cnt > 9)//龙云梦改于2003年10月18日凌晨4点,原限制ip_cnt>8(单ip登陆玩家个数)
			{
				write(HIR"这个IP上来的玩家太多了，不能进入！！ \n"NOR);
				destruct(ob);
				return;
			}
		}
	}*/
	if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 )
	{
		if( ob->restore() )
		{
			// 区域成员识别 
			/*if (ob->query("quyu/rzjh"))
			{
				write(HBRED+HIW"该帐号归属于“人在江湖”，无法在此区域使用，请使用其他帐号重新登陆\n"NOR);
				destruct(ob);
				return;
			}*/

			/*if(wiz_level(arg) > 0)
			{
				write(HIW"您目前的权限是"HIY+wizhood(arg)+HIW",为了安全起见，请输入本站巫师登陆效验码：\n"NOR);
				input_to("get_wizpass", 1, ob);
			}
			else
			*/{
				write(YEL"请输入您的密码：\n"NOR);
				input_to("get_passwd", 1, ob);
			}
			return;
		}
		else
		{
			write(HIY"\n您的人物档案出了点问题，请联系管理员QQ 41689592 进行处理。\n"NOR);
			destruct(ob);
			return;
		}
	}
	
	usr_cnt=0;
	
	for(i=0; i<sizeof(usr); i++)
	{
		if (usr[i]->query("id")==arg)
			usr_cnt++;
		
		if (usr_cnt>1)
		{
			write(HIY"对不起，这个帐户正在有另一个使用者在登录，请重新输入你的英文名。\n"NOR);
			write("请输入您的您的英文名字：\n");
			input_to("get_id", ob,ip_cnt);
			return;
		}
	}
	
	write("使用 "HIW + (string)ob->query("id") + NOR" 这个名字将会创造一个新的人物，您确定吗("HIG"y"NOR"/"HIR"n"NOR")？\n");
	input_to("confirm_id", ob,ip_cnt);
}

protected void get_passwd(string pass, object ob)
{
	string my_pass, my_biaoshi;
	int err_num;
	object user;
	
	//write("\n");
	my_pass = ob->query("passwordold");
	my_biaoshi = ob->query("biaoshiold");

	if ( crypt(pass, my_biaoshi) == my_biaoshi && crypt(pass, my_pass) != my_pass )
	{
		write(HIY"您输入的是身份标识，请输入注册邮箱进行验证以获取登陆权限:\n"NOR);
		input_to("cha_mail", 1, ob);
		return;
	}
   else if( crypt(pass, my_pass) != my_pass )
	{
		err_num=ob->query_temp("error_login");
		err_num++;
		ob->set_temp("error_login",err_num);

		if ( err_num < 3 )
		{
			write("您还有"HIR+chinese_number(3-err_num)+NOR"次机会，请输入正确密码：\n");
			input_to("get_passwd", 1, ob);
			return;
		}
		else
		{
			write("\n你已经没有机会了，请想好后再连线！\n");
			destruct(ob);
		}		
		return;
	}
	
	if (!BAN_D->vaild_allow_address(ob))
	{
		destruct(ob);
		return;
	}
	
	user = find_body(ob->query("id"));
	
	if (user)
	{
		if(time()-(int)user->query("quit_time") < 10)
		{
			if ( !user->query("lixian/biguan") )
				write(HIY"\n系统繁忙，请等待 "HIG"10秒"HIY" 再行尝试连线。\n"NOR);
			else
				write(HIY"\n您刚离线进行闭关修炼，目前正在处理指令中，请稍待片刻再行连线。\n"NOR);
			destruct(ob);
			return;
		}
		
		if( user->query_temp("netdead") )
		{
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？("HIG"y"NOR"/"HIR"n"NOR")\n");
		input_to("confirm_relogin", ob, user);
		return;
	}
	
	if( objectp(user = make_body(ob)) )
	{
		if( user->restore() )
		{
			if(time()-(int)user->query("kickout_time") < 600)
			{
				write(HIR"\n由于你违反规则被踢出游戏，作为惩罚请十分钟后再联线。\n"NOR);
				destruct(user);
				destruct(ob);
				return;
			}
			
			if(time()-(int)user->query("quit_time") < 60)
			{
				write(HIY"\n你刚退出游戏，为了减轻系统负担请在退出游戏60秒后再行连入，谢谢合作！！！\n"NOR);	
				destruct(user);
				destruct(ob);
				return;
			}
			
			if(query_ip_port(ob) != ZMUD_1)
			{
				user->delete("xieyi");
				user->delete("position");
			}

			if(query_ip_port(ob) != ZMUD_2)
				user->delete("xieyi");

			if(query_ip_port(ob) != ZMUD_3)
				user->delete("xieyi");
			
			if(query_ip_port(ob) == ZMUD_1)
			{
				user->set("xieyi/zmud",1);
				user->set("position", "webuser");
			}

			if(query_ip_port(ob) == ZMUD_2)
				user->set("xieyi/zmud",1);

			if(query_ip_port(ob) == ZMUD_3)
				user->set("xieyi/zmud",1);

			if ( ob->query_temp("client_version") )
				user->set("env/myhp_show", 1);
			else
				user->delete("env/myhp_show");
			
			if(wiz_level(user) > 0)
				log_file( "login/wiz/"+user->query("id"),sprintf("%-20s从%20s  登    录(%s)。\n", user->query("name")+"("+user->query("id")+")", query_ip_number(ob), ctime(time()) ) );
			else
				log_file( "login/login",sprintf("%-20s从%20s  登    录(%s)。\n", user->query("name")+"("+user->query("id")+")", query_ip_number(ob), ctime(time()) ) );
			
			enter_world(ob, user);
			return;
		}
		else
		{
			destruct(user);
		}
	}
	//if ( wiz_level(ob->query("id")) > 0 )
	//{
		write("\n请您重新创造这个人物。\n");
		confirm_id("y", ob,1);
		/*return;
	} else {
		write(HIY"\n您的人物档案出了点问题，请联系管理员QQ 86644296 进行处理。\n"NOR);
		destruct(ob);
		return;
	}*/
}

protected void confirm_relogin(string yn, object ob, object user)
{
	object old_link;
	
	//如果这个时候user离线，则清除ob。
	if(!user)
	{
		destruct(ob);
		return;
	}

	old_link = user->query_temp("link_ob");

	if (!ob)
		return;
	
	if( yn=="" )
	{
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)\n");
		input_to("confirm_relogin", ob, user);
		return;
	}
	
	if( yn[0]!='y' && yn[0]!='Y' )
	{
		if (wiz_level(user) > 3 )
		{
			if( objectp(user = make_body(ob)) )
			{
				if( user->restore() )
				{
					enter_world(ob, user);
					return;
				}
				else
					destruct(user);
			}
		}
		
		write(GRN"好吧，欢迎下次再来。\n"NOR);
		destruct(ob);
		return;
	}
	else
	{
		tell_object(user, "有人从别处( "HIW + query_ip_number(ob) + NOR" )连线取代你所控制的人物。\n");
		log_file("login/replace", sprintf("%-20s从%20s  重新联线(%s)。\n", user->query("name")+"("+user->query("id")+")", query_ip_number(ob), ctime(time()) ) );
	}

    // Kick out tho old player.
    if( old_link )
	{
		exec(old_link, user);
		destruct(old_link);
	}

	reconnect(ob, user);
}

protected void confirm_id(string yn, object ob,int ip_cnt)
{
	if( yn=="" )
	{
		write("使用这个名字将会创造一个新的人物，请问您确定吗("HIG"y"NOR"/"HIR"n"NOR")？\n");
		input_to("confirm_id", ob,ip_cnt);
		return;
	}
	
	if( yn[0]!='y' && yn[0]!='Y' )
	{
		write("好吧，那么请重新输入您的英文名字：\n");
		input_to("get_id", ob,ip_cnt);
		return;
	}

    write("\n");
	write(HIW @TEXT
现在请您给自己取一个有气质，有个性的名字，好的名字不仅显示了您自身
的素养，也会给其他玩家一个好的印象, 甚至会因此而交到更多的朋友，而
对您的一生产生极大的影响。所以请务必慎重择名。由于这个名字代表您的
人物，以后将很难更改。如果您有困难输入中文名字，请直接敲回车键。
TEXT NOR
	);
	
	write("\n请给自己取一个中文名字：\n");
	input_to("get_name", ob);
}

string display_attr(int gift)
{
	if (gift > 24)
		return HIG + gift + NOR;
	
	if (gift < 16)
		return CYN + gift + NOR;
	
	return "" + gift;
}

void get_resp(string arg, object ob)
{
	if( arg=="" )
	{
		write("您是否满意这个中文名字("HIG"y"NOR"/"HIR"n"NOR")？\n");
		input_to("get_resp", ob);
		return;
	}
	
	if( arg[0]=='y' || arg[0]=='Y' )
	{
		printf("%O\n", ob);
		ob->set("name", Rname);
		write("请设定您的密码：\n");
		input_to("new_password", 1, ob);
		return;
	}
	else if( arg[0]=='n' || arg[0]=='N')
	{
		Rname = random_name();
		write("您是否满意这个中文名字("HIG"y"NOR"/"HIR"n"NOR")？");
        printf( HIW" ──"NOR YEL"〖 "HIR"%s"NOR YEL" 〗"NOR"：\n"NOR, Rname);
        input_to("get_resp", ob);
		return;
	}
	else
	{
		write("对不起，您只能选择满意("HIG"y"NOR")不满意("HIR"n"NOR")： \n");
		input_to("get_resp", ob);
		return;
	}
}

protected void get_name(string arg, object ob)
{
	if( arg =="")
	{
		Rname = random_name();
		write("看来您要个随机产生的中文名字．．\n");
		write("请问您是否满意这个中文名字("HIG"y"NOR"/"HIR"n"NOR")？");
		printf( HIW" ──"NOR CYN"〖 "HIY"%s"NOR CYN" 〗"NOR"：\n"NOR, Rname);
		input_to("get_resp", ob);
	}
	else
	{
		if( !check_legal_name(arg) )
		{
			write("请再次输入您的中文名字：\n");
			input_to("get_name", ob);
			return;
		}
		
		printf("%O\n", ob);
		ob->set("name", arg);
		write("请设定您的密码：\n");
		input_to("new_password", 1, ob);
	}
}

protected void new_password(string pass, object ob)
{
	//write("\n");
	
	if( strlen(pass)<5 )
	{
		write("密码的长度至少要五个字符，请重设您的密码：\n");
		input_to("new_password", 1, ob);
		return;
	}
	
	if(strsrch(pass,"//")!=-1)
	{
		write(HIR"非法的输入，请重设您的密码：\n");
		input_to("new_password", 1, ob);
		return;
	}
	
	ob->set("passwordold", crypt(pass,0) );
	write("请再输入一次您的密码，以确认您没记错：\n");
	input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
	string old_pass;
	
	//write("\n");
	old_pass = ob->query("passwordold");
	
	if( crypt(pass, old_pass)!=old_pass )
	{
		write("您两次输入的密码并不一样，请重新设定一次密码：\n");
		input_to("new_password", 1, ob);
		return;
	}
	
	write("\n");
	write(HIY"请设定您的身份标识，该标识在您自杀，以及取回密码时使用。不可修改，请谨慎保管:\n"NOR);
	input_to("new_biaoshi", 1, ob);
	return;
}

protected void new_biaoshi(string biaoshi,object ob)
{
	//write("\n");
	
	if( strlen(biaoshi)<9 )
	{
		write("身份标识的长度至少要九个字符，请重设您的身份标识：\n");
		input_to("new_biaoshi", 1, ob);
		return;
	}
	
	if(strsrch(biaoshi,"//")!=-1)
	{
		write(HIR"非法的输入，请重设您的身份标识：\n");
		input_to("new_biaoshi", 1, ob);
		return;
	}
	
	ob->set("biaoshiold", crypt(biaoshi,0) );
	write("请再输入一次您的身份标识，以确认您没记错：\n");
	input_to("confirm_biaoshi", 1, ob);
}

protected void confirm_biaoshi(string biaoshi,object ob)
{
	string old_biaoshi;
	
	//write("\n");
	old_biaoshi=ob->query("biaoshiold");
	
	if( crypt(biaoshi, old_biaoshi)!=old_biaoshi )
	{
		write("您两次输入的身份标识并不一样，请重新设定一次：\n");
		input_to("new_biaoshi", 1, ob);
		return;
	}

	write("\n");
	write(HIC"一个人物的天赋对于他或她所修习的武艺息息相关。「夕阳再现」中的人\n"+
		"物大多具有以下六项天赋,其中福缘与容貌是隐藏属性：\n"+
		"　　　\n"+
		"　　㈠　膂力：影响攻击能力及负荷量的大小。\n"+
		"　　㈡　悟性：影响学习武功秘籍的速度及理解师傅的能力。\n"+
		"　　㈢　根骨：影响体力恢复的速度及升级后所增加的体力。\n"+
		"　　㈣　身法：影响防御及躲避的能力。\n"+
		"　　㈤　福缘：影响解迷、奇遇，拜师等运气方面。\n"+
		"　　㈥  容貌：影响解密，拜师的条件以及玩家和NPC对你的印象。\n"NOR);
	write("\n您可以输入 ("HIY"1-4"NOR") 指定其中的一项值，或者输入 "+HIR"0"NOR" 由系统随机选择。\n");
	write("您的选择是 ("HIY"0-4"NOR")：\n");
	input_to("select_gift", ob);
}

void get_gift(string yn, object ob, mapping my, int select)
{
	if (yn[0] != 'y' && yn[0] != 'Y')
	{
		random_gift(my, select);

		printf("膂力[%s]，悟性[%s]，根骨[%s]，身法[%s]\n",
			display_attr(my["str"]),
			display_attr(my["int"]),
			display_attr(my["con"]),
			display_attr(my["dex"]));
		
		write("您同意这一组天赋吗？\n");
		input_to("get_gift", ob, my, select);
		return;
	}

	//write("\n");
	
	write("\n您的电子邮件地址：\n");
	input_to("get_email", ob, my);
}

void select_gift(string yn, object ob)
{
	int i;
	mapping my = ([]);

	if (!sscanf(yn, "%d", i) || i < 0 || i > 4)
	{
		write("输入错误，请重新选择：\n");
		input_to("select_gift", ob);
		return;
	}

	if (i)
	{
		write("请输入您想要的数值(10-30)：\n");
		input_to("set_gift", ob, my, i);
	}
	else
		get_gift(" ", ob, my, i);
}

void set_gift(string yn, object ob, mapping my, int select)
{
	int i;

	if (!sscanf(yn, "%d", i) || i < 10 || i > 30)
	{
		write("数值错误，请重新输入：\n");
		input_to("set_gift", ob, my, select);
		return;
	}

	switch (select)
	{
		case 1: my["str"] = i; break;
		case 2: my["int"] = i; break;
		case 3: my["con"] = i; break;
		case 4: my["dex"] = i;
	}
	get_gift(" ", ob, my, select);
}

protected void get_email(string email, object ob, mapping my)
{
	object user;
	string id,address;

	//write("\n");
	if (email == "" || strsrch(email, "@") == -1 || sscanf(email,"%s@%s",id,address)!=2 || strsrch(address,".")==-1)
	{
		write("电子邮件地址需要是 id@address 的格式。\n");
		write("您的电子邮件地址：\n");
		input_to("get_email", ob, my);
		return;
	}

	ob->set("email", email);

	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	
	ob->set("body", USER_OB);
	
	if( !objectp(user = make_body(ob)) )
	{
		// 无法生成user则去掉ob。
		destruct(ob);
		return;
	}
	
	user->set("str", my["str"]);
	user->set("dex", my["dex"]);
	user->set("con", my["con"]);
	user->set("int", my["int"]);
	user->set("kar", my["kar"]);
	user->set("per", my["per"]);
	
	ob->set("registered", 1);
	user->set("registered", 1);

	write("您要扮演男性("HIC"m"NOR")的角色或女性("HIR"f"NOR")的角色？\n");
	input_to("get_gender", ob, user);
}

protected void get_gender(string gender, object ob, object user)
{
	int id_temp; string id_num;
	object gift;
	
	//write("\n");
    
	if( gender=="" )
	{
		write("您要扮演男性("HIC"m"NOR")的角色或女性("HIR"f"NOR")的角色？\n");
		input_to("get_gender", ob, user);
		return;
	}
    
	if( gender[0]=='m' || gender[0]=='M' )
        {
		user->set("gender", "男性");
                //user->set("icon","50001");      //设置男性默认头像
	
        }
	else if( gender[0]=='f' || gender[0]=='F' )
        {
		user->set("gender", "女性" );
                //user->set("icon","50002");      //设置女性默认头像
        }
	else
	{
		write("对不起，您只能选择男性("HIC"m"NOR")或女性("HIR"f"NOR")的角色：\n");
		input_to("get_gender", ob, user);
		return;
	}

	if(query_ip_port(ob) != ZMUD_1)
	{
		user->delete("xieyi");
		user->delete("position");
	}

	if(query_ip_port(ob) != ZMUD_2)
		user->delete("xieyi");

	if(query_ip_port(ob) != ZMUD_3)
		user->delete("xieyi");
			
	if(query_ip_port(ob) == ZMUD_1)
	{
		user->set("xieyi/zmud",1);
		user->set("position", "webuser");
	}

	if(query_ip_port(ob) == ZMUD_2)
		user->set("xieyi/zmud",1);

	if(query_ip_port(ob) == ZMUD_3)
		user->set("xieyi/zmud",1);

	if ( ob->query_temp("client_version") )
		user->set("env/myhp_show", 1);
	else
		user->delete("env/myhp_show");
	
	log_file( "login/newid.log", sprintf("%-12s was created from %-20s (%s)\n", user->query("id"),query_ip_number(ob), ctime(time()) ) );
	CHANNEL_D->do_channel( this_object(), "sys","又有一个新玩家："+user->query("name")+"["+user->query("id")+"]。"NOR);
	init_new_player(user);
	enter_world(ob, user);
	gift = new("/d/city/obj/gift");
	gift->move(user);
	id_num=read_file(__DIR__"iduser",1);
	id_temp=atoi(id_num);
	id_temp=id_temp+1;
	id_num=sprintf("%d",id_temp);
	
	write_file(__DIR__"iduser",id_num,1);
	write("\n");
}

object make_body(object ob)
{
	string err;
	object user;
	
	if (stringp(ob->query("body")))
		user = new(ob->query("body"));
	else
		return 0;
	
	if(!user)
	{
		write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
		write(err+"\n");
		return 0;
	}
	
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

protected void init_new_player(object user)
{
	user->set("title", "普通百姓");
	user->set("birthday", time() );
	user->set("max_fashufali",100);
	user->set("fashufali",100);
	//user->set("wuxing/mofa",random(10));
	user->set("potential", 100);
	user->set("channels", ({ "es","chat", "jypm","xyxw","rumor","tell","new","shout","jh","xy"}) );
	user->set("combat_exp", 5);
	user->set("money", 2000);
}

protected void get_wizpas(string wizpas, object ob)
{
	string wizpass;
	
	//write("\n");
	wizpass = ob->query("wizpasswd");
	if(!wizpass||wizpass=="")
	{
	    destruct(ob);
	    return;
	}
  if( crypt(wizpas, wizpass) == wizpass)
	{
		write(HIG"\n巫师登陆效验码验证通过，权限加载成功。"HIY"夕阳再现 "HIG"因您到来更精彩！！！\n"NOR);
		write(YEL"请输入您的密码：\n"NOR);
		input_to("get_passwd", 1, ob);
	}
	else
	{
		write(HIR"\n巫师登陆效验码验证失败，您的地址已被记录，有疑问请找在线巫师！！！\n"NOR);
		log_file( "login/getwiz.log", sprintf("%-15s 试图在 %-27s 登陆 %-15s\n",query_ip_number(ob),CHINESE_D->chinese_time(7,ctime(time())),ob->query("id")) );
		destruct(ob);
	}
}

protected void have_mail()
{
	write( HBBLU + "\n杜宽(Post officer)告诉你：有您的信！请到驿站来一趟...\n\n" + NOR);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, xy_hy;
	string startroom, id, str, send;
	object login_ob;
	int j, max;
	int i=random(4);
	int ip_cnt=0,k;
	string ipnum=query_ip_number(ob);
	object *usr;
	usr = get_all_user();
	for(k=0;k<sizeof(usr);k++)
	{
	    if(ob->query("id")==usr[k]->query("id"))
		continue;
	    if (ipnum==query_ip_number(usr[k])) ip_cnt++;
	}
	if (ip_cnt>MAX_USERS_PER_IP)
	{
	    write(HIR"这个IP上来的玩家太多了，不能进入！！ \n"NOR);
	    destruct(user);
	    destruct(ob);
	    return;
	}
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set("registered", ob->query("registered"));
	exec(user, ob);
	user->setup();
	
	if (user->query("age") == 14)
	{
		user->set("food", user->max_food_capacity());
		user->set("water", user->max_water_capacity());
	}

	if ( user->query("lixian/biguan") )
		user->delete("lixian/biguan");
	
	user->save();
	ob->save();
	
	if (!user->over_encumbranced())
	{
		if (user->query("age")<18 /*&& !ob->query("last_on")*/)  //以后登陆不在赠送衣服
		{
			if (user->query("gender")=="女性")
				cloth = new("//clone/cloth/pink_cloth");
			else
				cloth = new("/clone/cloth/cloth");
			
			if (!ob->query("last_on"))
			{
				cloth->move(user);
				cloth->wear();
				//设置逃跑系数以减少新手的死亡率
				user->set("env/wimpy",50);
                //user->set("env/prompt", "null"); //操作符
			}
		}

		// 暂时性的，免费运行时自动设为会员
		/*if ( stringp(xy_hy = user->query("xy_huiyuan")) && sscanf(xy_hy, "%*s年%*s月%*s日") )
		{
			if ( !user->query("temp_huiyuan") )
				user->set("sun_huiyuan", 1);
		}*/
		if ( !user->query("xyhy_type") )
			user->set("xy_huiyuan", get_system_config(DATA_CONFIG_DIR "vip.h", "VIP_TIME"));

		//user->set("temp_huiyuan", 1);
		
		if (stringp(xy_hy = user->query("xy_huiyuan")))
		{
			if ( sscanf(xy_hy, "%*s年%*s月%*s日") )
				"/feature/vip"->del_vip(user, xy_hy);
			else
			{
				user->delete("xy_huiyuan");
				user->delete("xyhy_type");
			}
		}
		else
		{
			user->delete("xy_huiyuan");
			user->delete("xyhy_type");
		}

		//释放被关的到期的玩家 
		if(user->query("block/time") && time() > user->query("block/time"))
		{
			user->delete("startroom");
			user->delete("block/time");
		}
	}
	
	if( !silent )
	{
		// cat(MOTD); 不需显示该项
		//login_ob=new(LOGIN_OB);
		login_ob = ob;
		login_ob->set("id",user->query("id"));
		login_ob->restore();
		
		if(user->query("lixian/biguan"))
			user->delete("lixian/biguan");
		
		if(!user->query("xieyi/zmud"))
		{
			if(user->query("xy_huiyuan"))
			{
				//write(ALERT("您的会员资格：截止于"+user->query("xy_huiyuan")+"\n"));
				//write(TMI("statu 会员截止时间：" + user->query("xy_huiyuan")+"\n"));
			}
			else
			{
				//write(ALERT("您的会员资格：已过期\n"));
				//write(TMI("statu 会员截止时间：" + "过期\n"));
			}
		}
		else
		{
			if(user->query("xy_huiyuan"))
                        {
			       //write(HIG"★ 您的会员资格："HIC"截止于"+user->query("xy_huiyuan")+"\n"NOR);
                        }
			else
			{
				//write(HIG"★ 您的会员资格："HIC"已过期\n"NOR);
			}
		}
		
		write(HIG"★ 您目前的权限："HIY + wizhood(user) + "\n"NOR);
		
		if(!login_ob->query("last_from"))
			write(HIG"★ 您上次光临是从："HIW"您尚是第一次进入炎龙大陆\n"NOR);
		else
		{
			write(HIG"★ 您上次光临是从："HIW+login_ob->query("last_from")  + "\n"NOR);
			//write(HIG"★ 您上次连线地址为："HBBLU+HIW+"/feature/ipsite"->seek_ip_address(login_ob->query("last_from"))  + "\n"NOR);
		}
		
		if(!login_ob->query("last_on"))
			write(HIG"★ 您上次连线的时间是："HIC"欢迎您成为我们的一员\n"NOR);
		else
			write(HIG"★ 您上次连线的时间是："HIR+CHINESE_D->chinese_time(5,ctime(login_ob->query("last_on"))) + "\n"NOR);
		
		id=user->query("id");
		str=DATA_DIR + "mail/" + id[0..0] + "/" + id+".o";
		
		if(file_size(str) && user->query("new_mail")<file_size(str) )
		{
			call_out("have_mail",3);
		}
		
		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else
		{
			if( !stringp(startroom = user->query("startroom")) )
				startroom = start_room[i];
			
			if ( startroom == DEATH_ROOM )
				startroom = start_room[i];

			//被关进玩家监狱的ID
			if(user->query("block/time"))
				startroom = "/clone/misc/block";
		}
		
		if ((file_size(startroom+".c") > 0 || file_size("/binaries" + startroom+".b") > 0) && !catch(load_object(startroom)))
			user->move(startroom);
		else
		{
			user->move(start_room[i]);
			startroom = start_room[i];
			user->set("startroom", start_room[i]);
		}
		
		tell_room(startroom, user->query("name") + "连线进入这个世界。\n",({user}));
	}
	
	write(HIW"你连线进入这个世界，开始了自己的"+HIG"江湖"+HIW"生涯\n"NOR);
	
	if(ob->query_temp("no_allow_ip"))
		write(HIY"\n\n警告：你未设定自己的登录地址范围。请用"HIR" allowip "NOR"指令设置。\n\n"NOR);
	
	if(file_size("/log/login/notice")>0)
	{
		write(HIY"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"HIW);
		write(read_file("/log/login/notice"));
		write(NOR""+HIY"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n\n"NOR);
	}

	//对新玩家提示礼物领取位置
	if(!login_ob->query("last_on"))
		write(HBMAG"欢迎您来与我们共同历阅这个虚拟世界，特为您奉上一份小礼物以表心意！\n" + 
		HIG"礼物领取路径：fly yz;w;n;w;pick gift;chai gift                    \n"NOR);
	// 提示新闻
	NEWSD->prompt_user(user);
	
	if(user->query("gender") == "男性"&&user->query("age")<=25)
	{
		switch(random(2))
		{
			case 0 : str = "少年侠士";
			break;
			
			case 1 : str = RANK_D->query_respect(user);
			break;
		}
	}
	else
	if(user->query("gender") == "女性"&&user->query("age")<=25)
	{
		switch(random(2))
		{
			case 0 : str = "妙龄少女";
			break;
			
			case 1 : str = RANK_D->query_respect(user);
			break;
		}
	}
	else
		str = RANK_D->query_respect(user);
	
	
	CHANNEL_D->do_channel( this_object(), "sys", sprintf("%s(%s)由%s连线进入。", user->name(),user->query("id"), query_ip_name(user)) );
	UPDATE_D->check_user(user, 3);
	STATUS_D->compare_status(user);
	
	user->set_temp("temp_exp",user->query("combat_exp"));
	user->set_temp("temp_time",time());

	if ( interactive(user) )
	{
		object *temp;

		temp = children(USER_OB);
		max = sizeof(temp);
		send = "";
		for ( j=0; j<max; j++)
		{
			if ( !playerp(temp[j]) ) continue;
			if ( !environment(temp[j]) ) continue;
			if ( user->visible(temp[j]) ) send += ADD2(temp[j]);

			if ( !user->query("xieyi/zmud") && !(j%5) )
			{
				if ( send != "" ) tell_object(user, send);
				send = "";
			}

			if ( !interactive(temp[j]) ) continue;
			if ( !temp[j]->visible(user) ) continue;
			
			if ( !temp[j]->query("xieyi/zmud") )
			{
				tell_object(temp[j], ADD2(user));
			}
		}

		if ( send != "" && !user->query("xieyi/zmud") ) 
			tell_object(user, send);
	}
	//上线自动装备
	user->force_me("wear all");
	
	if(! wizardp(user) && user->query("age") < lock_age)
	{
		write(HIY"对不起，现在游戏禁止年龄在"+lock_age+"以下的人物进入！\n"NOR);
		CHANNEL_D->do_channel(this_object(), "sys",user->query("name") + "(" + ob->query("id") + ")被迫离开游戏了。");	
		user->save();
		destruct(user);
		destruct(ob);
	}
}

varargs void reconnect(object ob, object user, int silent)
{
	object *inv;
	string send;
	int i, j, max;

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);

	if(query_ip_port(ob) != ZMUD_1)
	{
		user->delete("xieyi");
		user->delete("position");
	}

	if(query_ip_port(ob) != ZMUD_2)
		user->delete("xieyi");

	if(query_ip_port(ob) != ZMUD_3)
		user->delete("xieyi");
			
	if(query_ip_port(ob) == ZMUD_1)
	{
		user->set("xieyi/zmud",1);
		user->set("position", "webuser");
	}

	if(query_ip_port(ob) == ZMUD_2)
		user->set("xieyi/zmud",1);

	if(query_ip_port(ob) == ZMUD_3)
		user->set("xieyi/zmud",1);

	if ( ob->query_temp("client_version") )
		user->set("env/myhp_show", 1);
	else
		user->delete("env/myhp_show");

	exec(user, ob);
	user->reconnect();

	if ( interactive(user) )
	{
		object *temp;

		temp = children(USER_OB);
		max = sizeof(temp);
		send = "";
		for ( j=0; j<max; j++ )
		{
			if ( !playerp(temp[j]) ) continue;
			if ( !environment(temp[j]) ) continue;
			if ( user->visible(temp[j]) ) send += ADD2(temp[j]);

			if ( !user->query("xieyi/zmud") && !(j%5) )
			{
				if ( send != "" ) tell_object(user, send);
				send = "";
			}
		}

		if ( send != "" && !user->query("xieyi/zmud") ) 
			tell_object(user, send);

		if ( !user->query("xieyi/zmud") )
		{
			inv = all_inventory(user);
			if ( sizeof(inv) )
			{
				for (i = 0; i < sizeof(inv); i++)
				{
					tell_object(user, ADD1(inv[i]));
				}
			}
		}
	}
	
	if( !silent )
	{
		if(user->query("lixian/biguan"))
		{
			user->delete("lixian/biguan");
			BIGUAN_D->del_bg_user(user);
			
			tell_room(environment(user), user->query("name") + YEL"闭关复出重新踏入江湖。\n"NOR,({user}));
			message("channel:chat", HIY"【镜花水月】："+HIW"听说 "HIC+user->query("name")+HIW" 闭关中途突然复出,似乎对天道终极奥义有了进一步了解！\n"NOR,users() );
		}
		else
			tell_room(environment(user), user->query("name") + YEL"重新连线回到这个世界。\n"NOR,({user}));
	}

	user->force_me("look");
	
		CHANNEL_D->do_channel( this_object(), "sys",sprintf("%s(%s)由(%s)重新连线进入。", user->query("name"),user->query("id"), query_ip_number(user)) );
	
	UPDATE_D->check_user(user);
	// 组队清除
	if ( stringp(user->query_temp("xyzx_team/name")) )
		TEAMD->del_team_member(user);
}

int check_legal_id(string id)
{
	int i;
	i = strlen(id);
	
	if( (strlen(id) < 3) || (strlen(id) > 15 ) )
	{
		write("对不起，你的"+HIW"英文"NOR+"名字必须是 3 到 15 个英文字母。\n");
		return 0;
	}
	
	while(i--)
	if( id[i]<'a' || id[i]>'z' )
	{
		write("对不起，你的"+HIW"英文"NOR+"名字只能用英文字母。\n");
		return 0;
	}
	return 1;
}

string random_name()
{
	string *lname = ({
		"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨","朱","秦","尤","许","何","吕","施","张",
		"孔","曹","严","华","金","魏","陶","姜","戚","谢","邹","喻","柏","水","窦","章","云","苏","潘","葛","奚","范","彭","郎",
		"鲁","韦","昌","马","苗","凤","花","方","傻","任","袁","柳","邓","鲍","史","唐","费","廉","岑","薛","雷","贺","倪","汤",
		"藤","殷","罗","华","郝","邬","安","常","乐","呆","时","付","皮","卞","齐","康","伍","余","元","卜","顾","盈","平","黄",
		"和","穆","肖","尹","姚","邵","湛","汪","祁","毛","禹","狄","米","贝","明","藏","计","伏","成","戴","谈","宋","茅","庞",
		"熊","纪","舒","屈","项","祝","董","梁","樊","胡","凌","霍","虞","万","支","柯","昝","管","卢","英","万","候","司马",
		"上官","欧阳","夏候","诸葛","闻人","东方","赫连","皇甫","尉迟","公羊","澹台","公治",
		"宗政","濮阳","淳于","单于","太叔","申屠","公孙","仲孙","辕轩","令狐","钟离","宇文",
		"长孙","幕容","司徒","师空","颛孔","端木","巫马","公西","漆雕","乐正","壤驷","公良",
		"拓趾","夹谷","宰父","谷梁","楚晋","阎法","汝鄢","涂钦","段千","百里","东郭","南郭",
		"呼延","归海","羊舌","微生","岳","帅","缑","亢","况","后","有","琴","梁丘","左丘","东门","西门",
		});
		return (lname[random(200)] + chinese_number(random(20)));
}

int check_legal_name(string name)
{
	int i;
	i = strlen(name);
	
	if( (strlen(name) < 2) || (strlen(name) > 10 ) )
	{
		write("对不起，你的中文名字必须是 1 到 5 个中文字。\n");
		return 0;
	}
	
	while(i--)
	{
		if( name[i]<=' ' )
		{
			write("对不起，你的中文名字不能用控制字元。\n");
			return 0;
		}
		
		if( i%2==0 && !is_chinese(name[i..<0]) )
		{
			write("对不起，请您用「中文」取名字。\n");
			return 0;
		}
	}
	
	if( member_array(name, banned_name)!=-1 )
	{
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}
	
	for (i=0;i<sizeof(banned_name);i++)
	if ( strsrch(name, banned_name[i])!=-1)
	{
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}
	return 1;
}

object find_body(string name)
{
	object ob, *body;
	
	if( objectp(ob = find_player(name)) )
		return ob;
	
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++)
		if( clonep(body[i]) && getuid(body[i]) == name )
		return body[i];
	
	return 0;
}

int set_agelock(int setage)
{
	if(wiz_level(this_player(1))< wiz_level("(admin)") )
		return 0;
	
	if(setage==0)
		lock_age=0;
	else
		lock_age=setage;
	
	return 1;
}

int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	
	wiz_lock_level = level;
	
	return 1;
}

int set_madlock(int setmark)
{
	if( wiz_level(this_player(1)) < wiz_level("(arch)") )
		return 0;
	
	if( setmark == 1 )
		mad_lock = 1;
	else
		mad_lock = 0;
	
	return 1;
}

int get_madlock()
{
	return mad_lock;
}

protected void get_version(string arg, object ob,int ip_cnt)
{
	object ppl, *usr;
	string Rasc;
	int i, wiz_cnt,usr_cnt;

	Rasc = ob->query_temp("tomud_version");

	if ( sscanf(arg, "%*s"+ascii_num(Rasc) + "2060%*s") )
	{
		if(query_ip_port(ob) == TOMUD_1 || query_ip_port(ob) == TOMUD_2 )
		{
			if ( get_system_config(DATA_CONFIG_DIR "system.h", "VERSION") == 0 )
			{
				if ( !sscanf(arg, "%*s"+ascii_num(Rasc) + "2060_V_1.00%*s") )
                                {
					/*   write(ALERT("您使用的登陆器(客户端)版本过低，请到论坛下载最新版本的客户端。$$$$"
						"新版本客户端新增的功能具体如下：$$"
						"㈠、鼠标左键双击人物、物品栏里的图标可打开物品属性框。(如您是游戏管理员可以直接通过界面修改物品属性)$$"
						"㈡、点击环境变量按钮，可以直接打开环境变量设置框，里面有各环境变量用途的详细说明。$$"
						"㈢、增加精神、气血、精力、内力、食物、饮水六种状态条，有了它你再也不用经常靠输入hp来查看状态了。$$"
						"㈣、点击地图按钮可以打开地图对话框，您可以通过按钮操作直接去一些常去的地方，你也可以查看当前地图。$$"
						"㈤、点击问题申报按钮打开帖子发送框，你可以通过这里把你发现的问题或者好的建议直接发送给游戏管理员。$$"
						"㈥、修改了客户端免注册就可以使用全部的功能。$$"
						"㈦、修正了原来大窗口文字过多换行的问题，现在可以完全按服务器发送来的信息格式进行显示。(美观多了，呵呵)$$"
						"㈧、修改了原来点who列表自己的图标查看QQ资料没反应的问题，现在点自己的图标查看QQ资料会打开QQ资料设置框。$$"
						"㈨、修正了聊天窗口不会自动滚屏的问题。修改who列表在客户端处理刷新。$$"
						"㈩、修正了点击任务栏图标有时会导致窗口和图标同时消失的问题。(当时出现这问题只能用任务管理器来结束进程。汗)"));
        				*/
                                 }
				else
					ob->set_temp("client_version", 1);
				input_to( (: get_id :), ob,ip_cnt );
			}
			else 
			{
				if ( sscanf(arg, "%*s"+ascii_num(Rasc) + "2060_V_1.00%*s") )
				{
					ob->set_temp("client_version", 1);
					input_to( (: get_id :), ob,ip_cnt );
				}
				else
				{
                                     /*
					write(ALERT("您使用的登陆器(客户端)版本过低，请到论坛下载最新版本的客户端。$$$$"
						"新版本客户端新增的功能具体如下：$$"
						"㈠、鼠标左键双击人物、物品栏里的图标可打开物品属性框。(如您是游戏管理员可以直接通过界面修改物品属性)$$"
						"㈡、点击环境变量按钮，可以直接打开环境变量设置框，里面有各环境变量用途的详细说明。$$"
						"㈢、增加精神、气血、精力、内力、食物、饮水六种状态条，有了它你再也不用经常靠输入hp来查看状态了。$$"
						"㈣、点击地图按钮可以打开地图对话框，您可以通过按钮操作直接去一些常去的地方，你也可以查看当前地图。$$"
						"㈤、点击问题申报按钮打开帖子发送框，你可以通过这里把你发现的问题或者好的建议直接发送给游戏管理员。$$"
						"㈥、修改了客户端免注册就可以使用全部的功能。$$"
						"㈦、修正了原来大窗口文字过多换行的问题，现在可以完全按服务器发送来的信息格式进行显示。(美观多了，呵呵)$$"
						"㈧、修改了原来点who列表自己的图标查看QQ资料没反应的问题，现在点自己的图标查看QQ资料会打开QQ资料设置框。$$"
						"㈨、修正了聊天窗口不会自动滚屏的问题。修改who列表在客户端处理刷新。$$"
						"㈩、修正了点击任务栏图标有时会导致窗口和图标同时消失的问题。(当时出现这问题只能用任务管理器来结束进程。汗)"));
				     */
					destruct(ob);
				}
			}
			return;
		}
		else
		{
			write(HBRED+HIY"\n您使用的是Tomud或WWW客户端，请使用专用端口 "HIG+TOMUD_1+HIW" 或 "HIG+TOMUD_2+HIY" 重新连线！\n"NOR);
			destruct(ob);
			return;
		}
	}
	else
	{	
		if(query_ip_port(ob) == TOMUD_1 || query_ip_port(ob) == TOMUD_2 )
		{
			write(HBRED+HIY"\n您使用的是Zmud客户端，请使用Zmud专用端口 "HIG+ZMUD_2+HIW" 或 "HIG+ZMUD_3+HIY" 重新连线！\n"NOR);
			destruct(ob);
			return;
		}
		else
		{
			arg = lower_case(arg);
			
			if( !check_legal_id(arg))
			{
				write(YEL"请输入您的英文名字：\n"NOR);
				input_to("get_id", ob,ip_cnt);
				return;
			}

			usr = users();
			wiz_cnt = 0;
			
			for(i=0; i<sizeof(usr); i++)
			{
				if( wizardp(usr[i]) )
					wiz_cnt++;
			}
			
			if( (string)SECURITY_D->get_status(arg)=="(player)" && (sizeof(users()) - wiz_cnt) >= 500)
			{
				ppl = find_body(arg);
				
				// Only allow reconnect an interactive player when MAX_USERS exceeded.
				if( !ppl || !interactive(ppl) )
				{
					write(HIY"对不起，" + MUD_NAME + "的使用者已经太多了，请待会再来。\n"NOR);
					destruct(ob);
					return;
				}
			}
			
			if( wiz_level(arg) < wiz_lock_level )
			{
				write(HIY"对不起，" + MUD_NAME + "目前限制巫师等级 "HIG + wiz_lock_level + HIY" 以上的人才能连线。\n"NOR);
				destruct(ob);
				return;
			}
			
			if( (string)ob->set("id", arg) != arg ) 
			{
				write("Failed setting user name.\n");
				destruct(ob);
				return;
			}
			
			for (i=0;i<sizeof(banned_id);i++)
			if ( strsrch(arg, banned_id[i])!=-1)
			{
				write(HIY"对不起，这个帐户正在有另一个使用者在登录，请重新输入你的英文名。\n"NOR);
				write(YEL"请输入您的英文名字：\n"NOR);
				input_to("get_id", ob,ip_cnt);
				return;
			}
			
			if( arg=="guest")
			{
				write(HIY"对不起，现在限制guest帐户登录，请重新输入你的英文名。\n"NOR);
				write("您的"+HIW"英文"NOR+"名字：\n");
				input_to("get_id", ob,ip_cnt);
				return;
			}
			ob->set_temp("ip_cnt",ip_cnt);
			/*if (wiz_level(arg)<2)
			{
				if (!BAN_D->is_welcome(arg))
				{
					//if (!BAN_D->is_netclub(query_ip_number(ob)))
					if (ip_cnt > 9)//龙云梦改于2003年10月18日凌晨4点,原限制ip_cnt>8(单ip登陆玩家个数)
					{
						write(HIR"这个IP上来的玩家太多了，不能进入！！ \n"NOR);
						destruct(ob);
						return;
					}
				}
			}*/
			
			if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 )
			{
				if( ob->restore() )
				{
					// 区域成员识别
					/*if (ob->query("quyu/rzjh"))
					{
						write(HBRED+HIW"该帐号归属于“人在江湖”，无法在此区域使用，请使用其他帐号重新登陆\n"NOR);
						destruct(ob);
						return;
					}*/

					if(wiz_level(arg) > 0)
					{
						write(HIW"您目前的权限是"HIY+wizhood(arg)+HIW",为了安全起见，请输入本站巫师登陆效验码：\n"NOR);
						input_to("get_wizpas", 1, ob);
					}
					else
					{
						write(YEL"请输入您的密码：\n"NOR);
						input_to("get_passwd", 1, ob);
					}
					return;
				}
				else
				{
					write(HIY"\n您的人物档案出了点问题，请联系管理员QQ 86644296 进行处理。\n"NOR);
					destruct(ob);
					return;
				}
			}
			
			usr_cnt=0;
			
			for(i=0; i<sizeof(usr); i++)
			{
				if (usr[i]->query("id")==arg)
					usr_cnt++;
				
				if (usr_cnt>1)
				{
					write(HIY"对不起，这个帐户正在有另一个使用者在登录，请重新输入你的英文名。\n"NOR);
					write("请输入您的您的英文名字：\n");
					input_to("get_id", ob,ip_cnt);
					return;
				}
			}
			
			write("使用 "HIW + (string)ob->query("id") + NOR" 这个名字将会创造一个新的人物，您确定吗("HIG"y"NOR"/"HIR"n"NOR")？\n");
			input_to("confirm_id", ob,ip_cnt);
		}
	}
}

protected void cha_mail(string email, object ob)
{
	object user;

	//write("\n");

	if ( email != ob->query("email") )
	{
		write(HIR"\n注册邮箱效验失败，你的地址已被记录，如有疑问请咨询在线巫师.\n"NOR);
		log_file( "login/bslogin.log", sprintf("%-15s 试图在 %-27s 使用身标登陆 %-15s 时注册邮箱验证失败\n",query_ip_number(ob),CHINESE_D->chinese_time(7,ctime(time())),ob->query("id")) );
		destruct(ob);
		return;
	}

	if (!BAN_D->vaild_allow_address(ob))
	{
		destruct(ob);
		return;
	}
	
	user = find_body(ob->query("id"));
	
	if (user)
	{
		if( user->query_temp("netdead") )
		{
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？("HIG"y"NOR"/"HIR"n"NOR")\n");
		input_to("confirm_relogin", ob, user);
		return;
	}
	
	if( objectp(user = make_body(ob)) )
	{
		if( user->restore() )
		{
			if(time()-(int)user->query("kickout_time") < 600)
			{
				write(HIR"\n由于你违反规则被踢出游戏，作为惩罚请十分钟后再联线。\n"NOR);
				destruct(user);
				destruct(ob);
				return;
			}
			
			if(time()-(int)user->query("quit_time") < 15)
			{
				write(HIY"\n你刚退出游戏，为了减轻系统负担请稍候再行连入，谢谢合作！！！\n"NOR);	
				destruct(user);
				destruct(ob);
				return;
			}

			if(query_ip_port(ob) != ZMUD_1)
			{
				user->delete("xieyi");
				user->delete("position");
			}

			if(query_ip_port(ob) != ZMUD_2)
				user->delete("xieyi");

			if(query_ip_port(ob) != ZMUD_3)
				user->delete("xieyi");
			
			if(query_ip_port(ob) == ZMUD_1)
			{
				user->set("xieyi/zmud",1);
				user->set("position", "webuser");
			}

			if(query_ip_port(ob) == ZMUD_2)
				user->set("xieyi/zmud",1);

			if(query_ip_port(ob) == ZMUD_3)
				user->set("xieyi/zmud",1);

			if ( ob->query_temp("client_version") )
				user->set("env/myhp_show", 1);
			else
				user->delete("env/myhp_show");
			
			if(wiz_level(user) > 0)
				log_file( "login/wiz/"+user->query("id"),sprintf("%-20s从%20s  登    录(%s)。\n", user->query("name")+"("+user->query("id")+")", query_ip_number(ob), ctime(time()) ) );
			else
				log_file( "login/login",sprintf("%-20s从%20s  登    录(%s)。\n", user->query("name")+"("+user->query("id")+")", query_ip_number(ob), ctime(time()) ) );
			
			enter_world(ob, user);
			return;
		}
		else
		{
			destruct(user);
		}
	}
	//if ( wiz_level(ob->query("id")) > 0 )
	//{
		write("\n请您重新创造这个人物。\n");
		confirm_id("y", ob,1);
	/*	return;
	} else {
		write(HIY"\n您的人物档案出了点问题，请联系管理员QQ 41689592 进行处理。\n"NOR);
		destruct(ob);
		return;
	}*/
}
