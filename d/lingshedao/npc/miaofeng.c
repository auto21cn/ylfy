//NPC: /d/lingshedao/npc/huiyue.c
//Creat by Yjss on Sep.1999
#include "ansi.h"
inherit NPC;
inherit F_UNIQUE;
void create()
{
        set_name("���ʹ", ({"miao feng", "miao",}));
        set("long",
        "���˻���ӥ��,������������.\n"
        );
        set("nickname",MAG"��˹�����̻ܽ���ʹ��" NOR);
        set("gender", "����");
        set("attitude", "peaceful");
        set("age", 30);
        set("shen_type",-1);
        set("per", 18);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 2000);
        set("max_jing", 1200);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 60);
        set("combat_exp", 1500000);
        set("score",30000);

        set_skill("force", 380);
        set_skill("dodge", 380);
        set_skill("sword", 380);
        set_skill("parry", 380);
        set_skill("qiankundanuoyi", 390);
        set_skill("shenghuo-shengong", 380);
        set_skill("shenghuo-ling",385);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "qiankundanuoyi");
        map_skill("parry", "qiankundanuoyi");
        map_skill("sword", "shenghuo-ling");       
        
        setup();
        carry_object("/d/mingjiao/obj/baipao")->wear();
        carry_object("/d/lingshedao/obj/shenghuo-ling")->wield();
        
}

void init()
{
  object ob=this_player();
  if(interactive(ob) && ob->query("party/party_name")== HIG "����" NOR)
  message_vision(HIC"���ʹ����Ŀ���$N.\n"NOR,ob);
}
