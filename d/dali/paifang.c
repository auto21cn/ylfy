// Room: /d/dali/paifang.c
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月18日，北京时间：21时23分37秒。

inherit ROOM;

void create()
{
	set("short", "[1;33m牌坊[2;37;0m");
	set("long", @LONG
你来到了一座牌坊之前，牌坊上提着四个金笔大字「[1;33m圣道广慈[2;37;0m」。
夕阳照在黄瓦宫殿的琉璃瓦上，金碧辉煌，令人目为之炫。前面是一座
宫殿，宫门上写着「[1;33m圣慈宫[2;37;0m」三个大字。
LONG
	);
	set("outdoors", "dali");
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"guangchang",
  "north" : __DIR__"huanggong1",
]));

        set("objects", ([
                __DIR__"npc/shiwei" : 2,
        ]));

	setup();
}

int valid_leave(object me, string dir)
{
    int i;
    object *inv;
    if(dir=="north")
    {
     if( this_player()->query("combat_exp")>256000 )
        {
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
            if(inv[i]->query("weapon_prop") && (inv[i]->query("equipped")))
                if(objectp(present("shi wei", environment(me))) &&
                   living(present("shi wei", environment(me))))
                    return notify_fail("[1;33m金甲带刀侍卫[2;37;0m上前挡住你，朗声说道：这位" +
                        RANK_D->query_respect(me) + "请放下兵刃。\n"
                        "你可以进宫，但不得手持兵刃。\n");
        return ::valid_leave(me, dir);
        }
     else
     {
         if(objectp(present("shi wei", environment(me)))&&living(present("wei", environment(me))))
            return notify_fail("[1;33m金甲带刀侍卫[2;37;0m拦住你骂道：“你以为你是谁啊？一个寻常百姓，难道还想进宫晋见皇上？！\n你这" + RANK_D->query_rude(me) +"快给我滚远点儿，不然别怪我不客气！”\n");
      }
    }   
return ::valid_leave(me, dir);
}


