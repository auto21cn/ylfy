//yitianjian.c
#include <weapon.h>

inherit SWORD;

void create()
{
    set_name("���콣", ({ "yitian jian", "yitian","jian" }) );
    set_weight(20000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
        	set("unit", "��");
		set("icon", "10016");
        	set("value", 50000);
//        	set("no_drop", "1");
        	set("material", "iron");
        	set("long", "�������µ�һ�������С����첻����˭�����桱֮˵��\n");
        	set("wield_msg","ֱ�������ˮ���������һ�㣬$n����$N���У����Ϊ֮��ɫ��\n");
        	set("unwield_msg", "$N��$n������䣬�����������ؼ�ֻ��������\n");
	}
    	init_sword(500);
	setup();
}
int query_autoload() { return 1; }	