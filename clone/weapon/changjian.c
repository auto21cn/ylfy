// longsword.c ����
#include <weapon.h>
inherit SWORD;
void create()
{
	set_name("����", ({ "sword","changjian", "jian" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon", "10006");
		set("long", "����һ����ͨ�ľ��ֽ���һ��Ľ��Ͷ�����˽���\n");
		set("value", 100);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
	}
        init_sword(25,2);
	setup();
}
int query_autoload() { return 1; }