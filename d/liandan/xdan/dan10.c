#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}

void create()
{
  set_name( HIY "养颜丹" NOR , ({"yangyan dan", "dan"}));
  set_weight(90);
  if (clonep())
  set_default_object(__FILE__);
  else {
    set("unit", "颗");
    set("long", "一颗金黄色的丹丸，略微能闻到些许香气。\n");
    set("value", 1000);
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="dan" && arg!="yangyan dan")   return 0;
  
  if(me->query("id")==query("value"))
 return notify_fail("这棵丹不是你练的,你吃个什么劲。\n");
  me->add("per", 1);
  message_vision(HIG "$N轻轻掰开一颗养颜丹送入嘴中，$N的脸上突然奇痒无比...
也不知道过了多久,$N的脸上竟蜕了一层皮下来...\n" NOR, me);
  destruct(this_object());
  return 1;
}

