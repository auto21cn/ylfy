// xifang.c
#include <ansi.h>
inherit NPC;
void consider();
void create()
{
    set_name("西方失败", ({"xifang shibai", "xifang"}));
    set("nickname", HIY "天下无敌" NOR );
    set("gender", "女性");
    set("age", 42);
    set("long",
        "她就是日月神教教主。号称无人可敌，因此有一称号为「西方失败」。\n");
    set("attitude", "peaceful");
    set("str", 31);
    set("int", 10);
    set("con", 26);
    set("dex", 200);
    set("chat_chance", 1);
    set("chat_msg", ({
 "西方失败叹了口气道：“唉 …… 那东方不败是谁呀，你们烦不烦啊！\n",
        }));
    set("qi", 1000);
    set("max_qi", 1000);
    set("jing", 500);
    set("max_jing", 500);
    set("jingli", 1000);
    set("max_jingli", 1000);
    set("neili", 50000);
    set("max_neili", 5000);
    set("jiali", 20);
    set("combat_exp", 12500000);

    set_skill("force", 500);             // 基本内功
    set_skill("unarmed", 500);
    set_skill("throwing", 500);
    set_skill("mantianhuayu", 500);
    set_skill("tanzhi-shentong", 500);   // 弹指神通
    set_skill("dodge", 500);             // 基本躲闪
    set_skill("parry", 500);             // 基本招架
    set_skill("sword", 500);             // 基本剑法
    set_skill("pixie-jian", 450);        // PiXieJian
    set_skill("qimen-wuxing",400);       // 奇门五行
    set_skill("literate",1000);           // 读书识字
    set_skill("kuihua-xinfa", 100);       // 葵花心法
    map_skill("force"  , "kuihua-xinfa");
    map_skill("throwing"  , "mantianhuayu");
    map_skill("sword", "pixie-jian");
    map_skill("unarmed" , "tanzhi-shentong");
    map_skill("dodge"  , "pixie-jian");
    map_skill("parry"  , "pixie-jian");
   set_temp("apply/shade_vision",1);
    create_family("日月神教", 2, "教主");
    set("chat_msg_combat", ({
    (: exert_function, "protect" :),
    (: exert_function, "recover" :),
    }) );

    setup();
    carry_object(__DIR__"obj/zhen")->wield();
    carry_object(__DIR__"obj/kuihuazhen")->wield();
    carry_object(__DIR__"obj/hongchouxiaoshan")->wear();
}

