// Room: qian-ting.c

inherit ROOM;

void create()
{
        set("short", "前厅");
        set("long", @LONG
上得山来，一座波斯风格的建筑豁然矗立在你的眼前，碧绿色的
琉璃瓦和金黄色的廊柱相互辉映，在阳光下熠熠发光，常令来着者惊
叹不已，正前方的石壁上刻着三个火红大字，如火焰升腾状，你不禁
急切起来，想早些一睹明教光明顶的风采。下意识地加快了脚步。

LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"guangming-ding",
  "southwest" : __DIR__"xiaolu-1",
]));
        set("objects", ([
                __DIR__"npc/pengyingyu" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

