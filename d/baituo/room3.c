//room1.c
inherit ROOM;
void create()
{
  set("short","练功室");
  set("long",
      "这里是白驼山弟子的练功室。有陪练童子陪你练功。\n"
    );
  set("exits",([
      "out" : __DIR__"liangong",
     ]));
 set("objects",([
     __DIR__"npc/tongzi" : 1,
     ]));
 setup();
}
int do_check(object me)
{
    object where=this_object();
    object *obj;
    int i;
    obj=deep_inventory(where);
    if (!sizeof(obj))   return 0;
    for (i=0;i<sizeof(obj);i++){
        if (obj[i]==me) continue;
        if (userp(obj[i]))
            return 1;
    }
    return 0;
    
}
void init()
{
    object ob=this_player();
    if(userp(ob) && (int)do_check(ob)){
        message_vision("$N一见房间里已经有人了，只好退了出去。\n",ob);
        ob->move(__DIR__"liangong");
    }
}
 
