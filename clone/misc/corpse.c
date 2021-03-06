// 尸体 Write By Wenwu

inherit ITEM;

int decayed;

void create()
{
	set_name("无名尸体", ({ "corpse" }) );
	set("long", "这是一具无名尸体。\n");
	set("no_put",1);
	set("unit", "具" );
	decayed = 0;
	set_heart_beat(90);
}

int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }
int is_container() { return 1; }

string short() { return name() + "(" + capitalize(query("id")) + ")"; }

protected void heart_beat()
{
	object me, env, *inv;
	int i;
	
	me = this_object();
	decayed++;
	
	// 宿主物件
	if ( !clonep(me) ) return;

	if ( !objectp(env = environment()) )
	{ // 没有环境
		destruct(me);
		return;
	}

	switch ( decayed ) 
	{
		// 开始腐烂
		case 1:
			me->delete("valid_get_from"); // 清除绑定
			tell_room(env, query("name") + "开始腐烂了，发出一股难闻的恶臭。\n");
			switch ( query("gender") ) 
			{
				// 男尸
				case "男性":
					set_name("腐烂的男尸", ({ "corpse", "尸体" }) );
					break;
				// 女尸
				case "女性":
					set_name("腐烂的女尸", ({ "corpse", "尸体" }) );
					break;
				default:
					set_name("腐烂的尸体", ({ "corpse", "尸体" }) );
			}
			set("long",	"这具尸体显然已经躺在这里有一段时间了，正散发著一股腐尸的味道。\n");
			break;
		// 骸骨
		case 2:
			tell_room(env, query("name") + "被风吹乾了，变成一具骸骨。\n");
			set_name("枯乾的骸骨", ({ "skeleton", "骸骨" }) );
			set("long", "这副骸骨已经躺在这里很久了。\n");
			set("unit", "具" );
			break;
		// 清除
		case 3:
			tell_room(env, "一阵风吹过，把" + query("name") + "化成骨灰吹散了。\n");
			inv = all_inventory(this_object());
			for ( i=0; i<sizeof(inv); i++ ) 
			{
				if ( inv[i] ) inv[i]->move(env);
			}
			destruct(me);
			break;
		default:
			destruct(me);
	}
}

int bind_get(object ob)
{
	object me;
	mixed flag;

	me = this_object();

	if ( !objectp(ob) ) return 0;
	if ( wizardp(ob) ) return 0;
	if ( !(flag = me->query("valid_get_from")) 
		|| !stringp(flag) )
		return 0;
	// 不是自己的，无法拿去
	if ( flag != ob->query("id") ) return 1;

	return 0;
}