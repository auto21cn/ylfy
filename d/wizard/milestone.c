inherit ITEM;

int do_read(string arg);

void create()
{
      

        set_name(RED "※"YEL"江湖纪念碑"RED"※" NOR, ({ "jinian bei","bei" }) );
        
        set("unit", "本");
        set("long", "这是一块用来纪录江湖成名人物的石碑，伴随着江湖的
风风雨雨，岁月的流逝，石碑依旧。而上的名字却换了
一代又一代。石碑上刻录着：
　     一："CYN"江湖"HIY"富豪"NOR+CYN"排行榜"NOR"
　     二："YEL"江湖"HIM"经验"NOR+YEL"排行榜"NOR"
　     三："BLU"江湖"HIC"内力"NOR+BLU"排行榜"NOR"
　     四："RED"江湖"HIW"精力"NOR+RED"排行榜"NOR"
　     五："WHT"江湖"HIR"读书"NOR+WHT"排行榜"NOR"

你可以用(read 标号)来翻看记载。\n");
        
        set("material","steel");
        set_weight(8888888);
		set("no_get",1);
        setup();
}

void init()
{
	add_action("do_read","read");
}

int do_read(string arg)
{
	string str;

	if(!arg || arg=="")
		return notify_fail("你要阅读哪一项排行？\n");
	
	switch(arg)
	{
		case "一": arg ="rich";break;
		case "二": arg = "exp";break;
		case "三": arg = "neili";break;
		case "四": arg = "jingli";break;
		case "五": arg = "dushu";break;
		default : arg = "none";break;
	}
	
	str="/adm/daemons/toptend"->topten_query(arg);
	write(str+"\n");
	return 1;
}
