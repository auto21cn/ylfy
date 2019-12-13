//yuren.c
inherit NPC;
void create()
{
    set_name(HIW "����" NOR, ({"yu ren"}));
    set("gender", "����");
    set("age", 42);
    set("per", 18);
    set("long", 
        "��һ�ź�����Ĺ��������������������������\n");
    set("attitude", "peaceful");
    
    set("str", 251);
    set("int", 80);
    set("con", 86);
    set("dex", 140);
    set("chat_chance", 5);

    set("qi", 2000);
    set("max_qi", 2000);
    set("jing", 2000);
    set("max_jing", 2000);
    set("max_jingli", 1000);

    set("jingli", 1000);
    set("neili", 10000);
    set("max_neili", 1000);
    set("jiali", 300);
    
    set("combat_exp", 400000);
     
    set_skill("force", 200);             // �����ڹ�
    set_skill("tianshan-zhang", 200);
    set_skill("yiyang-zhi", 200);
    set_skill("yunlong-shengong", 200);
    set_skill("yunlong-shenfa", 200);
    set_skill("staff", 200);
    set_skill("unarmed", 200);           // ����ȭ��
    set_skill("dodge", 200);             // ��������
    set_skill("parry", 200);             // �����м�
    
    map_skill("force"  , "yunlong-shengong");
    map_skill("unarmed", "yiyang-zhi");
    map_skill("dodge"  , "yunlong-shenfa");
    map_skill("parry"  , "tianshan-zhang");
    map_skill("staff"  , "tianshan-zhang");
    
    setup();
    carry_object("/clone/cloth/cloth")->wear();
    carry_object("/clone/weapon/gangjiang")->wield();   
}

void die()
{
        object killer;
        if( objectp(killer = query_temp("last_damage_from")) )
                 killer->add_temp("kill_shi",1);
           ::die();
}
