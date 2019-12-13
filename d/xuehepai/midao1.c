
inherit ROOM;
void create()
{
        set("short","洞府");
        set("long",@LONG
来到这里，好象到了水帘洞，居然别有洞天。看来是血河派前任的
十一位掌门的坐化之地，这是血河派的传统：为了不让血河派的武学失
传。快去找找吧，说不定会有什么奇遇。。。。
LONG );
        set("valid_startroom",1);
        set("class","血河派");
       set("exits",([
                "east" : __DIR__"pubulei1",
        ]));
//        set("no_clean_up"， 0);
        setup();
}

void init()
{
        add_action("do_jump","tiao");
}

int do_jump(string arg)
{
        object me;

        me=this_player();
        
        if (!arg || arg!="out")
                return notify_fail("你要往哪里跳？\n");
        message_vision("$N纵身一跃，跳了出去。\n",me);
        me->move(__DIR__"pubu");
        message_vision("$N突然从瀑布中穿了出来。\n",me);   
        return 1;
}

