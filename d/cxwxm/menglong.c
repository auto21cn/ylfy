// Room: /d/cxwxm/menglong.c
// marry 8,21
inherit ROOM;

#include <ansi.h>
void create()
{
        set("short",HIC"猛龙阁"NOR);
        set("long",
"这里就是门主的大师兄居住的地方，除了摆放的器具比较奢侈以外\n"
"就没啥特殊的饰物了。对着门的那面墙上挂着一柄斧头，不过看来并不\n"
"是什么"HIW"神兵"HIB"利器"NOR"，不过尺寸大得有些夸张，也许这里的主人的偏爱吧。\n\n"
 );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"dating",
]));
        set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/liang.c" : 1,
  __DIR__"npc/puren.c" : 2,
]));

        setup();
}
/*
void init()
{
        object me;
        me=this_player();
        if (wizardp(me)) return 0;
        if (!me->query("jihao",1))
        {
        message_vision(HIC"突然,眼前出现了一大票的人，其中一个人指着$N大叫：\n"NOR
                    CYN"“我想起来了，就是他干的！”\n"NOR
                    HIR"立刻黑压压的一群人提着西瓜刀冲了过来，向$N一阵乱砍！\n"NOR,me);
                me->move("/d/cxwxm/tianye");
                me->unconcious();
        } 
}
*/
