// ë�� /clone/eat/food/mao_sun.c
// by lala, 1997-12-16

#include <ansi.h>

inherit ITEM;

inherit F_FOOD;

void create()
{
    set_name( RED"��Ϻ"NOR, ({"yu5"}) );
    set_weight( 30000 );
    if ( clonep() )
            set_default_object( __FILE__ );
    else {
        set( "long", @LONG
һֻ��Ϻ�������ʣ������ɿڣ��Ǻ��ϵ��ز���
LONG
        );
        set( "unit", "ֻ" );
	set( "icon", "05011" );
		set("no_drop","��Ҫ�Ҷ����ⶫ������ʹ��\n");
		set("no_get",1);
		set("no_give",1);
		set("no_steal",1);

		set("no_put",1);

        set( "value", 500 + random( 600 ) );
        set( "food_remaining", 5 );
        set( "food_supply", 25 );
    }
}

int do_eat( string arg )
{
    return notify_fail("�⻹�����ģ�ֻ����è�ſϳԡ�\n");
}