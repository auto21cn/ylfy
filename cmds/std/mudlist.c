
// mudlist.c Yuj@SJ 1999-6-2

#include <ansi.h>
#include <net/daemons.h>
#include <net/macros.h>

inherit F_CLEAN_UP;
inherit F_DBASE;

int main(object me, string arg)
{
        mapping mud_list;
        mixed *muds;
        string output;
        int loop, size, count=0, total;

        if( !find_object(DNS_MASTER) )
                return notify_fail("网路精灵并没有被载入。\n");

		if ( !DNS_MASTER->query_doing_end() )
			return notify_fail("正与各站点同步更新中。。。。。\n");

        //      Obtain mapping containing mud data
        mud_list = (mapping)DNS_MASTER->query_muds();

        if(!mud_list)
                return notify_fail( MUD_NAME + "目前并没有跟网路上其他 Mud 取得联系。\n");

        //      Get list of all mud names within name server
        muds = keys( mud_list ) - ({ "DEFAULT" });

        //      Place mudlist into alphabetical format
        muds = sort_array(muds, 1);

        //      If mudname provided, search server's database for a match
        //      and display its cooresponding address
        if( arg ) arg = upper_case(arg);
        if(arg && arg != "ALL") {
                arg = htonn(arg);
                if(!mapp( mud_list[arg] )) {
                        write(MUD_NAME + "并没有和这个 Mud 取得联系。\n");
                        return 1;
                }
                if( wizardp(me) && !me->query("env/debug") )
                        printf("有关 %s 的资讯：\n%O\n", arg, mud_list[arg]);
                else
                        printf("\n有关 %s 的资讯：\n"
                                "──────────────────\n"
                                "中文名称：  %s\n"
                                "语言：      %s\n"
                                "版本：      %s\n"
                                "MudOS：     %s\n"
                                "Mudlib：    %s\n"
                                "主机：      %s\n"
                                "端口：      %s\n"
                                "状态：      %s\n"
                                "在线玩家：  %s\n"
                                "当地时间：  %s\n"
                                "──────────────────\n\n",
                                mud_list[arg]["NAME"],
                                undefinedp(mud_list[arg]["MUDNAME"])?
                                "不详":mud_list[arg]["MUDNAME"],
                                undefinedp(mud_list[arg]["ENCODING"])?
                                "不详":(mud_list[arg]["ENCODING"]=="GB"?"简体汉字":"繁体汉字"),
                                undefinedp(mud_list[arg]["VERSION"])?
                                "不详":mud_list[arg]["VERSION"],
                                undefinedp(mud_list[arg]["DRIVER"])?
                                "不详":mud_list[arg]["DRIVER"],
                                undefinedp(mud_list[arg]["MUDLIB"])?
                                "不详":mud_list[arg]["MUDLIB"],
                                mud_list[arg]["HOSTADDRESS"],
                                mud_list[arg]["PORT"],
                                mud_list[arg]["_dns_no_contact"]<1?
                                "连线":"断开",
                                undefinedp(mud_list[arg]["USERS"])?
                                "不详":mud_list[arg]["USERS"],
                                undefinedp(mud_list[arg]["TIME"])?
                                "不详":mud_list[arg]["TIME"],
                                );
                return 1;
        }

        output = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"+
BBLU+HIW" 中文名称              国际网络位址    端口 运行时间          人数\n"NOR+
"─────────────────────────────────\n";
        //      Loop through mud list and store one by one
        for(loop = 0, size = sizeof(muds); loop<size; loop++) {
                if( !arg && mud_list[muds[loop]]["VERSION"] != MUDLIB_VERSION )
                        continue;
                if( arg ) {
                        if( arg!="ALL" && mud_list[muds[loop]]["MUDLIB"] != MUDLIB_NAME )
                                continue;
                }
                if( mud_list[muds[loop]]["_dns_no_contact"] > 0 ) {
                        if( !me || !wizardp(me) || (wizardp(me) && me->query("env/debug")) )
                                continue;
                }

		if( htonn(upper_case(muds[loop])) == htonn(upper_case(INTERMUD_MUD_NAME)) )
			output +=  BRED+HIY;
			output +=  sprintf(HIW"%-22s %-15s %4s ", 
				(undefinedp(mud_list[muds[loop]]["MUDNAME"])?"":mud_list[muds[loop]]["MUDNAME"]) +
				"(" + upper_case(muds[loop]) + ")",
				mud_list[muds[loop]]["HOSTADDRESS"],
				mud_list[muds[loop]]["PORT"]);
		if (mud_list[muds[loop]]["TIME"] != query(muds[loop])) {
			set(muds[loop], mud_list[muds[loop]]["TIME"]);
			set(muds[loop]+".Time", time());
		}
		if (time() > query(muds[loop]+".Time") + 2100) output += "<失去联系>";
		else {
			string tmp = "";
			int d, h, m, s;

			total = atoi(mud_list[muds[loop]]["TIME"]);
			d = total / 86400;
			if (d) tmp += d + "天";
			h = (total % 86400) / 3600;
			if (h) tmp += h + "小时";
			m = (total % 3600) / 60;
			if (m) tmp += m + "分";
			s = total % 60;
			if (s) tmp += s + "秒";
			output += sprintf("%-16s", tmp);
			if(!undefinedp(mud_list[muds[loop]]["USERS"])) {
				output+=sprintf(" %4s", mud_list[muds[loop]]["USERS"] );
				count += atoi(mud_list[muds[loop]]["USERS"]);
			} else    output+=" ---";
		}

                output += NOR"\n";
        }
	//      Display dumped mudlist output through user's more pager
	output+="━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	output += HIW"「"HIR"夕阳再现"HIW"」"NOR"共有" +HIG+ chinese_number(count) + NOR"位玩家连线中。\n";
        write( output );

	return 1;
}

int help()
{
	write("\n指令格式：mudlist            列出连线中的"MUD_NAME"站点。\n"
		"          mudlist <MudName>  列出指定 Mud 的信息。\n"
		"          mudlist all        列出目前所有连线中的 Mud。\n\n"
        );
        return 1;
}
