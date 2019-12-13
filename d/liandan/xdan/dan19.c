inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIM"技能丹"NOR, ( {"jineng dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "颗");
		set("long", "这是一颗黑呼呼的药丸。\n");
	}
}
int do_eat(string arg)
{
	string *skills;
	mapping all_skills;
	int i;
	if (!id(arg))
		return notify_fail("你要吃什么药？\n");
	else
	{
    if(this_player()->query("id")==query("value"))
        return notify_fail("这棵丹不是你练的,你吃个什么劲。\n");

		all_skills=this_player()->query_skills();
		if (!sizeof(all_skills))  destruct(this_object());
		skills=keys(all_skills);
		for(i=0; i<sizeof(skills); i++)
			this_player()->set_skill(skills[i],all_skills[skills[i]]+1);

		message_vision(HIB"$N吃下一颗技能丹,感觉武功有所提升。\n", this_player());

		destruct(this_object());
		return 1;
	}
}


