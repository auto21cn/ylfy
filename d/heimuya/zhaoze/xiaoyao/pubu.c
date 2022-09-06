// pubu.c 
// shilling 97.2
inherit ROOM;
#include <ansi.h>
void create()
{
    set("short", "瀑布");
    set("long", @LONG
你猛听得水声响亮，轰轰隆隆，便如潮水大至一般，抬头一看，只见一
条大瀑布，犹如银河倒悬，从高崖上直泻下来。崖壁上长着些小松树，下面
是万丈深渊，云雾弥漫，望不到尽头. . . .
LONG    );
    set("outdoors", "xiaoyao" );
    set("no_clean_up", 0);
    setup();
}
 
void init()
{
    add_action("do_jump","jump");
    add_action("do_climb","climb");
}
int do_jump(string arg)
{
    object ob;
    ob = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg != "down" )
        return notify_fail("你想要跳崖自杀？这么想不开啊？\n");
    tell_object(ob, HIR"你不加思索，纵身一跃，跳下了悬崖。。。。\n"NOR);
    message("vision", NOR"只见" + ob->query("name") + "万念俱灰，纵身跳入了悬崖之中。。。。\n"NOR, environment(ob), ob);
    if((random((int)ob->query_kar()) < 10 ) && ((int)ob->query_skill("dodge")<30) )
    {
        ob->die();
        return 1;
    }
    ob->set("qi", -1);
    ob->move(__DIR__"yanfeng");
    return 1;
}

int do_climb(string arg)
{
    object me;
    me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg != "up" )
        return notify_fail("你想要爬去那？\n");
    if ((int)me->query_skill("dodge",1) < 600 ) {
        message_vision("只见$N抓着崖壁上的小松树，想要爬上去。忽然一个不稳，掉了下来。\n", me); 
    me->set("qi", -1);
    return 1;
    } else           
        message_vision("只见$N抓着崖壁上的小松树，慢慢地爬了上去。\n", me);
          me->move("/d/heimuya/zhaoze/pubu");
    return 1;    
}
