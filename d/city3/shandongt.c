//shandongt.c
//by mei
inherit ROOM;
string *names=({
        __DIR__"shandong7",
        __DIR__"shandong5",
        __DIR__"shandong1",
        __DIR__"shandong6",
} );

int do_use(string arg);
int do_zuan(string arg);

void create()
{
        set("short", "山洞");
        set("long", @LONG
你壮起胆子，走进了山洞中，这里暗无天日，突然间，有
只蝙蝠在你面前飞过，你被惊出了一身冷汗。越往里走就越来
越黑，你好象迷失方向了。
LONG
        );

        setup();
}
void reset()
{
        int i,j;
        string temp;
        ::reset();
        for (i=0;i<=3;i++)
        {
                j=random(4);
                temp=names[j];
                names[j]=names[i];
                names[i]=names[j];
                names[i]=temp;
        }
        set("exits", ([
                "north" : names[0],
                "south" : names[1],
                "east" : names[2],
                "west" : names[3],
        ]));
}
void init()
{
        add_action("do_use", "use");
        add_action("do_zuan", "zuan");
}
int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(
             "你点燃了火折，发现山洞右边有一道裂缝，似乎可以钻(zuan)出去。\n"
             );
             me->set_temp("marks/钻1", 1);
             return 1;
       }
    return 0;
}

int do_zuan(string arg)
{
        object me;
        me = this_player();

        if (me->query_temp("marks/钻1") ) {
            message("vision", me->name() + "突然一脚踩空，身体直往下坠！\n",
                    environment(me), ({me}) );
            me->move(__DIR__"midao");
            me->unconcious();
            message("vision", me->name() + "从山洞里掉了下来。\n",
                    environment(me), ({me}) );
            me->delete_temp("marks/钻1");

            return 1;
        }
        else {
            write("你想往哪儿钻?!\n");
            return 1;
        }
}

