// gems - by xbd

#include <ansi.h>

inherit ITEM;
inherit F_GEMS;
inherit F_SAVE;

void create()
{
	int lev, i;
	string gem;

	i = random(17);
	if (i < 3) gem = "ruby";
	else if (i < 6) gem = "topaz";
	else if (i < 9) gem = "sapphire";
	else if (i < 12) gem = "emerald";
	else if (i < 15) gem = "amethyst";
	else if (i < 16) gem = "diamond";
	else gem = "skull";

	i = random(1000);
        if (i < 500) lev = 1;
        else if (i < 600) lev = 2;
        else if (i < 700) lev = 3;
        else if (i < 880) lev = 4;
        else if (i < 900) lev = 5;
        else if (i < 950) lev = 6;
        else if (i < 990) lev = 7;
        else lev = 8;

	set_name(query_gem_name(gem, lev), ({query_gem_id(gem, lev)}));
	set_weight(100);
	set("long", query_all_effect(gem));
	set("unit", "��");
	set("no_put",1);
	set("buy_sell",1);
    set("no_sell",1);	
	set("liebiao_gem",1);
	set("no_beg",1);
    set("owner_id",1);
	set("xyzx_save_item", 1);
	set("no_steal",1);
    set("no_clone",1);
    set("no_pawn",1);
	set("value", 100000 * lev * lev * lev);
	set("material", gem);
	set("level", lev);
	setup();
}

void init()
{
	add_action("do_insert", "insert");
	add_action("do_combine", "combine");
}

int do_insert(string arg)
{
	mapping is_bind;
	int index, i, sockets;
	string gem, item_name;
	object ob, me = this_player();

	if (!arg || arg == "")
		return notify_fail("ָ���ʽ��insert ��ʯ into ��Ʒ at socket ���\n");
	if (sscanf(arg, "%s into %s at socket %d", gem, item_name, index) != 3)
		return notify_fail("ָ���ʽ��insert ��ʯ into ��Ʒ at socket ���\n");
	if (gem != query("id")) return 0;
	if (!objectp(ob = present(item_name, me)))
		return notify_fail("���������Ƕ��ʲô�����ϣ�\n");
	if (index > ob->query("sockets/max"))
		return notify_fail(ob->name() + "�Ϻ���û������ӿ�ѽ��\n");
	if (ob->query("equipped"))
		return notify_fail(ob->name() + "��װ�����أ�\n");
	if (me->query("max_neili") < 1000 || me->query("neili") < 1500)
		return notify_fail("�������ڵ�������Ϊ�����޷��˹���Ƕ��ʯ��\n");

	// �󶨵ı����޷�ʹ��
	if ( mapp(is_bind=query("bind_master_level")) 
		&& !is_bind[me->query("id")] )
		return notify_fail("���Ǳ��˵�˽����Ʒ���޷�ʹ�á�\n");

	//����Ƕ��ʯÿ����Ʒֻ����һ�����͵ı�ʯ�����Բ�ͬ�ȼ�
	sockets = ob->query("sockets/max");
	for (i = 1; i <= sockets; i++)
	{
		if ( strsrch(query("id"),ob->query(sprintf("sockets/socket%d", i))) != -1 && i !=index )
			return notify_fail(ob->name() + "�޷�ͬʱǶ����ͬ�����͵ı�ʯ���ڵ�" + i + "�ӿ�����Ƕ���������͵ı�ʯ�ˡ�\n" + 
			"����԰ѵ�" + i + "�ӿ���Ƕ�еı�ʯ�滻Ƕ�����������ʯ��");
	}

	message_vision(HIG"$N����������һʹ����" + name() + HIG"������" + ob->name() + HIG"�У�
ɲ�Ǽ䣬ֻ��" + ob->name() + HIG"�Ϸ���һ������Ĺ�â���ƺ���һ������������������У�\n", me);
	me->add("max_neili", -100);
	me->add("neili", -1000);
	me->start_busy(2);
	ob->set(sprintf("sockets/socket%d", index), query("material"));
	ob->set(sprintf("sockets/socket%d_level", index), query("level"));

	// �󶨵ı�ʯ��Ƕװ������ôװ��Ҳ�ᱻ��
	if ( mapp(this_object()->query("bind_master_level")) ) {
		ob->set("bind_master_level/"+me->query("id"), 1);
		ob->set("owner_id",1);
		ob->set("xyzx_save_item", 1);
	}

	seteuid(ROOT_UID);
	reload_object(ob);
        seteuid(getuid());
	destruct(this_object());

	return 1;
}

int do_combine(string arg)
{
	string name, mat;
	int i, lvl, flag, bind_flag;
	object *inv, gem, baoshi, me = this_player();

	if ( !arg || arg == "" ) return notify_fail("����ϲ�ʲô��ʯ��\n");
	if ( arg != query("id") ) return 0;
	if ( (lvl=query("level")) >= 8 ) return notify_fail("�����ʯ�Ѿ�����ߵȼ��ˣ�\n");
	if ( me->query("max_neili") < 500000 || me->query("neili") < 800 ) 
		return notify_fail("�������ڵ�������Ϊ�����޷��˹��ϲ���ʯ��\n");

	inv = all_inventory(me);
	for ( i = 0; i < sizeof(inv); i++ )
	{
		if ( inv[i] != this_object() && inv[i]->query("id") == query("id") ) 
		{
			if ( !objectp(gem) )
				gem = inv[i];
			else 
			{
				me->add("max_neili", -random(900));
				me->add("neili", -500);
				me->start_busy(1);
				name = name();
				mat = query("material");

				// �󶨵ı�ʯ��Ƕװ������ôװ��Ҳ�ᱻ��
				bind_flag = 0;
				if ( mapp(this_object()->query("bind_master_level")) 
					|| mapp(gem->query("bind_master_level")) 
					|| mapp(inv[i]->query("bind_master_level")) ) {
					bind_flag = 1;
				}

				if ( random(10) > lvl )
				{
					destruct(gem);
					destruct(inv[i]);
					message_vision(HIG"$N����������͸��ʯ������" + name + 
						HIG"�������������������$N�ջ���������ֻ��" + name + HIG"�ƺ���ø��������ˣ�\n", me);
					baoshi = new_gem(mat, lvl + 1);
					if ( bind_flag == 1 )
						baoshi->set("bind_master_level/"+me->query("id"), 1);
					baoshi->move(me);
					destruct(this_object());
				}
				else
				{
					flag = random(3);
					message_vision(HIW"$N����������͸��ʯ������" +  
						HIW"�����ꡱ����������" + 
						chinese_number(flag+1) + "��" + name + 
						HIW"����ס�ھ��Ĵ߶��ȱ������˿˿��ĩƮ�¡�\n", me);
					switch ( flag )
					{
						case 2 : destruct(gem);
						case 1 : destruct(inv[i]);
						case 0 : destruct(this_object());
					}
				}
				return 1;
			}
		}
	}
	return notify_fail("�����������ͬ���ı�ʯ���ܽ��кϲ���\n");
}