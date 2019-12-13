// Room: /d/kunlun/klsj2.c// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
        set("short", "石阶");
        set("long", @LONG
眼前的石阶只有薄薄的一层冰，你不禁纳闷地抬头一望，原来石阶两旁长
满了高大的松树。树冠上压了厚厚的白雪，是以石阶上没雪。北风吹过，积雪
向你迎头砸下，你不禁打了个哆嗦。
LONG
        );
        set("outdoors", "klsj2");
        set("exits", ([ 
  "southdown" : __DIR__"klsj1",
  "northeast" : __DIR__"klt",
]));
     
        setup();
}
int valid_leave(object me, string dir)
{
    object boot;
    int damage=80-me->query_skill("dodge",1)/10;
    boot=me->query_temp("armor/boots");
    if (dir=="northeast" && (!boot || boot->query("id")!="sandals")){
        if (damage<20){
            tell_object(me,HIW+"你脚下一滑，你晃了两晃，总算没摔着！\n"+NOR);
            return 1;
        }else
        me->receive_damage("qi",damage);
        me->receive_damage("jing",damage);
        return notify_fail(HIW+"你脚下一滑，摔了个四脚朝天！\n"+NOR);
   }
   return 1;
}

