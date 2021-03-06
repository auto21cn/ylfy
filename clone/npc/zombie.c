// zombie.c
#include <ansi.h>

inherit NPC;

void do_bite();
int do_drive(string arg);

void create()
{
    set_name("僵尸", ({ "zombie" }) );
    set("long","这是一具被人用符咒控制(drive)的僵尸，从它苍白的脸上看不出任何喜怒哀乐。\n");
    set("max_jing", 400);
    set("max_qi", 400);
    set("max_jingli", 100);
    set("jingli", 100);

    set("no_suck",1);
	set("no_put", 1);
    set("no_die",1);
    set("demogorgon",1);


    set("max_neili", 100);
    set("neili", 100);
    set("str", 60);
    set("int", 40);
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
                "僵尸口中发出荷荷的叫声。\n",
                "僵尸的脸上开始痉挛，一阵抽搐，发狂似地大叫。\n",
                "僵尸五指箕张，咬牙切齿，露出狰狞的笑容。\n",
                (: do_bite :),
    }) );
    set_skill("unarmed", 30);
    set_skill("dodge", 30);

    set_temp("apply/damage", 15);

    setup();
}

int is_zombie() { return 1; }
void init()
{
    ::init();
    add_action("do_drive","drive");
    set_heart_beat(1);

}

void animate(object who, int value)
{
    mapping skill_status,hp_status;
    string *sname,name,skill1,skill2;
    int i,level;
    object weapon,me=this_object();
    set("possessed", who);
    set_leader(who);
    name=query("victim_name");
    name=replace_string(name,"的僵尸","");
//        set("name",name+"的僵尸");	
    set("name",who->query("name")+"〓"+name+"的僵尸");	
    if ( mapp(skill_status = who->query_skills()) ) {
        sname  = keys(skill_status);
        for(i=0; i<sizeof(skill_status); i++) {
            level = skill_status[sname[i]]*value/50;
            if (level)
//               me->set_skill(sname[i], skill_status[sname[i]]*value/50);	
        me->set_skill(sname[i], skill_status[sname[i]]/2);	
        }
    }
    if (objectp(weapon=me->query_temp("weapon"))){
            skill1=weapon->query("skill_type");
            if (objectp(weapon=me->query_temp("secondaly_weapon")))
                    skill2=weapon->query("skill_type");
        }
    if ( mapp(skill_status = me->query_skills()) ) {
        sname  = keys(skill_status);
        for(i=0; i<sizeof(skill_status); i++) {
            command("enable unarmed "+sname[i]);
            command("enable force "+sname[i]);
            command("enable parry "+sname[i]);
            command("enable dodge "+sname[i]);
                        if (stringp(skill1))
            command("enable "+skill1+" "+sname[i]);
                        if (stringp(skill2))
            command("enable "+skill2+" "+sname[i]);
        }
    }

    hp_status = who->query_entire_dbase();

        me->set("str", hp_status["str"]);
        me->set("int", hp_status["int"]);
        me->set("con", hp_status["con"]);
        me->set("dex", hp_status["dex"]);
        me->set("per",7);
        me->set("max_qi",    hp_status["max_qi"]/10);
        me->set("eff_qi",    hp_status["eff_qi"]/10);
        me->set("qi",        hp_status["qi"]/10);
        me->set("max_jing",  hp_status["max_jing"]/10);
        me->set("eff_jing",  hp_status["eff_jing"]/10);
        me->set("jing",      hp_status["jing"]/10);
        me->set("max_neili", hp_status["max_neili"]/10);
        me->set("max_jingli",hp_status["max_jingli"]/10);
        me->set("jingli",    hp_status["max_jingli"]/10);
        me->set("neili",     hp_status["max_neili"]/5);
        me->set("gender",    hp_status["gender"]);
//       me->set("combat_exp",(hp_status["combat_exp"]/50)*value);	
me->set("combat_exp",(hp_status["combat_exp"]/2));	
        command("enforce max");
}

void dispell()
{
        if( environment() ) {
                tell_room(environment(),name() + "缓缓地倒了下来，化为一滩血水。\n");
        }

        destruct(this_object());
}
void die()
{
    dispell();
}

