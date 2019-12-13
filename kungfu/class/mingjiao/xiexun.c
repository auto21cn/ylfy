// XieXun.c
// pal 1997.05.09

#include "ansi.h"
int ask_jinmao(string str);
inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
void create()
{
    set_name("谢逊", ({"xie xun", "xie", "xun", }));
	set("long",
        "他是一位身材魁伟异常的的老者，身穿一件白布长袍。\n"
        "他满头黄发，威风凛凛，真如天神一般，只是两只眼睛并不睁开。\n"
	);

	set("title",HIG "明教" HIY "金毛狮王" NOR);
	set("level",9);
	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 63);
	set("shen_type", 1);
set("shen", 0);	
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

set("max_qi", 350000);  	
set("max_jing", 350000);        	
set("max_jingli", 80000);        	
set("neili", 1500000);           	
set("max_neili", 30000);	
set("jiali", 300);	

set("combat_exp", 150000000);	
	set("score", 800000);

set_skill("force", 1200);	
set_skill("dodge", 1500);       	
set_skill("blade", 1500);       	
set_skill("wuhu-duanmendao", 1500);       	
set_skill("parry", 1200);	
set_skill("unarmed", 1300);	
set_skill("hunyuan-yiqi", 1200);	
set_skill("shaolin-shenfa", 1500);	
set_skill("qishang-quan", 1300);	
set_skill("jingang-quan", 1300);	
set_skill("literate", 300);	

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("unarmed", "qishang-quan");
map_skill("blade", "wuhu-duanmendao");     	
map_skill("parry", "qishang-quan");	

	prepare_skill("unarmed","qishang-quan");

set("chat_chance_combat", 100);	
	set("chat_msg_combat", ({
(: perform_action, "blade.duan" :),
(: perform_action, "unarmed.hunpofeiyang" :),
	}) );
set("inquiry", ([
"金毛狮王" : "明教首席法王，也就是我--谢逊。",
"name" : "谢逊就是我。",
"明教" : "唉....，现在明教人心溃散，再也难以回复往日风光了。",
"张无忌" : "他就是我的义子，不知道他现在怎样了。你有他的消息吗？",
"屠龙刀" : "哼...，凭你也想打屠龙宝刀的主意。想要拿刀先得砍下谢某项上人头。",
"金毛": (: ask_jinmao :),
]) );
	setup();

carry_object("/clone/cloth/lingyun")->wear();           	
carry_object("/clone/weapon/tulong")->wield();	
carry_object("/clone/cloth/zixuan")->wear();	
}
int ask_jinmao(string arg)
{
object me;
object xie;
object jinmao;
xie=this_object();
me=this_player();
if (me->query("class")!="shizhe")        	
{
command("say 你与本派毫无瓜葛，不知这话从何说起。");	
return 1;
}
else {
if (xie->query_temp("sign")) 	
{
command("say 你来晚了，早已有人帮我送去了。");
return 1;
}
else {
message_vision(CYN "你有了我那义子的消息了，太好了.....谢逊激动地从怀中摸出撮金毛交了给$N \n" NOR,me);
jinmao=new("/d/mingjiao/npc/obj/jinmao");
jinmao->move(me);
xie->set_temp("sign",1);
return 1;
}
}
}
