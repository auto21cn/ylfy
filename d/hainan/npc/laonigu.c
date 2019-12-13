#include <ansi.h>
inherit NPC;
string *name=({"天聋尼","地哑尼",});
void create()
{
 set_name(YEL+name[random(sizeof(name))]+NOR, ({ "nigu", "dashi" }) );
  set("gender", "女性");
  set("age", 40+random(40));
  set("title",YEL"白云庵传人"NOR);
  set("long","一位面容慈祥的老尼,正拿着扫帚扫地。\n");
  create_family("白云庵",4,"传人");
  set("attitude", "peaceful");
  set("combat_exp", 50000000);
  set("per", 15);
  set_skill("parry", 580);
  set_skill("unarmed", 580);
  set_skill("dodge", 580);
  set_skill("sword", 580);
  set_skill("force", 580);
  set_skill("baihua-zhang", 580);
  set_skill("feixian-jian", 580);
  set_skill("bitao-shengong", 580);
  set_skill("qiongya-bufa", 580);
  map_skill("sword", "feixian-jian");
  map_skill("unarmed", "baihua-zhang");
  map_skill("parry", "feixian-jian");
  map_skill("force","bitao-shengong");
  set("max_qi",14000);
  set("max_jing",54000);
  set("max_jingli",54400);
  set("neili",54000);
  set("max_neili",54000);
  set("force_factor",3);
  setup();
  carry_object("/d/hainan/obj/hui_cloth")->wear();
  carry_object("/d/hainan/obj/saozhou")->wield();
   add_money("gold",2);
}
