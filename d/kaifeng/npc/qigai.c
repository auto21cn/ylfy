inherit NPC;

void create()
{
        set_name("��ؤ",({"qi gai", "qi", "gai"}));
        set("gender", "����");
        set("age",25);
        set("combat_exp", 7000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}