int heal_up()
{
        object master;
        if (!environment()){
            destruct(this_object());
            return 1;
        }
        if( objectp(master = query("possessed")) 
        &&  (int)master->query("jingli") > 50
        &&  (int)master->query("jing") > 30
        &&  living(master)) {
                if (living(this_object()) && !is_fighting())
                    tell_object(master, HIR + name() + "告诉你：我...需...要...你...的...力...量...\n" NOR );
                master->add("jingli", -10);
                master->receive_damage("jing", 3);
                    set_leader(master);
                ::heal_up();
                return 1;               // Always acquire power from master.
        } else {
                call_out("dispell", 1);
                return ::heal_up();
        } 
}

void do_bite()
{
        object *enemy;

        say( HIB + name() + "口中喷出一股令人欲呕的臭气，使你觉得头晕脑胀。\n"+NOR );
        enemy = all_inventory(environment());
        for(int i=0; i<sizeof(enemy); i++) {
                if( !enemy[i] ) continue;
                if( enemy[i]==this_object() ) continue;
                if( !enemy[i]->is_character() || enemy[i]->is_corpse() || enemy[i]->is_zombie())   continue;
                if (!living(enemy[i])) continue;
                enemy[i]->receive_damage("jing", query("jing")/50+10);
                COMBAT_D->report_status(enemy[i], 0);
        }
}
object find_player(string target)
{
    int i;
    object *str;
    str=users();
    for (i=0;i<sizeof(str);i++)
        if (str[i]->query("id")==target)
            return str[i];
    return 0;
}
 
int do_drive(string str)
{
    object ob,me=this_object();
    object master=query("possessed");
    
    if( !objectp(master) || master!=this_player()) return 0;
    if (!living(me) || is_fighting())  return notify_fail("你现在不能驱动"+name()+"．\n");
    if( (int)this_player()->query("jingli") < 100 ) return notify_fail("你的精力不够了！\n");
//       ob = LOGIN_D->find_body(str);	
ob = find_player(str);  	
    if (!ob) ob=present(str,environment());
//       if (!ob) ob=find_player(str);	
    if (!ob) ob=find_living(str);
    if (!ob || !environment(ob) || !this_player()->visible(ob)) return notify_fail("咦... 有这个人吗?\n");
if (environment(ob)->query("fight_room") || environment(ob)->query("no_fight"))  return notify_fail(me->name()+"似乎不明白你的意思!\n");	
if ( ob->query("age",1) < 18 )
return notify_fail(me->name()+"似乎不太愿意去欺负小孩子!\n");     	
if ( ob->is_ghost() )	
return notify_fail(ob->query("name")+"已经是个死人了!\n");     
if(ob->query_temp("apply/name") && userp(ob)) 
return notify_fail(me->name()+"似乎找不到"+ob->query("name")+"的踪迹！\n");
if(domain_file(base_name(environment(ob)))=="party" || domain_file(base_name(environment(ob)))=="new")
	return notify_fail(ob->query("name")+"似乎在一个无法到达的地方！\n");  
    if ( me==ob){
        animate(this_player(), 120);
        ob=this_player();
    }
    if( environment(ob)==environment(me) ) {
        message_vision("$N眼睛忽然睁开，喃喃地说道：" RED "杀....死....$n....\n" NOR,me, ob);
    } else {
        message_vision("$N眼睛忽然睁开，喃喃地说道：" RED "杀....杀....杀....\n" NOR, me);
        message_vision("$N一蹦一蹦地跳开了！\n" NOR, me);
        me->move(environment(ob));
write_file("/log/static/zombie",sprintf("%s   驱僵尸去杀   %s on %s\n", this_player()->query("name"),ob->query("name"), ctime(time()) ));	
        message_vision("$N一蹦一蹦地跳了过来！\n" NOR, me);
    }
    me->kill_ob(ob);
    me->set_leader(ob);
    ob->kill_ob(me);
    this_player()->add("jingli",-100);
    return 1;
}
void killed_enemy(object obj)
{
    delete("attack");
}

