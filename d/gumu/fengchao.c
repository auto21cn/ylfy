// fengchao.c by river 98/08/29
#include <ansi.h>
inherit ROOM;

void delete_hexiu(object me, object arg);

void create()
{
          set("short",HIR"蜂巢"NOR);
          set("long", @LONG
这丛红花排开来长达数丈，密密层层，奇香扑鼻，但见花丛有如一座大屏
风，红瓣绿枝，煞是好看，四下里树荫垂盖，便似天然结成的一座花房树屋。
四周都是一片清幽，只闻泉声鸟语，杳无人迹，确是个上好的练功所在。
LONG        );

          set("exits", ([
               "eastdown" : __DIR__"guoyuan",
          ]));

          set("outdoors","古墓");          

          setup();
}

void init()
{
       add_action("do_tong","tong");
}

int do_tong(string arg)
{
        object me = this_player();        
        mapping fam;        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢。\n");
        if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
            return notify_fail("你不是古墓派传人，不要再在古墓久留了。\n");
        if ( arg =="fengchao"){
           if ( me->query_condition("gumu_job" ) > 0 )
                return notify_fail("你捅了半天发现蜂巢里什么都没有了。\n");
           if ( me->query("combat_exp") < 30000)
                return notify_fail("采蜂蜜很危险，你现在还不能干。\n");
           if (me->query("combat_exp") > 120000 )
                return notify_fail("你武功已经够高，采蜂蜜的事就让小弟子们去做吧。\n");
           if ( me->query_temp("gm_fengmi"))
                return notify_fail("你不是已经采了蜂蜜了么？\n");
           message_vision(HIY"$N用力捅了捅蜂巢，从中挖出了不少蜂蜜。\n"NOR,me);
           new(__DIR__"obj/fengmi")->move(me);
           me->start_busy(5);
           call_out("danger", 3, me);
           return 1;
           }
        return notify_fail("你胡乱捅了几下，结果什么也没有发生。\n");
}

void danger(object me)
{
          object obj;
          tell_object(me, HIR"你隐约感觉到有东西围了过来....，着眼四观，发现自己被包围了。\n" NOR);
          new(__DIR__"/npc/beast")->move(__DIR__"fengchao");                       
          obj = present("feng mi", me);
          destruct(obj);
          tell_object(me, RED "你紧张起来，蜂蜜随手落在地上。\n" NOR);
          me->set_temp("gm_fengmi",1);
}

