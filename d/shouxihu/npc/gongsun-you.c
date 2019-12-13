#include <ansi.h>
inherit NPC;

void create()
{ 
    set_name(HIR"公孙幽"NOR, ({"gongsun you"}) );
    set("title", HIM"江湖奇女子" NOR);
    set("gender", "女性" );
    set("age", 30);
    set("long", "孤女，生卒年不详。自幼被江湖女侠聂隐娘收养，授其武功。成年后行走江湖，称公孙大娘，创建忆盈楼，后改为七秀坊，任首任坊主。\n");
    //set("attitude", "aggressive");
    //set("class", "yuanling");
    set("str", 150);
    set("con", 150);
    set("int", 150);
    set("dex", 150);
	set("per", 150);
	set("no_get", 1);
    set("max_qi", 100000000);
    set("qi", 100000000);
    set("max_jing", 50000000);
    set("jing", 50000000);
    set("neili", 30000000);
    set("max_neili", 13000000);
    set("jingli", 300000000);
    set("max_jingli", 3000000);
    set("no_suck", 1);
    set("jiali", 100000);
    //set("end_boss", 1);
    set_temp("apply/attack",  1550);
    set_temp("apply/defense", 1730);
    set("combat_exp", 2100000000);
    set("xyzx_sys/level", 15000);
    set("xyzx_sys/fanying", 400000);
    set("xyzx_sys/jingzhun", 400000);
    set("xyzx_sys/minjie", 400000);
    set("xyzx_sys/lingxing", 400000);
    set_skill("force", 100000); 
    set_skill("unarmed", 100000);
    set_skill("dodge", 100000);
    set_skill("parry", 100000);
    set_skill("blade", 100000);
	set_skill("sword", 100000);
    set_skill("demon-blade", 20000);
    set_skill("yunshang-xinjing", 50000); 
    set_skill("music", 20000);
    set_skill("ai-sword", 20000); 
    set_skill("shuiyue",20000);
    map_skill("force", "yunshang-xinjing");
    map_skill("unarmed","music");
    map_skill("parry", "ai-sword");
	map_skill("sword", "ai-sword");
    map_skill("blade", "demon-blade");
    map_skill("dodge", "shuiyue");
	set("chat_chance_combat", 100);
   /* set("chat_chance", 5);
    set("chat_msg", ({
                "情之一字，最是伤人...\n",
                "妹妹，你什么时候才会回来啊。\n",
                "妹妹，我不是想和你争什么，只是缘分弄人！\n",
        }) );*/
    setup();
    
    carry_object("/clone/cloth/pink_cloth")->wear();
    carry_object("clone/weapon/yuenv")->wield();
    add_money("gold", random(300));
}

