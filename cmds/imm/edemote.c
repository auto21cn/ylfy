// edemote.c
// write by Fan 1997-12-21
inherit F_CLEAN_UP;
#include <ansi.h>
int in_use;
string emote_more()
{
	mapping emote;
	string *str,arg="";
	int i;		
	str=sort_array(EMOTE_D->query_all_emote(), 1);
	for (i=0;i<sizeof(str);i++){
	emote = EMOTE_D->query_emote(str[i]);
	arg+=sprintf(RED+"%s"+NOR+"上次修改：%s\n",str[i], emote["updated"]);
	arg+=sprintf("—————————————\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		emote["myself"], emote["others"], emote["myself_self"],
		emote["others_self"], emote["myself_target"], emote["target"],
		emote["others_target"] );
	}
	return arg;
}
int main(object me, string arg)
{
        mapping emote,emote1;
        if( !arg ) return notify_fail("你要编辑什么 emote？\n");
	if (arg=="all"){
		me->start_more(emote_more());
		return 1;
	}
        if( sscanf(arg, "-d %s", arg) ) {
                write("删除 emote：" + arg + "\n");
                EMOTE_D->delete_emote(arg);
                return 1;
        }
        if( sscanf(arg, "-p %s", arg) ) {
                emote = EMOTE_D->query_emote(arg);
                printf("上次修改：%s\n", emote["updated"]);
                printf("—————————————\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                        emote["myself"], emote["others"], emote["myself_self"],
                        emote["others_self"], emote["myself_target"], emote["target"],
                        emote["others_target"] );
                return 1;
        }
	emote1= EMOTE_D->query_emote(arg);
        emote = EMOTE_D->query_emote(arg);
        emote = (["updated":geteuid(me)]);
        write("编辑 emote：" + arg + "\n");
        write("讯息可以有好几行，用 . 表示结束。\n");
        write("讯息中可使用的参数有以下几种：\n");
        write("  $N  自己的名字。     自己的中文名字。\n");
        write("  $n  使用对象的名字。 对象的中文名字。\n");
        write("  $p  使用对象的人称代名词，如你、你、他、她、它、它。\n");
        write("  $S  对自己的称呼。   如在下、老纳、小女子、贫僧等。\n");
        write("  $s  对自己的粗鲁称呼。如本姑娘、老娘、大爷我、老子。\n");
        write("  $C  对自己的呢称。如愚兄我、小弟我、姐姐我、小妹我。\n");
        write("  $c  对别人的呢称。如哥哥、弟弟、姐姐、妹妹\n");
        write("  $R  对别人的尊称。如仙姑、小姑娘、壮士、大师。\n");
        write("  $r  对别人的粗鲁称呼。如死牛鼻子、死秃驴、臭贼、小贱人。\n");
        write("————————————————————————————————————\n");
        write("不指定对象使用这个 emote 时，其他人看到的讯息：\n->");
        write(emote1["others"]+"->");
        input_to("get_msg_others", emote,emote1, arg);
        return 1;
}
int get_msg_others(string msg, mapping emote, mapping emote1,string pattern)
{
        if (msg==".") {
		if (undefinedp(emote["others"]) && !undefinedp(emote1["others"])) 
			emote["others"]=replace_string(emote1["others"],"$P","$N");
		else
                if( !undefinedp(emote["others"]) ) emote["others"] =replace_string(emote["others"],"$P","$N")+ "\n";
                write("对自己使用这个 emote 时，其他人看到的讯息：\n->");
	        write(emote1["others_self"]+"->");
                input_to("get_msg_others_self", emote,emote1, pattern);
                return 1;
        }
        if( !undefinedp(emote["others"]) )
                emote["others"] += msg + "\n";
        else emote["others"] = msg;
        write("->");
        input_to("get_msg_others", emote,emote1, pattern);
        return 1;
}
int get_msg_others_self(string msg, mapping emote, mapping emote1,string pattern)
{
        if (msg==".") {
		if (undefinedp(emote["others_self"])&& !undefinedp(emote1["others_self"])) 
                        emote["others_self"]=replace_string(emote1["others_self"],"$n","$p");
		else
                if( !undefinedp(emote["others_self"]) ) emote["others_self"] = replace_string(emote["others_self"],"$n","$p")+ "\n";
                write("对别人使用这个 emote 时，使用对象看到的讯息：\n->");
	        write(emote1["target"]+"->");
                input_to("get_msg_target", emote,emote1, pattern);
                return 1;
        }
        if( !undefinedp(emote["others_self"]) )
                emote["others_self"] += msg + "\n";
        else emote["others_self"] = msg;
        write("->");
        input_to("get_msg_others_self", emote,emote1, pattern);
        return 1;
}
int get_msg_target(string msg, mapping emote, mapping emote1,string pattern)
{
        if (msg==".") {
		if (undefinedp(emote["target"])&& !undefinedp(emote1["target"])) 
                        emote["target"]=replace_string(emote1["target"],"$n","$p");
		else
                if( !undefinedp(emote["target"]) ) emote["target"] = replace_string(emote["target"],"$n","$n")+ "\n";
                write("对别人使用这个 emote 时，除你自己和使用对象外，其他人看到的讯息：\n->");
	        write(emote1["others_target"]+"->");
                input_to("get_msg_others_target", emote,emote1, pattern);
                return 1;
        }
        if( !undefinedp(emote["target"]) )
                emote["target"] += msg + "\n";
        else emote["target"] = msg;
        write("->");
        input_to("get_msg_target", emote,emote1, pattern);
        return 1;
}
int get_msg_others_target(string msg, mapping emote, mapping emote1,string pattern)
{
		string emote_str;
        if (msg==".") {
		if (undefinedp(emote["others_target"])&& !undefinedp(emote1["others_target"])) 
			emote["others_target"]=emote1["others_target"];
		else
                if( !undefinedp(emote["others_target"]) ) emote["others_target"] += "\n";
                if( !undefinedp(emote["others"]) ) emote["myself"]=replace_string(emote["others"],"$N","$P");
                if( !undefinedp(emote["others_self"]) ){
					emote_str=emote["others_self"];
					emote_str=replace_string(emote_str,"$N","$P");
					emote["myself_self"]=emote_str;
		}
                if( !undefinedp(emote["target"]) ){
			emote_str=replace_string(emote["target"],"$N","$P");
			emote_str=replace_string(emote_str,"$p","$n");
			emote["myself_target"]=emote_str;
		}
                EMOTE_D->set_emote(pattern, emote);
                write("Emote 编辑结束。\n");
                return 1;
        }
        if( !undefinedp(emote["others_target"]) )
                emote["others_target"] += msg + "\n";
        else emote["others_target"] = msg;
        write("->");
        input_to("get_msg_others_target", emote,emote1, pattern);
        return 1;
}
int help(object me)
{
write(@HELP
指令格式 : edemote [-d|-p] <emote>
 
这个指令可以修改, 删除 emote 或列出其内容. 加上 -d 参数会删除
指定的 emote, -p 参数则会列出指定 emote 的内容. 列出的顺序与编
辑 emote 时相同.
 
输入 emote 讯息时有三个项目: 没有目标, 指定目标或是对自己. 若
不想有某项讯息, 则直接在空白行输入 '.' 跳过.
 
一个 emote 讯息可以有很多行, 在空白行输入 '.' 结束输入该项 emote.
 
编辑 emote 时可以用以下的符号来表示:
 
$N : 自己的名字.
$n : 目标的名字.
$P : 自己的人称代名词.
$p : 目标的人称代名词.
$S : 对自己的称呼。
$s : 对自己的粗鲁称呼。
$C : 对自己的呢称。
$c : 对别人的呢称。
$R : 对别人的尊称。
$r : 对别人的粗鲁称呼。
HELP
    );
    return 1;
}
