
#include <ansi.h>	
#include <mudlib.h>	
inherit F_CLEAN_UP;        	
int top_list(object ob1,object ob2);	
int get_score(object ob);	
int main(object me, string arg)	
{	
object *list,*ob;           	
int i;	
string msg,partyzhiwei;     	
if (!wizardp(me))		
return notify_fail(YEL"只有巫师才能查询会员名单！\n"NOR);	
ob = filter_array(children(USER_OB), (: $1->query("xy_huiyuan") && !wizardp($1) :));	
list = sort_array(ob, (: top_list :));
msg =  "\n"+HIW"     ◇"HIY"夕阳再现"HIC" 会员查询列表： \n"+HIW;                      	
msg += "    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";      	
msg += "    ┃      会        员     │    时    间   │  期      限  ┃\n";      
msg += "    ┠────────────────────────────┨\n"NOR;  	
for (i = 0 ;i < sizeof(list) ; i++) {                   	
if(list[i]->query("xy_huiyuan")=="2006年1月21号" || list[i]->query("xy_huiyuan")=="2005年12月31号" || list[i]->query("xy_huiyuan")=="2005年12月19号" || list[i]->query("xy_huiyuan")=="2005年10月25号" || list[i]->query("xy_huiyuan")=="2005年10月15号" || list[i]->query("xy_huiyuan")=="2005年10月10号" || list[i]->query("xy_huiyuan")=="2005年10月13号")       	
{	
partyzhiwei="   一    年   ";	
msg +=HIG;      	
}
else  if(list[i]->query("xy_huiyuan")=="2005年9月10号")       	
{
partyzhiwei="   十一 月   ";   	
msg +=GRN;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年8月10号")       	
{
partyzhiwei="   十    月   ";   	
msg +=GRN;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年7月10号")       	
{
partyzhiwei="   九    月   ";   	
msg +=GRN;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年6月10号")       	
{
partyzhiwei="   八    月   ";   	
msg +=GRN;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年5月13号" || list[i]->query("xy_huiyuan")=="2005年5月10号" || list[i]->query("xy_huiyuan")=="2005年5月11号")       	
{
partyzhiwei="   七    月   ";   	
msg +=GRN;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年10月19号" || list[i]->query("xy_huiyuan")=="2005年10月18号" || list[i]->query("xy_huiyuan")=="2005年10月11号" || 
	list[i]->query("xy_huiyuan")=="2005年8月12号" || list[i]->query("xy_huiyuan")=="2005年8月2号" || list[i]->query("xy_huiyuan")=="2005年8月26号" || 
	list[i]->query("xy_huiyuan")=="2005年7月15号" || list[i]->query("xy_huiyuan")=="2005年7月13号" || list[i]->query("xy_huiyuan")=="2005年6月30号" || list[i]->query("xy_huiyuan")=="2005年6月28号" || list[i]->query("xy_huiyuan")=="2005年6月25号" || list[i]->query("xy_huiyuan")=="2005年6月18号" || list[i]->query("xy_huiyuan")=="2005年6月16号" || list[i]->query("xy_huiyuan")=="2005年6月13号" || list[i]->query("xy_huiyuan")=="2005年5月29号" || list[i]->query("xy_huiyuan")=="2005年5月21号" || list[i]->query("xy_huiyuan")=="2005年5月16号" || list[i]->query("xy_huiyuan")=="2005年5月14号" || list[i]->query("xy_huiyuan")=="2005年5月12号" || list[i]->query("xy_huiyuan")=="2005年4月30号" || list[i]->query("xy_huiyuan")=="2005年4月13号" || list[i]->query("xy_huiyuan")=="2005年4月12号" || list[i]->query("xy_huiyuan")=="2005年4月10号" || list[i]->query("xy_huiyuan")=="2005年4月11号")       	
{
partyzhiwei="   半    年   ";   	
msg +=YEL;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年4月4号" || list[i]->query("xy_huiyuan")=="2005年3月10号")       	
{
partyzhiwei="   五    月   ";   	
msg +=HIW;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年2月10号")       	
{
partyzhiwei="   四    月   ";   	
msg +=HIW;              	
}
else  if(list[i]->query("xy_huiyuan")=="2005年2月25号" || list[i]->query("xy_huiyuan")=="2005年2月7号" || list[i]->query("xy_huiyuan")=="2005年1月18号" || list[i]->query("xy_huiyuan")=="2005年1月14号" || list[i]->query("xy_huiyuan")=="2005年1月13号" || list[i]->query("xy_huiyuan")=="2005年1月10号" || list[i]->query("xy_huiyuan")=="2005年1月11号")       	
{
partyzhiwei="   三    月   ";   	
msg +=HIW;              	
}
else  if(list[i]->query("xy_huiyuan")=="2004年12月10号")       	
{
partyzhiwei="   二    月   ";   	
msg +=HIW;              	
}
else	
{ 	
partyzhiwei="   一    月   ";	
msg +=HIW;	
}	
msg += sprintf("    ┃%-22s    %-10s %-15s┃\n"NOR,list[i]->query("name")+"("+                        	
capitalize(list[i]->query("id"))+")",partyzhiwei,list[i]->query("xy_huiyuan")             	
);    	
}	
msg += HIW+"    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";          	
msg += sprintf(HIY"     目前游戏中共有 "HIG"%s"HIY" 位会员在线。\n"NOR,chinese_number(i));
write(msg);	
return 1;	
}	
int top_list(object ob1, object ob2)	
{	
int score1,score2;	
score1 = get_score(ob1);	
score2 = get_score(ob2);	
return 1;                       	
}	
int get_score(object ob)	
{	
int score;       	
score = ob->query("xy_huiyuan");              	
return score;	
}	
int party_listener(object ppl, string str)	
{	
if( !environment(ppl)) return 0;	
if(ppl->query("xy_huiyuan")==str ) return 1;		
else return 0;	
}
int help(object me)	
{	
write(@HELP	
指令格式 : huiyuan 	
用这个指令可以查询游戏中的会员名单。  	
HELP	
);	
return 1;	
}	
