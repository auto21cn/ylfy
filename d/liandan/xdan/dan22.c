inherit ITEM;
void create()
{
        set_name(HIR"智力丸"NOR, ({ "zhili wan","wan"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
       else {   
                set("unit", "颗"); 
                set("no_get",1);
                set("no_s",1);             
                set("no_put",1);
                set("no_give",1);
        }
    setup();
}
void init()
{
    if (environment()==this_player())
        add_action("do_eat", "eat");
}
int do_eat(string arg)
{
  object me = this_player();
  int maxneili,neili;
    neili = me->query("neili");
    maxneili = me->query("max_neili");
    
  if(!id(arg)) return 0;

  if(me->query("id")==query("value"))
  return notify_fail("这棵丹不是你练的,你吃个什么劲。\n");
    
me->add("combat_exp",random(5000));
me->set_skill("literate",me->query_skill("literate",1)+1);
  message_vision(HIR"$N拿起智力丸吃了下去,感觉对读书写字的了解更加清晰了!!!!!\n"NOR,me);
       destruct(this_object());
       return 1;
}


