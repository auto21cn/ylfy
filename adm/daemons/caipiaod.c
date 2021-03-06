#include <ansi.h>
#include <localtime.h>
#include <dbase.h>

inherit F_SAVE;

void do_kaijiang(string type);
void time_go();

object cpb;

void create()
{
    time_go();
}

string record_time(int time)
{
    int mo, d, h, m, s;
    mixed *ltime;
    string ctime;
    ltime = localtime(time);
    s = ltime[LT_SEC];
    m = ltime[LT_MIN];
    h = ltime[LT_HOUR];
    d = ltime[LT_MDAY];
    mo = ltime[LT_MON]+1;
    ctime = "";
    ctime += chinese_number(mo) + "月";
    ctime += chinese_number(d) + "日";
    ctime += chinese_number(h) + "时";
    ctime += chinese_number(m) + "分";
    ctime += chinese_number(s) + "秒";
    return ctime;
}

void time_go()
{
	object *cpbs;
    int i, j;

	i = time();
	cpbs = children("/clone/misc/caipiao_ban");
	cpbs -= ({ find_object("/clone/misc/caipiao_ban") });
	if ( !sizeof(cpbs) )
	{
		cpb = new("/clone/misc/caipiao_ban");
		if ( !objectp(cpb) ) return;
		cpb->move("/d/city/caipiao");
	}
	else if ( sizeof(cpbs) > 1 )
	{
		cpb = cpbs[0];
		for ( j=1; j<sizeof(cpbs); j++ )
		{
			destruct(cpbs[j]);
		}
	}
	else
		cpb = cpbs[0];
    remove_call_out("time_go");
    call_out("time_go", 1);
    cpb->restore();
    if (cpb->query("kaijiang_date") &&(i>cpb->query("kaijiang_date") || i==cpb->query("kaijiang_date")))
        do_kaijiang("kaijiang");
    else if(cpb->query("end_date") &&(i>cpb->query("end_date") || i==cpb->query("end_date")))
        do_kaijiang("end");
    else if(cpb->query("start_date") && (i==cpb->query("start_date") || i>cpb->query("start_date")))
        do_kaijiang("start");
    if (!cpb->query("start_date") && !cpb->query("kaijiang_date"))
        do_kaijiang("start");
    i=0;
}

