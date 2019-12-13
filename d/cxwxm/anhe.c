inherit ROOM;

#include <ansi.h>

void create()
{
        set("short","暗河");
        set("long","这是一条地下暗河，看不到任何出口，寒冷的河水（shui)冻得你发抖。\n\n");
        set("item_desc", ([
                "shui" : "你唯一的出路只好潜到水底去看看究竟了。\n" ]) );
        setup();
}
void init()
{
        add_action("do_qian", "qian");
}
int do_qian(string arg)
{
        object me = this_player();

    if( !arg || arg!="shui" )
        {
        write("你要上哪儿？\n");
        return 1;
    }
    message_vision( "$N硬着头皮往下一潜。\n", this_player());
{               me->move(__DIR__"pubu");
                this_player()->set("qi",1);
                this_player()->unconcious();
                return 1;
}               
}
