// Room: /d/shaolin/zhonglou.c
// Date: YZC 96/01/19
inherit ROOM;
void create()
{
    set("short", "钟楼小院");
    set("long", @LONG
这是一座砖木结构的宝塔，塔高七层，塔身作八角形，飞檐
翘翎，檐角上挂满了一串串小铜铃，随风叮叮作响。塔身墙上镂
空雕绘着无数佛陀们的坐像。一个个形态维肖，看来出自名匠之
手。塔底入口处开了一扇拱形的小木门，门扇两侧用彩漆涂绘，
画的是释祖在灵山对诸天众佛讲经时的情形。
LONG
    );
    set("exits", ([
        "west" : __DIR__"guangchang2",
        "enter" : __DIR__"zhonglou1",
    ]));
    set("objects",([
        __DIR__"npc/seng-bing3" : 2,
    ]));
    set("outdoors", "shaolin");
    setup();
}
void init()
{
    object me=this_player();
    object ob=present("yingxiong ling",me);
    mapping myfam;
    myfam = (mapping)me->query("family");
    if (myfam)
    if (myfam["family_name"] == "少林派" && me->query("gender")=="男性") return;
    if (!ob)
    if (userp(me)){
            tell_object(me, HIY "几个僧兵对你喝道：施主未经我寺邀请，如何进来的？莫非是鼠辈？\n"+"只觉一阵腾云驾雾般，你昏昏沉沉地被扔出了少林寺！\n" NOR);
            me->move("/d/nanyang/shanmen");
            message("vision",
                HIY "只听乒地一声，你吓了一跳，定睛一看，\n"
                "原来是一个昏昏沉沉的家伙从少林寺里被扔了出来！\n" NOR, environment(me), me);
    }
}

