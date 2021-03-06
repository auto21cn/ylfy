// Room: /d/heimuya/zhaoze/pubupang.c
inherit ROOM;

void create()
{
        set("short", "瀑布旁");
        set("long", @LONG
只见瀑布旁柳树下坐着一人，头戴斗笠，身披蓑衣，坐在一块石上，
正自垂钓。这瀑布水势湍急异常，一泻如注，水中哪里有鱼？纵然有鱼，
又哪有余暇吞饵？
LONG
);
        set("exits", ([ 
  "southup" : __DIR__"shandian",
  "eastup" : __DIR__"lingding",
]));
    set("objects", ([
        __DIR__"npc/yuren" : 1,
    ]));

        set("outdoors", "pubupang");

        setup();
}
int valid_leave(object me, string dir)
{
        object ob=present("yu ren", environment(me));
        if (ob && living(ob) ){
            if (( present("hong juan",me) ) && dir == "southup" ) {
                    say("渔人对"+me->name()+"喝道：请留步。\n");
                    return notify_fail("渔人喝道：这位" + RANK_D->query_respect(me) + "请止步。\n");
            }
        }
        return ::valid_leave(me, dir);
}

