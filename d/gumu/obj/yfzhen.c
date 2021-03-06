#include <ansi.h>
#include <weapon.h>
inherit THROWING;

void create()
{
        set_name(HIY"玉蜂针" NOR, ({ "yufeng zhen", "zhen" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", HIY"这玉蜂针乃是细如毛发的金针，六成黄金、四成精钢，以玉蜂尾刺上
毒液浸过，虽然细小，但因黄金沉重，掷出时(she)仍可及远。\n"NOR);
                set("value", 20000);
                set("material", "steel"); 
                set("treasure",1); 
                set("base_unit", "枚");
                set("base_weight", 2);              
        }
        set_amount(1);
        init_throwing(50);
        setup();
}

int init()
{
   add_action("do_throw", "she");
}

int do_throw(string arg)
{
       object me, ob;
       int i, damage;
       string msg;

       me = this_player();
       if (!arg) return notify_fail("你要对谁下手？\n");       
       ob = present(arg, environment(me)); 
       if (!ob) return notify_fail("找不到这个生物。\n");       i = ob->query_skill("dodge", 1) + ob->query_skill("parry", 1);
       i = random(i/2) - 10;
       damage = me->query_skill("throwing", 1)+me->query_str()*2;
       if( environment(me)->query("no_fight") )
                return notify_fail("你不能在这里动手。\n");
       if(me->is_busy())
                return notify_fail("你正忙着呢。\n");
       if(me->query("neili") < 500)
                return notify_fail("你的内力不够用来动手。\n");
       if(me->query("family/master_name") != "小龙女")
             return notify_fail("你不是小龙女的弟子，怎么会使用玉蜂针！\n"); 
       msg = HIY"\n$N袖袍一挥，一枚玉蜂针从袖底飞出直向$n急射而去！\n\n"NOR;       
       me->start_busy(2);
       me->add("neili", -100);
       me->add("jingli", -20);
       if(me->query_skill("throwing", 1) > i && random(ob->query("kar")) < 10 &&
          me->query("combat_exp") > (int)ob->query("combat_exp")/2 ) {
          msg += HIR"$n猛见金光一闪，急忙闪身躲避，但听一声惨叫，结果仍是被玉蜂针刺中！\n"NOR;
          ob->apply_condition("bee_poison", 70);
          ob->receive_wound("jing", damage/2);
          ob->receive_damage("qi", damage+random(damage));
          ob->receive_wound("qi", damage); 
//          p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
//          msg += "( $n"+eff_status_msg(p)+" )\n";
//          ob->set_temp("last_damage_from", "被"+me->name()+"杀");
          }
       else {
          msg +=HIY"$n急忙飞身后跃，只听嗤一声轻响，玉蜂针射在$p身前的泥土之中。\n"NOR;
          ob->add("jingli", -10);
          }              
       message_vision(msg, me, ob);
       if(!ob->is_killing(me->query("id"))) ob->kill_ob(me);
       destruct(this_object());
       return 1; 
}


int query_autoload() { return 1; }