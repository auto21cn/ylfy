// /cmds/skill/abandon.c
// lisa 2003.7.24
// 2.0 限制放弃武功前必须输入身份标识

inherit F_CLEAN_UP;
int get_biaoshi(string biaoshi,object me,string arg);
int main(object me, string arg)
{
object ob;
if( me != this_player(1) ) return 0;
ob = me->query_temp("link_ob");
if( !ob ) return 0;
while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");
	if( !arg || arg=="" ) return notify_fail("你要放弃哪一项技能？\n");
	if (!(me->query_skill(arg,1) + me->query_skill_learn(arg)))
		return notify_fail("你并没有学过这项技能。\n");
write("请输入你的身份标识：");
input_to("get_biaoshi", 1,ob,arg);
return 1;
}
int get_biaoshi(string biaoshi,object ob,string arg)
{
object me=this_player();
string old_biaoshi;
write("\n");
old_biaoshi=ob->query("biaoshiold");
if( crypt(biaoshi, old_biaoshi)!=old_biaoshi) 
{
	write("身份标识错误！\n");
	return 0;
}
if( !me->delete_skill(arg) )
return notify_fail("你没有学过这项技能。\n");
write("你决定放弃继续学习" + to_chinese(arg) + "。\n");
me->reset_action();
return 1;
}
int help()
{
	write(@TEXT
指令格式：abandon <技能名称>
放弃一项你所学过的技能，注意这里所说的「放弃」是指将这项技能从你人物
的资料中删除，如果你以后还要练，必须从０开始重练，请务必考虑清楚。
这个指令使用的场合通常是用来删除一些「不小心」练出来的技能，由于每个
人有着不同的天赋，所修习的武功也不会相同。如果样样都学，到头来只会样
样不精。
TEXT
	);
	return 1;
}
