// ----/cmds/arch/checkall.c ----
inherit F_CLEAN_UP;
int help(object me);

int busy;

int main(object me, string arg)
{
    if (busy)
                return notify_fail(HIR "整理玩家数据正在进行！\n" NOR);
//        message("system", RED"\n 整理玩家储存档，请稍候....\n" NOR, users());
    write("处理中：\n");
    rm("/log/bad_data");
    rm("/log/check_users");
    rm("/log/check_money");
    rm("/log/check_skill");
    busy=1;
        call_out("checking",2);
        return 1;
}
int checking(int i)
{
        int j;
        string *dir, *ppls, *puls, name,arg;
        object ob,obj;

        seteuid(getuid());
        dir = get_dir(DATA_DIR + "login/");
        if (!i){
            i=0;
        }
        ob=new("/clone/misc/player");
        if ( i<sizeof(dir) ){
                reset_eval_cost();
                arg=dir[i];
                write("正在整理 -= "+arg+" =-\n");
                i++;
                ppls = get_dir(DATA_DIR + "login/" + arg + "/");
                puls = get_dir(DATA_DIR + "user/" + arg + "/");
                for(j=0; j<sizeof(ppls); j++) {
                        if( sscanf(ppls[j], "%s.o", name)==1 ){
                                if( (string)SECURITY_D->get_status(name)!="(player)" ){
                                    write(BOLD+"排除巫师"+name+"\n"+NOR);
                                        continue;
                                }
                                if (file_size(DATA_DIR + "login/" + arg + "/"+ppls[j])<5 || file_size(DATA_DIR + "user/" + arg + "/"+puls[j])<5 ){
                                        log_file("bad_data",name+"\tis bad.\n");
                                        continue;
                                }
                                if (!ob->new_object(name)){
                                        log_file("bad_data",name+"\tis bad.\n");
                                        continue;
                                }
                                if (ob->query("id")!=name)
                                        log_file("bad_data",name+"\tisn't\t"+ob->query("id")+"\n");
                                  obj=present("thousand-gold",ob);
                                if (ob->query("combat_exp")>=50000000 || (int)ob->query("potential") - (int)ob->query("learned_points")>100000 || ob->query("max_neili")>150000 )
                                        log_file("check_users",sprintf("%10s(%s) 经验:%10d,潜能:%10d,内力:%10d,上线时间:%d\n",ob->name(),name,ob->query("combat_exp"),(int)ob->query("potential") - (int)ob->query("learned_points"),ob->query("max_neili"),ob->query("mud_age")/86400));
                                if (ob->query_skill("literate",1)>2600)
                                        log_file("check_skill",sprintf("%10s(%s) 讀書識字:%d,上线时间:%d\n",ob->name(),name,ob->query_skill("literate",1),ob->query("mud_age")/86400));
                                
                                
                        }
                  if  ( obj && obj->query_amount()>100)
                  log_file("check_money",sprintf("%10s(%s) 身上金票数:%d\n",ob->name(),name,obj->query_amount()));
                }
                destruct(ob);
                call_out("checking",1,i);
                return 1;
        }else{
//              message("system", BOLD"\n 整理完毕!\n" NOR, users());
                busy=0;
        }
        return 1;
}
int help(object me)
{
write(@HELP
指令格式：checkall

HELP
        );
    return 1;
}


