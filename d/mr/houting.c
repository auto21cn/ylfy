#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
         set("short","后厅");
         set("long", @LONG
这里是慕容家里商议事情的地方，不是慕容弟子最好不要到这里来。在
后堂正中摆放着一个香案，上面摆放着一个灵位牌子(paizi)，在正中墙
上挂着一幅百鸟朝奉图，边墙上挂着一口宝剑。东西两面各是一间厢房，
南面是内堂。
LONG
    );
         set("item_desc",([
             "paizi" : "慕容世代祖先灵位\n",  
             "sword" : "那是一口玲珑般的宝剑，透着碧玉色。\n",
             "baojian" : "那是一口玲珑般的宝剑，透着碧玉色。\n",
]));
         set("exits",([
             "east" : __DIR__"xiangfang2",
             "west" : __DIR__"xiangfang3",                    
             "south" : __DIR__"neitang",
             "north" : __DIR__"dating",
]));
         set("count",1);
         setup();
//         replace_program(ROOM);
}
             
void init()
{
        add_action("do_ketou", "ketou");
        add_action("do_ketou", "拜祭");
}             

int do_ketou()
{
        object me = this_player();
        object ob = this_object();
        if ( !present("yu xi",me) ) return 0;
        if ( me->query_temp("慕容/ketou") == 2 ) {
                if ( ob->query("count") > 0 ) {
                        new(__DIR__"npc/obj/biyujian")->move(ob);
                        message("vision","只听见铛的一声，灵牌里掉下一把" +
                                "寒光闪闪的宝剑。\n",me);
                        destruct(present("yu xi",me));
                        me->delete_temp("慕容/ketou");
                        ob->add("count", -1);
                        return 1;
                }
                else {
                        message("vision","你不经意望见灵牌似乎已被打开过。\n",
                                me);
                        me->delete_temp("慕容/ketou");
                        return 1;
                }
        }
        else {
                me->add_temp("慕容/ketou", 1);
                message_vision("$N恭恭敬敬地在灵牌前磕了个响头。\n", me);
                return 1;
        }
}       
