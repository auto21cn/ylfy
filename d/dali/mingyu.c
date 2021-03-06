// Room: /d/dali/mingyu.c
// Data: 哈迪斯(hades)
// Time: 公元：1999年4月19日，北京时间：21时18分3秒。

inherit ROOM;

void create()
{
	set("short", "鸣玉坊外");
	set("long", @LONG
此楼虽不在京都，但却是大理最有名的青楼。这里有最贵的酒，也是最好的酒；
这里有最贵的女人，也是最有味儿的女人；这里有最贵的服务，也是最好的服务。
朱红大门上牌（ｓｉｇｎ）一块，又高悬一块御赐金匾：
[1;35m
			春色无边
[2;37;0m
LONG
	);
	set("item_desc", ([ /* sizeof() == 1 */
  "sign" : "鸣玉坊坊规：
１．不可夹带任何兵器入楼。
２．以防您被鸣玉坊小姐误认为没有消费能力，
　　不可夹带任何食物，酒水入楼。
３．大家出门在外是朋友，相互给点面子，
　　打架，闹事者楼规处置。
４．＂赏头＂给得越多，您受的伺侯越好。
",
]));
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"xidajie2",
  "south" : __DIR__"pingfeng",
]));

	set("objects", ([ /* sizeof() == 2 */
         __DIR__"npc/guinu" : 2,
]));

	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
	object *inv;
	int i;
        if( dir == "south" &&  ob = present("guinu",this_object()))
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("weapon_prop") && (inv[i]->query("equipped")))
			return notify_fail(ob->name()+"向你笑道：鸣玉坊有鸣玉坊的规矩，您请看牌．\n");
			if((int)inv[i]->query("food_remaining") != 0)
			return notify_fail(ob->name()+"向你笑道：鸣玉坊有鸣玉坊的规矩，您请看牌．\n");
			if((int)inv[i]->query("liquid/remaining") !=0)
			return notify_fail(ob->name()+"向你笑道：鸣玉坊有鸣玉坊的规矩，您请看牌．\n");
			if((int)inv[i]->is_container()) 
//			if(check_container(inv[i]))
			return notify_fail(ob->name()+"向你笑道：鸣玉坊有鸣玉坊的规矩，您请看牌．\n");
		}
        me->set("food",0);
        me->set("water",0);
        }
	return 1;
}

int check_container(object ob)
{
object *inv;
int i;
inv = all_inventory(ob);
 for(i=0; i<sizeof(inv); i++)
 {
                        if(inv[i]->query("weapon_prop"))
                        return 1;
                        if(inv[i]->query("food_remaining") != 0)
                        return 1;
                        if(inv[i]->query("liquid/remaining") !=0)
                        return 1;
                        if(inv[i]->is_container()) 
                        if(check_container(inv[i]))
                        return 1;
 }
return 0;
}
