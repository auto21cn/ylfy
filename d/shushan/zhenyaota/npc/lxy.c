//【蜀山剑派】dhxy-evil 2000.7.5
//lilong改于 2002.01.12
inherit NPC;
#include <ansi.h>
int do_report();
void create()
{
        set_name("李逍遥", ({ "li xiaoyao", "li", "xiaoyao" }));
        set("title","蜀山剑派入门弟子");
        set("long", 
"李逍遥身材较瘦，长的浓眉阔眼，气宇暄昂。\n");
        set("gender", "男性");
        set("age", 18);
	 set("class", "xiake");
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("per", 30);
        set("qi", 15000000);
        set("max_qi", 15000000);
        set("jing", 15000000);
        set("max_jing", 15000000);
        set("neili", 15000000);
        set("max_neili", 15000000);
        set("combat_exp", 2100000000);
        set("max_jingli", 15000000);
        set("jingli", 15000000);
         set("jiali",10000);
		set("no_suck", 1);
        set_skill("force", 1500);
        set_skill("dodge", 1500);
        set_skill("unarmed", 1500);
         set_skill("fumozhang", 1500);
        set_skill("parry", 1500);
        set_skill("sword", 1500);
        set_skill("canxin-jian", 1500);
        set_skill("shushan-force", 1500);
        set_skill("zuixian-steps",1500);
        set_skill("literate",1500);
        map_skill("unarmed", "fumozhang");
        map_skill("force", "shushan-force");
        map_skill("dodge", "zuixian-steps");
        map_skill("parry", "canxin-jian");
        map_skill("sword", "canxin-jian");
        set("inquiry", ([
                "救出来了"    : (: do_report :),
        ]));
        setup();
        create_family("蜀山派", 3, "弟子");
         carry_object("/clone/cloth/dao-cloth")->wear();
         carry_object("/clone/weapon/gangjian")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="蜀山派" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师叔见笑了。\n");
			else command("say 师姑见笑了。\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师兄太客气了。\n");
			else command("say 师妹太客气了。\n");
		}
		else 
		{
			command("consider");
			command("say 看在你诚心诚意的份上,我收你为徒!\n");
			command("recruit " + ob->query("id") );
                     ob->set("shushan/xiangsi_perform",1);

		}
	}
            else
	{
		command("say 看在你诚心诚意的份上,我收你为徒!\n");
		command("recruit " + ob->query("id") );
              ob->set("shushan/xiangsi_perform",1);

	}

	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "蜀山派李逍遥弟子");
              }
              return 0;
}

void init()
{
  object ob;

  ::init();
  if( interactive(ob = this_player()) && !is_fighting() )
  {
    remove_call_out("greeting");
    call_out("greeting", 1, ob);
  }
}
void greeting(object ob)
{
        if( !ob || !present(ob, environment(this_object())) ) return;
        say( "李逍遥说道：这位" + RANK_D->query_respect(ob) +
"，能不能帮我救出灵儿！她被关进镇妖塔里了！\n");
}

int do_report()
{
 int i=random(3000000);
 object me = this_player();
 if(me->query("shushan/zhanyi")) { 
 me->set("zhanyi/zhenyaota",1);
 me->delete("shushan/zhanyi");
 me->add("combat_exp",50000+i);
 me->add("neili",1000);
 message("system",HIC"〖"HIW"镇妖塔传讯"HIC"〗"HIY+me->query("name")+HIG"救出[1;37m镇妖塔[1;32m里的赵灵儿，受到奖励！[2;37;0m\n"NOR,users());    
 tell_object(me,"你赢得了50000点的经验和1000点的内力\n");
 me->save();
 } 
 else 
 {
 command("say 谢谢你！不能再麻烦你啦！");
 }
 return 1;
}



