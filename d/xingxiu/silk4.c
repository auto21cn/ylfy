// /d/xingxiu/silk4.c
// Jay 3/17/96
inherit ROOM;
void create()
{
        set("short", "丝绸之路");
          set("long", @LONG
这是一条中原和西域之间的商道。西面是一望无际的大沙漠，
传说那里常有盗匪出没。西北则通向一片连绵的山脉，东面就是通
向中原的路。路边有一块石碑(shibei)，石碑旁有一个洞(hole)。
LONG );
        set("outdoors", "xingxiuhai");
        set("exits", ([
                "east" : __DIR__"silk3",
                "west" : __DIR__"shamo1",
                "northwest" : __DIR__"shanjiao",
                "southwest" : "/d/xueshan/caoyuan" ,
        ]));
        set("item_desc", ([
                "shibei" : "北至西域，东达中原。谁若西行，格杀勿论。白驼山主人启。\n",
        ]));
        setup();
}
void init()
{
        add_action("do_push", "enter");
}
int valid_leave(object me, string dir)
{
    if ((dir == "west")&& !userp(me)) return 0;
    return 1;
}
int do_push(string arg)
{
    object me;
    mapping fam;
    me = this_player();
    if( !arg || arg=="" ) return 0;
    if( arg=="hole" )
    {
        if( (fam = me->query("family")) && fam["family_name"] == "丐帮" ) 
        {
            message_vision("$N运起丐帮缩骨功，一弯腰往洞里钻了进去。\n",me );
            me->move("/d/gaibang/underxx");
                    message("vision",me->name() + "从洞里走了进来。\n",
                        environment(me), ({me}) );
            return 1;
        }
        else 
            return notify_fail("这么小的洞，你钻得进去吗？\n");
    }
    return 0;
}   
