// gangjian.c

#include <weapon.h>
inherit DAGGER;

void create()
{
	set_name("��ͨذ��", ({ "bishou" }));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����ͨ��Сذ�ס�����������˱ȽϺ��ʡ�\n");
		set("value", 2000);
		set("material", "steel");
		set("wield_msg", "$N�Ӷ����ͳ�һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n�Żᶵ�\n");
	}
        init_dagger(30,2);
	setup();
}
int query_autoload() { return 1; }