// marry 8,14

inherit NPC;

void create()
{
        set_name("仆人", ({ "pu ren","ren","pu" }) );
        set("gender", "男性" );
        set("age", 30);
        set("jihao", 1);
        set("long", "一个表情呆板的仆人,正在大院中打扫落叶。\n");
        set("combat_exp", 3000);
        set("str", 17);
        set("dex", 16);
        set("con", 18);
        set("int", 20);
        set("attitude", "peaceful");
        set("max_qi", 150);
        set("max_jing", 150);

        set_skill("force", 15);
        set_skill("dodge", 15);
        set_skill("unarmed", 15);
        set_skill("parry", 15);


        setup();
        carry_object("/d/cxwxm/obj/cloth2.c")->wear();

}

