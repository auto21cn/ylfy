inherit ITEM;
#include <task.h>
void create()
{
        set_name("ˮ��", ({"shui hu", "hu"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "�����õ�ˮ����\n");
                set("unit", "��");
               set("owner_name","����");
               set("owner_id","xu zhu");
        }
}