//ju-e.c
inherit NPC;
void create()
{
        set_name("巨鳄", ({ "ju e", "e" }) );
        set("race", "野兽");
        set("age", 200000);
        set("long", "一只庞然大物，它眼中喷火,好象要一口把你吞下。\n");
        set("attitude", "aggressive");
        set("no_chang", 1);
        set("qi", 40000);
        set("max_qi", 40000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("max_neili", 20000);
        set("jiali",2000);
        set("neili",2000000);
        set ("max_jingli",20000);
        set ("jingli",200000);
        set("str", 860);
        set("dex", 580);
        set("int",3000);
        set("con",50000);
        set_skill("dodge", 5000);
        set_skill("parry", 5000);
        set("limbs", ({ "头部", "爪子","后脚","身体", "尾巴" }) );
        set("verbs", ({ "bite","hoof","claw","knock"}) );

        set("combat_exp", 10000000);
        set("chat_chance", 3);
        set("chat_msg", ({
        (: random_move :)
        }) );
        set_temp("apply/attack", 850);
        set("apply/dodge", 800);
        set_temp("apply/damage", 800);
        set_temp("apply/armor", 20000);
        set_temp("apply/defence",800);
        setup();
}

void die()
{
        object ob;
        message_vision("$N惨嚎一声，死了！\n", this_object());
        ob = new(__DIR__"obj/epi");
        ob->move(environment(this_object()));
        destruct(this_object());
}

