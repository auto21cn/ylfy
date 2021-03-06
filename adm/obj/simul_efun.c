#include <liebiao.h>

void create() 
{
	seteuid( ROOT_UID );
	write("simul_efun 成功加载.\n");
}

#include "/adm/simul_efun/atoi.c"
#include "/adm/simul_efun/chinese.c"
#include "/adm/simul_efun/gender.c"
#include "/adm/simul_efun/object.c"
#include "/adm/simul_efun/path.c"
#include "/adm/simul_efun/wizard.c"
// This must be after gender.c
#include "/adm/simul_efun/message.c"
#include "/adm/simul_efun/file.c"
#include "/adm/simul_efun/player.c"
#include "/adm/simul_efun/item.c"
// This is the utilitis
#include "/adm/simul_efun/util.c"
#include "/adm/simul_efun/config.c"

varargs object snoop(object who, object target) 
{
	if(!target)
		return efun::snoop(who);
	
	if(!wizardp(who))
		return 0;
	
	log_file("snoop", who->name() + " snoops " + target->name() + " at " + ctime(time()) );
	return efun::snoop(who, target);
}

void shutdown(int etc)
{
	if( base_name(previous_object()) != NATURE_D && base_name(previous_object()) != "/adm/daemons/automap" )
		return 0;
	else
		efun::shutdown(etc);
}

void destruct(object ob)
{
    string err, name;
	object env, *temp;
	int i;

    if ( objectp(ob) )
    {
        if ( previous_object() )
            err = catch(ob->remove( geteuid(previous_object()) ));
        else
            err = catch(ob->remove(0));
        
		if ( err )
        {
            if ( userp(ob) && geteuid(previous_object()) != ROOT_UID )
               return;
        }

		if ( clonep(ob) && objectp(env = environment(ob)) )
		{
			//Tomud列表删除
			//------------------------------------------------------
			//过滤，只传回目前的可互动物件
			if(interactive(env)) 
			{
				if(!env->query("xieyi/zmud"))
				{
					//删除物品栏里的列表图标
					tell_object(env,REM1(ob));
				}
			}
			else if(!env->is_character())
			{
				//同环境下的所有物件
				temp=all_inventory(env);
				for(i=0;i<sizeof(temp);i++)
				{
					if (temp[i] == ob)
						continue;
					if(!temp[i]->query("xieyi/zmud"))
					{
						if (interactive(temp[i]))
							tell_object(temp[i],REM0(ob));
					}
				}
			}
		/*
	解决destruct物件后该物件的携带重量附加给其它环境的BUG 
	比如追杀NPC后玩家捡尸体回去交差，此时尸体内有物件未清理，产生携带重量，做以下处理后此负重累加BUG消失
*/			
			if (ob->query_encumbrance() > 0)
				env->add_encumbrance( -ob->query_encumbrance());
			
			if (ob->is_character())//有大量未经过die()函数便清除的生物，此时需要清除仇恨
				all_inventory(environment(ob))->remove_killer(ob);//解除仇恨
		}
		
		//玩家退出游戏时，清除所有在线玩家的who列表里该玩家的图标
		if(playerp(ob))
		{
			temp=users();
			for(i=0;i<sizeof(temp);i++)
			{
				if(!temp[i]->query("xieyi/zmud"))
				{
					tell_object(temp[i],REM2(ob));
				}
			}

			auto_save_item(ob);

			// 组队清除
			if ( stringp(name = ob->query_temp("xyzx_team/name")) )
				TEAMD->del_team_member(ob);
			/*if ( (ob->query("vrm_in_busy") > time() && !ob->query_temp("no_end_save")) 
				|| objectp(environment(ob)) )*/
			if ( !ob->query_temp("no_end_save") 
				&& objectp(environment(ob)) 
				&& ob->query_temp("save_end_time") != time() )
				ob->save();

			//if ( in_input(ob) ) remove_input_to(ob);
		}

        efun::destruct(ob);
    }
}
//void replace_program(string arg) { return; }
