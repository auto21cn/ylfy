// Room: /d/xingxiu/xxroad7.c
inherit ROOM;
void create()
{
        set("short", "收购店");
        set("long", @LONG
这是一个小收购店, 房屋内铺着羊毛地毯。店老板为一波斯人, 专门收
购当地物产。在一张大羊皮纸上,写着需收购的各类物产表(sign)。
LONG
        );
        set("exits", ([
            "east" : __DIR__"huijiang3",
        ]));
        set("objects", ([
                __DIR__"npc/dealer": 1 ]) );
        set("item_desc", ([ /* sizeof() == 1 */
"sign" : "羊皮纸上写道：
中原钱币通用。
        哈密瓜(hamigua)
        羊皮(yangpi)
        狼皮(langpi)
        毛毯(maotan)
        雪蚕(xuecan)
\n"
]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
