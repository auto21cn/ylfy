inherit ROOM;
void create()
{
        set("short", "前花园");
        set("long", @LONG
鸣玉坊著名之处在这里可略见一斑，四边花草甚多，但唯有牡丹最胜。那花不是寻
常玉楼春之类，乃“姚黄”“魏紫”有名异品，一本价值五千。那花正种在朱门对面，
周围以湖石拦之。其花大如丹盘，五色灿烂，光华夺目。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"garden",
]));

        set("objects", ([ /* sizeof() == 1 */
         __DIR__"npc/huajiang" : 1,
]));
        set("outdoors","dali");

        setup();
}
