// zjb /2002/3/15/
inherit ROOM;
int do_jump(string arg);  
void on_sun();
void create()
{
        set("short", "黄土大道");
        set("long", @LONG 
你一脚深一脚浅的走在黄泥之中，甭提有多难过
更要命的是这里的地下似乎还有股吸力在不断的吸收
你的生命力，还是走快些吧。
LONG
        );
        set("outdoors", "yihua");
        set("exits", ([
                "enter" : "d/xuantian/room2",
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));             
        setup();

}
void init()
{
        add_action("do_use", "use");
        add_action("do_tiao", "tiao");
    this_player()->receive_damage("qi", 15);
    this_player()->receive_wound("qi",  15);
    message_vision(YEL"$N一脚深一脚浅的往前走着，只觉得呼吸越来越难。\n"NOR, this_player());
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(
             "你点燃了火折，发现路边有个小坑，你要跳下去吗？\n"
             );
             this_player()->set_temp("marks/走1", 1);
             return 1;
       }
}

int do_tiao(string arg)
{
        object me;
        me = this_player();
        if( arg != "坑" )
                return notify_fail("你跳了起来，狠狠的摔在了地上。\n");
        if (me->query_temp("marks/走1") ) {
            message("vision", me->name() + "消失在一阵黑暗之中。\n",
                    environment(me), ({me}) );
            me->move("d/xuantian/dongxue");
        me->unconcious();
            message("vision", me->name() + "从坑里爬了出来。\n",
                    environment(me), ({me}) );
            this_player()->delete_temp("marks/走1");

            return 1;
        }
        else {
            write("你跳了起来，狠狠的摔在了地上。\n");
            return 1;
        }
}

