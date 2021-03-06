// Room: /inherit/room/cunyangdaoguan.c
inherit ROOM;
int do_put(string arg);
void create()
{
        set("short", "纯阳道观");
        set("long", @LONG
只见前方一侧是深不见底的峭壁，另一旁依山势建有一小道观，道观已十分破旧，两扇
石门紧闭着，门顶的石匾上刻着「纯阳道观」四个模糊的大字。
LONG
);
        set("exits", ([ 
  "east" : __DIR__"houzhiwangyu",
]));
    set("item_desc", ([
        "men" : 
"    两扇刻满雷鸟和云卷的石门。由于年代久远，门上已长满了青苔。
但仍然可以看出门上有一凹陷的印痕。\n",
       "石门" : 
"    两扇刻满雷鸟和云卷的石门。由于年代久远，门上已长满了青苔。
但仍然可以看出门上有一凹陷的印痕。\n",
       "印痕" :"这印痕有点象块令牌的形状。\n",
])); 
        setup();
}
void init()
{
    add_action("do_put", "put");
    
}
int do_put(string arg)
{
        object me,ob;
        object room;
        me = this_player();
        if (!objectp(ob=present("ling pai",me)))
            return notify_fail("你身上没有那样东西。\n");
        if( arg=="ling in 印痕" || arg=="ling pai in 印痕") {
            if (!( room = find_object(__DIR__"daoguan")) )
                room = load_object(__DIR__"daoguan");
            message_vision("$N举起手中的"+ob->query("name")+"插进印痕。\n",me);
            message("vision","这时突然传来一阵机关的响声，石门打开了，露出一条甬道。\n",this_object());
            message("vision", "这时突然传来一阵机关的响声，石门被人打开了。\n",room);
            set("exits/north",base_name(room));
            room->set("exits/south",base_name(this_object()));
            destruct(ob);
            call_out("close_door",10,room);
        return 1;
      }
      return 0;
}
void close_door(object room)
{
      message("vision","突然“砰”的一声，石门又关得死死的。\n",this_object());
      message("vision","突然“砰”的一声，石门又关得死死的。\n",room);
      delete("exits/north");
      room->delete("exits");
        room->set("do_prize",0);
}

