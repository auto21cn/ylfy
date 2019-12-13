//nai niu.c

inherit NPC;

void create()
{
        set_name("内力奶牛", ({ "nai niu", "neili nainiu" }));
        set("long", "他是夕阳客栈给玩家吸内力的大奶牛.\n");
        set("nickname", "夕阳奶牛");
        set("gender", "男性");
        set("no_fight",1);
        set("age", 20);
        set("attitude","friendly");
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("per", 30);			
        set("max_qi", 5000);
        set("max_jing", 1000);
        set("neili", 20000);
        set("max_neili", 20000);			
        setup();

}

/*void init()
{     
                add_action("do_kill","team kill");
                add_action("do_kill","touxi");
                add_action("do_kill","kill");
                add_action("do_kill","hit");
                add_action("do_kill","fight");
                add_action("do_kill","steal");
                add_action("do_kill","beg");
                add_action("do_kill","persuade");
                add_action("do_kill","perform");
                //add_action("do_kill","exert");
                add_action("do_kill","yun");
                add_action("do_kill","throw");
                add_action("do_kill","conjure");
}       

int do_kill(string arg)
{
        string what,who;
        if(!arg) return 0;
                               
        if(this_object()->id(arg))
        {
                write("这是给你吸内力的奶牛，干吗老打他？！\n");
                return 1;
        }
        else
        if(sscanf(arg,"%s from %s",what,who)==2 && this_object()->id(who))
        {
                write("这是给你吸内力的奶牛，干吗老打他？！\n");
                return 1;
        } else
        if(sscanf(arg,"%s at %s",what,who)==2 && this_object()->id(who))
        {
                write("这是给你吸内力的奶牛，干吗老打他？！\n");
                return 1;
        } else
        if(sscanf(arg,"%s on %s",what,who)==2 && this_object()->id(who))
        {
                write("这是给你吸内力的奶牛，干吗老打他？！\n");
                return 1;
        } else
        if(sscanf(arg,"%s %s",what,who)==2 && this_object()->id(who))
        {
                write("这是给你吸内力的奶牛，干吗老打他？！\n");
                return 1;
        } else
        if( arg == "roar" || arg =="hou" )
        {
                write("这是给你吸内力的奶牛，干吗老打他？！\n");
                return 1;
        }  

        return 0;
}


void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        command("heng " + ob->query("id"));
}*/

void unconcious()
{
        reincarnate();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("neili", 20000);
        set("max_neili", 20000);
        say( "内力奶牛狞笑着说：我是无敌不死版！\n");
        }

void die()
{
        unconcious();
}
