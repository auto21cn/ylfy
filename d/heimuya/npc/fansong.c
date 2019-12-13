// fansong.c
#include <ansi.h>
inherit NPC;

void create()
{
    set_name("����", ({"fan song", "fan", "song"}));
    set("nickname", HIW "������ħ" NOR );
    set("title", "������̳���");
    set("gender", "����");
    set("age", 42);
    set("shen_type", -1);
    set("long",
        "����������̳��ϡ�\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);

    set_skill("force", 150);
    set_skill("kuihua-xinfa", 150);
    set_skill("unarmed", 150);
    set_skill("changquan", 150);
    set_skill("dodge", 150);
    set_skill("lingxu-bu", 150);
    set_skill("parry", 150);
    set_skill("axe", 150);
    set_skill("duanyun-fu", 150);

    map_skill("force", "kuihua-xinfa");
    map_skill("axe", "duanyun-fu");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "lingxu-bu");
    map_skill("parry", "duanyun-fu");

    create_family("�������", 2, "����");

    setup();
    carry_object(__DIR__"obj/dafu")->wield();
    carry_object("/clone/cloth/cloth")->wear();
}
void attempt_apprentice(object ob)
{
    if (ob->query_int() < 25) {
        command("say �Ҳ������ʲ�ĵ��ӣ�����ذɣ�\n");
                return;
    }

    if ((int)ob->query("shen") >100000 || (int)ob->query ("shen") < -100000 ) {
        command("say �Һ�ľ�������������������������ֳ�������򽻵�������ذɣ�;\n");
                return;
        }
    command("say �ܺã��ܺá�\n");
    command("recruit " + ob->query("id"));
}
