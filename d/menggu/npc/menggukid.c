inherit NPC;
void create()
{
   set_name("�ɹ�С��",({"kid"}));
   set("age",9);
   set("combat_exp",200);
   set_skill("dodge",10);
   set_skill("unarmed",3);
   set("chat_chance",7);
   set("chat_msg",({
   (:random_move:),
   }));
   setup();
 carry_object("clone/cloth/cloth")->wear();
 add_money("coin",20);
}