void do_kaijiang(string type)
{
    int i,z,p=0;
    int *jieguo=({});
    string str="";
    if (type=="kaijiang")
    {
        cpb->restore();
        message("sendto_alluser",HIW"〖泥潭福彩〗：下面将开出本期彩票大奖！\n"NOR,users());
        i=0;
        z=0;
        while(p!=7)
        {
            i=random(30)+1;
            if(member_array(i,jieguo)!=-1) continue;
            else 
            {
                jieguo+=({i});
                p++;
                continue;
            }
        }
        for(i=0;i<sizeof(jieguo);i++)
            str+=jieguo[i]+" ";
        message("sendto_alluser",HIW"〖泥潭福彩〗：第"+chinese_number(cpb->query("times"))+"期兑奖号码为"+BLINK+HIR+str+"！\n"NOR,users());
        message("sendto_alluser",HIW"〖泥潭福彩〗：可以去扬州赌场彩票投注中心read biao来查看得奖名单。\n"NOR,users());
        cpb->set("last_z_num",jieguo);
        cpb->set("last_z_num_str",str);
        cpb->set("duijiang",1);
        cpb->delete("kaijiang_date");
        cpb->delete("kaijiang_cdate");
        cpb->delete("end_date");
        cpb->delete("end_cdate");
        cpb->add ("times",1);
        cpb->set("start_date",(time()+2*60*60*24)/60*60);
        cpb->set("start_cdate",record_time((time()+2*60*60*24)/60*60));
        cpb->save();
        cpb->show_player();
        cpb->set("last_gold",cpb->query("all_gold"));
        if (!cpb->query("zhongjiang_num")) cpb->add("all_gold",50000);
        else cpb->set("all_gold",500000);
        cpb->save();
        message("sendto_alluser",HIW"〖泥潭福彩〗：下期彩票将于"+cpb->query("start_cdate")+"开始发行，欢迎购买。\n"NOR,users());
        message("alluser",HIW"〖泥潭福彩〗：第"+chinese_number(cpb->query("times"))+"期预计奖金"+chinese_number(cpb->query("all_gold"))+"两黄金。\n"NOR,users());
        cpb->auto_post(
          sprintf(HIR"〖泥潭福彩〗：本期彩票开奖号码为"+str+"！"NOR),
          sprintf("中奖名单如下：%s",cpb->show_player()),
        );
        rm("/data/caipiao/call");
        write_file("/data/caipiao/call",sprintf(
			"〖赌场消息〗：本期彩票大奖已开出，兑奖号码为"+str+"\n" + 
			"〖赌场消息〗：下期彩票将于"+cpb->query("start_cdate")+"开始发行，欢迎购买。\n" + 
			"〖赌场消息〗：下期彩票预计奖金"+chinese_number(cpb->query("all_gold"))+"两黄金。\n"));
        return;
    }
    else if(type=="end" )
    {
        cpb->restore();
        cpb->set("end_ya",1);
        cpb->delete("start_date");
        cpb->delete("start_cdate");
        cpb->delete("end_date");
        cpb->delete("end_cdate");
        cpb->save();
        message("sendto_alluser",HIW"〖泥潭福彩〗：本期彩票停止购买，请关注开奖结果！\n"NOR,users());
        message("sendto_alluser",HIW"〖泥潭福彩〗：本期彩票将于"+cpb->query("kaijiang_cdate")+"开奖！\n"NOR,users());
		rm("/data/caipiao/call");
		write_file("/data/caipiao/call",sprintf(
			"〖赌场消息〗：本期彩票已停止购买，请关注开奖结果！\n" + 
			"〖赌场消息〗：本期彩票将于"+cpb->query("kaijiang_cdate")+"开奖！\n"));
		return;
	}
    else if(type=="start")
    {
        cpb->restore();
        cpb->clean_data();
        if (!cpb->query("all_gold")) cpb->set("all_gold",500000);
        message("alluser",HIW"〖泥潭福彩〗：第"+chinese_number(cpb->query("times"))+"期彩票开始发行，欢迎大家前来购买。\n"NOR,users());
        message("alluser",HIW"〖泥潭福彩〗：第"+chinese_number(cpb->query("times"))+"期预计奖金"+chinese_number(cpb->query("all_gold"))+"两黄金。\n"NOR,users());                
        cpb->delete("end_ya");
        cpb->delete("duijiang");
        cpb->delete("last_z_num");
        cpb->delete("last_z_num_str");
        cpb->delete("start_date");
        cpb->delete("start_cdate");
        cpb->set("kaijiang_cdate",record_time((time()+3*60*60*24)/60*60));
        cpb->set("kaijiang_date",(time()+3*60*60*24)/60*60);
        cpb->set("end_cdate",record_time((time()+70*60*60)/60*60));
        cpb->set("end_date",(time()+7*60*60*10)/60*60);
        cpb->save();
        cpb->restore();
        message("alluser",HIW"〖泥潭福彩〗：第"+chinese_number(cpb->query("times"))+"期彩票将于"+cpb->query("end_cdate")+"停止发行。\n"NOR,users());
		rm("/data/caipiao/call");
		write_file("/data/caipiao/call",sprintf(
			"〖赌场消息〗：第"+chinese_number(cpb->query("times"))+"期彩票已经发行，欢迎大家前来购买。\n" + 
			"〖赌场消息〗：第"+chinese_number(cpb->query("times"))+"期累计奖金"+chinese_number(cpb->query("all_gold"))+"两黄金。\n" + 
			"〖赌场消息〗：第"+chinese_number(cpb->query("times"))+"期彩票将于"+cpb->query("end_cdate")+"停止发行。\n"));
        return; 
    }
    return; 
}

