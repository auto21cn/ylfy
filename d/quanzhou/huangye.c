// Room: /d/quanzhou/huangye.c
// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
    set("short", "荒野");
    set("long", @LONG
你走在泉州郊外的荒野上，不时有一阵阵海风从南面吹来，北边通往
南方第一港泉州，南面是一个小渔村。
LONG
    );
    set("outdoors", "quanzhou");
    set("no_clean_up", 0);
    set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"nanmen",
  "south" : __DIR__"yucun",
]));
    setup();
    //replace_program(ROOM);
}

void init()
{
	object me=this_player();

	if(userp(me))
	add_action("discmds",({"touxi"}));
}

int valid_leave(object me, string dir)
{
	object ob;
	me=this_player();

	if(dir=="south")
	{
		if(!me->query("xy_huiyuan") && me->query("combat_exp") < 200000)
			return notify_fail("你的实战经验不足，还是不要去那种人蛇混杂的地方为妙。\n");
		
		if(me->query_temp("apply/name") && userp(me))
			return notify_fail("商业买卖、信用行首，还是不要戴面具的好吧？\n");

	ob=first_inventory(me);
    while(ob)
		{
		if (ob->is_character() && !ob->is_corpse() )
			return notify_fail("还是把"+ob->name()+"先放下来再去贩盐吧！\n");
		ob=next_inventory(ob);
		}
	}

	return ::valid_leave(me, dir);
}

int discmds()
{
	tell_object(this_player(),"大胆！商业交易场所也敢行凶？\n");

	if(!this_player()->is_busy())
	this_player()->start_busy(5);
	return 1;
}
