// semote.c
//#include "/doc/help.h"

inherit F_CLEAN_UP;
string replace_str(object me,string str)
{
        str = replace_string(str, "$N", me->name(1));
        str = replace_string(str, "$P", "你");
        str = replace_string(str, "$S", RANK_D->query_self(me));
        str = replace_string(str, "$s", RANK_D->query_self_rude(me));
        str = replace_string(str, "$C", "愚兄我");
        str = replace_string(str, "$c", "哥哥");
        str = replace_string(str, "$R", "壮士");
        str = replace_string(str, "$r", "臭贼");
        str = replace_string(str, "$n", "某人");
        str = replace_string(str, "$p", "他");
        return str;
}
string replace_str1(object me,string str)
{
        str = replace_string(str, "$N", me->name(1));
        str = replace_string(str, "$P", "他");
        str = replace_string(str, "$S", RANK_D->query_self(me));
        str = replace_string(str, "$s", RANK_D->query_self_rude(me));
        str = replace_string(str, "$C", "愚兄我");
        str = replace_string(str, "$c", "哥哥");
        str = replace_string(str, "$R", "壮士");
        str = replace_string(str, "$r", "臭贼");
        str = replace_string(str, "$n", "某人");
        str = replace_string(str, "$p", "你");
        return str;
}
void more(string cmd,string emote_str, int line)
{
        mapping emote;
        string *e,str;
        object me;
        int i;
        me=this_player();
        e = sort_array(EMOTE_D->query_all_emote(), 1);
        switch(cmd) {
        case "b":
        write(ESC+"[2A"+ESC+"[200D"+ESC+"[K");
        line = line - 30;
        if(line<0) line=0;
                for(i=line+15;line<sizeof(e) && line<i; line++){
                emote = EMOTE_D->query_emote(e[line]);
                if (stringp(str=emote[emote_str])){
                        str=replace_str(me,str);
                        write(RED+e[line]+NOR+"\n"+str);
                }
                }
                break;
                case "q":       write("结束！\n");
                        return;
        default:
                write(ESC+"[2A"+ESC+"[200D"+ESC+"[K");
                for(i=line+15;line<sizeof(e) && line<i; line++){
                emote = EMOTE_D->query_emote(e[line]);
                if (stringp(str=emote[emote_str])){
                        str=replace_str(me,str);
                        write(RED+e[line]+NOR+"\n"+str);
                }
                }
                if( line>=sizeof(e) ){  write("结束！\n"); return;}
                break;
        }
        printf(YEL"== 未完继续 " NOR BOLD "%d%%"NOR YEL " == (q 离开，b 前一页 其他继续下一页)\n"NOR,
                (line*100/sizeof(e)) );
        input_to("more", emote_str, line);
}
int main(object me, string arg)
{
        mapping emote;
        string *e,str,emote_str;
        int i;
        e = sort_array(EMOTE_D->query_all_emote(), 1);
        if (!arg){
                str = NOR"                       "+BRED+HIY"[夕阳再现]"HIG" 表情动作总汇\n\n"NOR;
	       	str += "—————————————————————————————————————\n";
                for(i=0; i<sizeof(e); i++)
                        str += sprintf("%-15s%s", e[i], (i%5==4)?"\n": "");
	                me->start_more(str);
                write("\n");
                return 1;
        }
        switch(arg){
                case "1":emote_str="myself";break;
                case "2":emote_str="others";break;
                case "3":emote_str="myself_self";break;
                case "4":emote_str="others_self";break;
                case "5":emote_str="myself_target";break;
                case "6":emote_str="target";break;
                case "7":emote_str="others_target";break;
                default:
                        emote = EMOTE_D->query_emote(arg);
                        if (!sizeof(emote))     return 
notify_fail("没有这个emote。\n");
                        if (stringp(str=emote["myself"]))
                                printf("不指定对象使用这个 emote 
时，你自己看到的讯息:\n"+BOLD+replace_str(me,str)+"\n"+NOR);
                        if (stringp(str=emote["others"]))
                                printf("不指定对象使用这个 emote 
时，其他人看到的讯息:\n"+BOLD+replace_str1(me,str)+"\n"+NOR);
                        if (stringp(str=emote["myself_self"]))
                                printf("对自己使用这个 emote 
时，自己看到的讯息:\n"+BOLD+replace_str(me,str)+"\n"+NOR);
                        if (stringp(str=emote["others_self"]))
                                printf("对自己使用这个 emote 
时，其他人看到的讯息:\n"+BOLD+replace_str1(me,str)+"\n"+NOR);
                        if (stringp(str=emote["myself_target"]))
                                printf("对别人使用这个 emote 
时，自己看到的讯息:\n"+BOLD+replace_str(me,str)+"\n"+NOR);
                        if (stringp(str=emote["target"]))
                                printf("对别人使用这个 emote 
时，使用对象看到的讯息:\n"+BOLD+replace_str1(me,str)+"\n"+NOR);
                        if (stringp(str=emote["others_target"]))
                                printf("对别人使用这个 emote 
时，除你自己和使用对象外，其他人看到的讯息:\n"+BOLD+replace_str
(me,str)+"\n"+NOR);
                return 1;
        }
        more("",emote_str,0);
        return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : semote <参数> || <emote>
这个指令可以列出目前所能使用的emote和emote的详细解析。
参数:
1:列出不指定对象使用这个 emote 时，你自己看到的讯息;
2:列出不指定对象使用这个 emote 时，其他人看到的讯息;
3:列出对自己使用这个 emote 时，自己看到的讯息;
4:列出对自己使用这个 emote 时，其他人看到的讯息;
5:列出对别人使用这个 emote 时，自己看到的讯息;
6:列出对别人使用这个 emote 时，使用对象看到的讯息;
7:列出对别人使用这个 emote 
时，除你自己和使用对象外，其他人看到的讯息。
HELP
    );
    return 1;
}

