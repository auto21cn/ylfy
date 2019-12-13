//ROOM didao6
inherit ROOM;
void init();
int do_move(string);
string look_wan();
void create()
{
  set("short","秘道尽头");
  set("long",
        "你忽觉前方一亮，身前真是别有洞天，除了来路，四周全是\n"
        "石壁。这里宽有十余丈，洞的中央有一石碗(wan)。\n"
     );
  set("exits",([      
      "northdown" : __DIR__"didao4",

     ]));
   
       set("item_desc", ([
            "wan" : (: look_wan :),
        ]));

 setup();
}
void init()
{
        add_action("do_circle", "circle");
}
string look_wan()
{
    this_player()->add_temp("look_wan",1);
        if (this_player()->query_temp("look_wan")>3){
                this_player()->delete_temp("look_wan");
                return "你仔细看了看，发现碗底是镶嵌在一块石头上的，似乎可以转动(circle)它。\n";
        }else
        return "这是一个自汉代流传下的古董,很别致。\n";
}

int do_circle(string arg)
{
        object me = this_player();
        object room;
        if ((arg != "wan") || !arg)
                return notify_fail("你要旋什么？\n");
        if((int)me->query("str") < 20)
                return notify_fail("你旋不动它！\n");
        if(!( room = find_object(__DIR__"neishi")) )
                room = load_object(__DIR__"neishi");
        if (!query("exits/up")){
          set("exits/up", __DIR__"neishi");
          message_vision("$N旋动了碗，只见迎面的石墙移开,露出一个黑幽幽的洞口。\n",me);
          room->set("exits/down", __FILE__);
          message("vision", "外面传来一阵搬动碗的声音，一束光线射了进来。\n", room);
        }else{
          delete("exits/up");
          message_vision("很快碗又搬回了原位。迎面的石墙合上，洞口又被封住了。\n",me);
          room->delete("exits/down");
          message("vision", "外面传来一阵搬动碗的声音，洞口被封住了。\n", room);
        }
        return 1;
}


