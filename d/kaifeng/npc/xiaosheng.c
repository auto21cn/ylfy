inherit NPC;
void create()
{
   	set_name("С��",({"xiao sheng", "xiao", "sheng"}));
	set("gender","Ů��");
   	set("long", "Ϸ���е�һ����ɫ��\n");
        set("age", 25);
        set("combat_exp", 7000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", 20);
}