// sl1.c
// Modify By csy 98/12
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{ 
       set("short",HIB"石室"NOR);
       set("long", @LONG
古墓中阴沉的石室，只听见远远传来你脚步的回音，空荡荡的感觉使你心
中只有恐惧，甚至忘记孤独。你不知身处何地，四周如此漆黑一片，只能靠摸
索前行。
LONG
     );
    
        set("exits", ([
                "east" : __DIR__"ss"+(1+random(3)),
                "west" : __DIR__"ss"+(1+random(3)),
                "south" : __DIR__"ss"+(1+random(3)),
                "north" : __DIR__"ss"+(1+random(3)),
        ]));

        setup();
}

void init()
{
        object me = this_player();
        if(userp(me) && me->query("jing") < 200){
           me->move(__DIR__"ss0"); 
           message("vision", me->name()+"昏昏沉沉地走了过来。\n",environment(me), ({me}));
           write(HIR"你慢慢发现自己体力不支.....\n"NOR);
           me->unconcious();
           }
        if(!me->query_temp("steps") && userp(me))
           me->set_temp("steps", keys(query("exits"))[random(sizeof(query("exits")))]);
}

int valid_leave(object me, string dir)
{
        if( dir != "up")
        me->receive_damage("jing",10 + random(10));
        if( dir != me->query_temp("steps"))                
                me->set_temp("step", 0);
        else    me->add_temp("step", 1);

        if( me->query_temp("step") > 3 + random(3) ) {
                me->move(__DIR__"ss5");
                me->delete_temp("step");
                me->delete_temp("steps");
                me->start_busy(2);
                return notify_fail("你累得半死，终於发现前方有一道光亮。\n");
        }
       return ::valid_leave(me,dir);
}

