#include <ansi.h>
inherit ITEM;

void create()
{
     set_name(HIY"��Կ��"NOR, ({"jin yaoshi","gold key", "key"}));
     set_weight(10);
          if (clonep())
           set_default_object(__FILE__);
     else {
           set("unit", "��");
           set("long", "����һ�ѻƽ�Կ�ף���������ģ��ƺ��͹�Ĺ��ĳЩ�����йء�\n");
           set("value", 1000);
           setup();
          }
}
int query_autoload() { return 1; }