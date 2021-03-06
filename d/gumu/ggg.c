
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIC"休息室"NOR);
	set("long", @LONG
这里是古墓弟子的休息室，房中空空洞洞，一如古墓无异。一块长条青石
作床，床上铺了张草席，一幅白布当作薄被，此外除了一根人高的绳索横过室
中，别无他物。
LONG
);

	set("exits", ([
		"north" : __DIR__"gmht",
	]));

	set("objects", ([
		__DIR__"obj/bed" : 1,
	]));

	set("sleep_room", 1);
	set("no_fight", 1);

	create_door("north", "石门", "south");
	setup();
}

void init()
{
	add_action("do_zuo", "zuo");
	add_action("do_liao", "liao");
}

int do_zuo(string arg)
{
	mapping fam;
	object me = this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
		return notify_fail("你不是古墓传人，如何能领悟古墓武功？\n");
	if (arg == "bed"){
		if (me->query("qi") < 40 )
			return notify_fail("你的气太少，无法抵御严寒。\n");
		if ( me->query("potential") - me->query("learned_points") < 1 )
			return notify_fail("你的潜能没了，不能再继续修习了\n");
		write(HIC"你往寒玉床上盘腿而坐。\n"NOR);
		if (me->query_skill("force", 1) < 20){
			message_vision(HIR"$N还未坐稳,就怪叫一声, 从床上跳了下来，想必是受不了千年古玉之寒气。\n"NOR, me);
		return 1;
	}
        if ((me->query("potential") - me->query("learned_points")) < 0)
        	return notify_fail("你的潜能不够了。\n");
	if (me->query_skill("yunv-xinjing", 1) > 50)
		return notify_fail("你的玉女心经已有相当火厚,寒玉床不能再助你修习内功了。\n");
		write("借寒玉床之天然神效，真气自然流动，你开始修习内功心法，当真灵验无比。 \n"NOR);
		me->receive_damage("qi", 10 + random(15));
		me->add("potential", -1);
		me->start_busy(random(2));
		me->improve_skill("yunv-xinjing", (int)(me->query_int()/2) +
		(int)(me->query_con()/2) );
		return 1;
	}
	return notify_fail("你要坐在哪里? \n");
}

int do_liao(string arg)
{
	object me = this_player();

	if (me->is_fighting() || me->is_busy())
		return notify_fail("你正忙着呢。\n");
	if ((int)this_player()->query("eff_qi") == (int)this_player()->query("max_qi"))
		return notify_fail("你现在身上没有受到任何伤害！\n");
	if ( (int)me->query_condition( "marks_bed" ) > 0 ){
		me->receive_wound("qi", 10);
		message_vision(HIR"$N突然只觉一阵奇寒侵入身体，想是两次疗伤时隔太短，身子尚未复原之故。\n"NOR, me);
		me->unconcious();
		return 1;
	}
	if (arg == "bed") {
		message_vision(HIY"$N爬上寒玉床, 要借千年寒玉疗伤. \n"NOR, me);
		if (me->query_skill("yunv-xinjing", 1) < 40)
			return notify_fail("寒玉床疗伤需以纯熟的玉女心经内功相辅, 否则无法外疗. \n");
		me->set("eff_qi", me->query("max_qi"));
		me->apply_condition("marks_bed", 25);
		return 1;
	}
	return notify_fail("你要在哪疗伤? \n");
}
