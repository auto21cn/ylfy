//item.c
//物品下线存档

#include <dbase.h>
#include <move.h>
#include <name.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

void setup()
{
	seteuid(getuid());
}

int query_autoload()
{
	//不需要存档物品标号
	if ( this_object()->query("owner_id") )
		return 0;
	else
		return 1;
}