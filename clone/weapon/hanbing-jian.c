//LUCAS 2000-6-18
#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
   set_name(HIW "寒冰剑" NOR, ({"hanbing jian", "sword", "jian"}));
   set_weight(5000);
   set("unit", "把");
   set("icon", "10015");
   set("long", "一把散发着森森寒气的寒冰剑,令人望之生寒。\n");
   set("material", "ice");
   set("wield_msg","$N「唰」地一声抽出一把$n握在手中，只觉一股寒气扑面而来！\n");
   set("unwield_msg","$N将手中的$n插入腰间，觉得暖和多了。\n");

   init_sword(500);

   if( clonep(this_object()) ) {
     set_default_object(__FILE__);
   }
   setup();
}  
void init()
{

   remove_call_out("do_melt");
   call_out("do_melt", 1);
}

void do_melt()
{
   if(this_object()) call_out("melt", 1);
}

void melt()
{
   object env;

   if(!this_object()) return;

   env=environment(this_object());

   if( env->is_character() && playerp(env) )
   {//a player or a NPC.
     
        if(environment(env))
          message_vision("$N觉得身上凉凉的，湿湿的，原来是寒冰剑化了。\n", env);
        destruct(this_object());
        return;
   }

   else if( (int)env->query_max_encumbrance() > 0 && !environment(env) )
   {//a room.  
   
        tell_object(env,"寒冰剑终于化成了一滩水，流得到处都是。\n");
        destruct(this_object());
        return;  
   } 
}


