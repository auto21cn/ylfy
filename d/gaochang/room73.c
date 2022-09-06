// Room: /d/gaochang/room73.c
// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
#include <room.h>
void init();
int do_pull(string arg);
void create()
{
        set("short", "暗室");
        set("long", "四周黑黑的，唯有密室中央隐隐透出一点"+BLINK+RED+"红光"+NOR+"(hong guang)。\n");
    set("exits", ([ 
        "up" : __DIR__"room36",
]));
        setup();
}
void init()
{
    object *obj;
    obj=children(__DIR__"obj/wolfblade");
    set("blade",1);
    if (sizeof(obj)>1)  set("blade",0);
    if (query("blade")){ 
        set("long", "四周黑黑的，唯有密室中央隐隐透出一点"+BLINK+RED+"红光"+NOR+"(hong guang)。\n");
        set("item_desc",(["hong guang":"你发现红光居然来自插在地上的一把刀。\n",]));
        add_action("do_pull", "pull");
    }else{
        delete("item_desc");
        set("long", "四周黑黑的，什么也没有。\n");
    }
}
int do_pull(string arg)
{
        object me,ob;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (query("blade"))
        if( arg=="刀" || arg=="blade") {
             ob=new(__DIR__"obj/wolfblade");
             if (!ob->move(me)) ob->this_object();
             message_vision("$N拔出一把"+RED+"血狼"+NOR+"刹时红光消失了，四周变得黑黑的。\n",me);
             set("long", "四周黑黑的，什么也没有。\n");
             delete("item_desc");
             set("blade",0);
             return 1;
        }
        return 0;
}

