// scavenger.c
inherit NPC;
void get_all();
void create()
{
	set_name("拾荒者", ({ "walker" }));
	set("gender", "男性");
	set("age", 53 + random(20));
	set("long", @LONG
这是一个年迈的拾荒者，看上去老实巴交的。
LONG );
	set("attitude", "heroism");
	set("str", 35);
	set("int", 15);
	set("con", 19);
	set("dex", 17);

	set("chat_chance", 30);
	set("chat_msg", ({
		"拾荒者抬头望了望天，摇了摇头，叹了口气，\n",
                (: get_all :),
                (: random_move :),
	}) );
	setup();
	carry_object("/clone/cloth/cloth")->wear();
	add_money("coin", 5);
}
int accept_object(object me, object obj)
{
	if (userp(obj)){
		command("fear "+me->query("id"));
		return 0;
	}
	command("smile");
	command("say 多谢这位" + RANK_D->query_respect(me) + "！");
	return 1;
}
int accept_fight(object me)
{
	command("say " + RANK_D->query_respect(me) + "饶命！小的这就离开！\n");
	return 0;
}
void get_all()
{

      int i=0;
     if (base_name(environment())=="/d/city/guangchang")
          command("climb up");
     else if (base_name(environment())=="/d/city/chatroom")
          command("tiao down");
        if (is_fighting() || is_busy() ) return;
         foreach (object ob in all_inventory(environment())){
                if( ob->is_character()) continue;
				if(ob->query("board_id")) continue;	
				if(ob->query("no_get")) continue;	
                if( ob->move(this_object()) ) {
                 i++;
                message_vision("$N捡起一"+ob->query("unit")+ob->name()+"。\n",this_object());
                 destruct(ob);
                }
       }
     if (i)      command("smile scavenger");
}
