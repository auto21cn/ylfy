// Room: /d/kunlun/klsj1.c// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
        set("short", "石阶");
        set("long", @LONG
石阶上积了层厚厚的积雪，路两旁山石嶙峋，四下静悄悄的，连半个行人
也没有。只有呼啸的北风卷起漫天飞雪，向你迎面扑来。
LONG
        );
        set("outdoors", "klsj1");
        set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"sbxd",
  "northup" : __DIR__"klsj2",
]));

        setup();
}
int valid_leave(object me, string dir)
{
    object boot;
    int damage=80-me->query_skill("dodge",1)/10;
    boot=me->query_temp("armor/boots");
    if (dir=="northup" && (!boot || boot->query("id")!="sandals")){
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

