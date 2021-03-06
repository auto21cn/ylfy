inherit ITEM;

#define COUNT  41

string query_long()
{
        int i;
        string arg=HIR+"                        银杏酒楼菜谱：\n\n\t"+NOR,cai;
        for (i=1;i<COUNT;i++){
                cai=sprintf("/d/city3/obj/caipu/cai%d.c",i);
                arg=arg+sprintf(HIY+"%2d"+NOR+": %-20s%s",i,cai->name(),i%3?"":"\n\t");
        }
        return arg+"\n\t大特价：每样酒菜只收黄金一两。\n\n\t点菜可用：dian 1 2 3 4 5 6...或all";
}

void create()
{
        string long=query_long();
        set_name("菜谱",({"cai pu","cai dan","pu"}));
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("long",long);
            set("unit","本");
            set("value", 0);
        }
}
void init()
{
        if (base_name(environment(this_player()))!="/d/city3/jiulou2")
        return 0;
        if (environment(this_object())!=this_player())
        return 0;
        add_action("do_dian", "dian");
        call_out("do_shang",10);
}
int do_dian(string arg)
{
        int i;
        string cai;
        object xiaoer;
        if (!arg)  return notify_fail("你要点第几个菜？\n");
        xiaoer=present("xiao gouzi",environment(this_player()));
        if (!xiaoer)    return notify_fail("你要先叫小二上来才能点菜。\n");
        if (arg=="all"){
                if (!this_player()->can_afford(COUNT*10000))
                        return notify_fail("你身上没那么多钱。\n");
                this_player()->pay_money(COUNT*10000);
                        arg="点";
                for (i=1;i<COUNT;i++){
                        this_player()->add_temp("dian/"+i,1);
                        cai=sprintf("/d/city3/obj/caipu/cai%d.c",i);
                        arg=arg+sprintf("%s一%s%s",cai->name(),cai->query("unit"),i%3?"\t":"\n");
                }
        }else   if (sscanf(arg,"%d",i)){
                        if (i<1 || i>=COUNT)
                                return notify_fail("你要点什么菜？\n");
                        if (!this_player()->can_afford(10000))
                                return notify_fail("你身上没那么多钱。\n");
                        this_player()->pay_money(10000);
                        cai=sprintf("/d/city3/obj/caipu/cai%d.c",i);
                                this_player()->add_temp("dian/"+i,1);
                                arg="点"+sprintf("%s一%s。\n",cai->name(),cai->query("unit"));
                        }else
                                return notify_fail("你要点什么菜？\n");
        
        message_vision("$N高声叫道："+arg+"\n",xiaoer);

        return 1;
}
int query_dian(string arg)
{
        string cai,*cais;
        mapping caipu;
        int i;
        if (!arg)  return notify_fail("你要查第几个菜？\n");
        caipu=this_player()->query_temp("dian");
        if (!sizeof(caipu))  return notify_fail("你还没有点菜！\n");
        cais=keys(caipu);
        if (arg=="all"){
                arg="\t\t你目前点了以下几个菜：\n";
                for (i=0;i<sizeof(cais);i++){
                cai=sprintf("/d/city3/obj/caipu/cai%d.c",cais[i]);
                arg=arg+sprintf("%-20s%d%s%s",cai->name(),caipu[cais[i]],cai->query("unit"),i%3?"":"\n\t");
                }
        }else   if (sscanf(arg,"%d",i)){
                arg="\t\t你目前点了以下几个菜：\n";
                if (i<1 || i>=COUNT)
                      return notify_fail("你要点什么菜？\n");
                cai=sprintf("/d/city3/obj/caipu/cai%d.c",i);
                arg=arg+sprintf("%-20s%d%s\n",cai->name(),caipu[sprintf("%d",i)],cai->query("unit"));
        }
        write(arg);
        return 1;
}

void do_shang()
{
        object player,ob,table;
        mapping dian;
        string *cais;
        string cai;

        if (!environment()) return;
        player=(environment());
        if (!interactive(player))  return;
        if (base_name(environment(player))!="/d/city3/jiulou2"){
                destruct(this_object());
                return;
        }
        table=present("table",environment(player));
        if (!table) return;

        dian=player->query_temp("dian");
        if (!sizeof(dian)){
                call_out("do_shang",100);
                return;
        }
        cais=keys(dian);
        cai=sprintf("/d/city3/obj/caipu/cai%s.c",cais[0]);
        ob=new(cai);
        message("vision","一个小伙计手端菜盆，走了上来。\n\n“来了！来了！"+ob->name()+"一"+ob->query("unit")+"！”\n",environment(player));
        if (!ob->move(table)){
                message("vision","小二陪着笑脸：“客官点的菜已经放不下了。”\n小二哼着小曲，手端"+ob->name()+"下楼去了。\n",environment(player));
                destruct(ob);
                player->delete_temp("dian");
                return;
        }
        message("vision","小伙计把菜往桌上一放，转身下楼去了。\n",environment(player));
        if (dian[cais[0]]==1){
                map_delete(dian,cais[0]);
        }
      else  player->add_temp("dian/"+cais[0],-1);
        call_out("do_shang",40);
}

