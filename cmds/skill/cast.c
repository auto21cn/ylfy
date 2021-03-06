// perform.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object weapon;
    mapping smap;
    string martial, skill, str;
    
    seteuid(getuid());
    
    smap = me->query_skill_map();
    if((int)me->query_temp("no_cast")==1)	
return notify_fail("你现在不能用魔法！\n");	
    if( me->is_busy() )
       return notify_fail("( 你上一个动作还没有完成，不能念咒文。)\n");
if ((int)me->query_temp("in_qingwang")==1)	
return notify_fail(MAG"你眼前出现那个熟悉的身影，搅的你心烦气燥，似离情，剪不断，理还乱。\n"NOR);
if( !wizardp(me) && environment(me)->query("no_fight") )	
return notify_fail("这里不准念咒文。\n");		
    if( !arg ) return notify_fail("你要用咒文做什麽？\n");
    if( sscanf(arg, "%s.%s", martial, str)!=2 ) {
        str=arg;
        if( weapon = me->query_temp("weapon") )
            martial = weapon->query("skill_type");
        else martial = "unarmed";
    }
    if( stringp(skill = me->query_skill_mapped(martial)) ) {
	if (file_size(SKILL_D(skill)->cast_action_file(str)+".c")>0){
        notify_fail("你所学的法术中没有这种功能。\n");	
        if( SKILL_D(skill)->perform_action(me, str) ) {
            if( random(120) < (int)me->query_skill(skill) )
                me->improve_skill(skill, 1, 1);
            return 1;
        } else if( SKILL_D(martial)->cast_action(me, str) ) {
            if( random(120) < (int)me->query_skill(martial, 1) )
                me->improve_skill(martial, 1, 1);
            return 1;
        }
        return 0;
	}
    }
    if( sscanf(arg, "%s.%s", martial, str)!=2 ) {
        str=arg;
        if( weapon = me->query_temp("secondary_weapon") )
            martial = weapon->query("skill_type");
        else martial = "unarmed";
    }
    if( stringp(skill = me->query_skill_mapped(martial)) ) {
       notify_fail("你所学的法术中没有这种功能。\n");	
        if( SKILL_D(skill)->cast_action(me, str) ) {
            if( random(120) < (int)me->query_skill(skill) )
                me->improve_skill(skill, 1, 1);
            return 1;
        } else if( SKILL_D(martial)->cast_action(me, str) ) {
            if( random(120) < (int)me->query_skill(martial, 1) )
                me->improve_skill(martial, 1, 1);
            return 1;
        }
        return 0;
    }
    return notify_fail("你请先用 enable 指令选择你要使用的咒文系。\n");	
}
int help (object me)
{
        write(@HELP
指令格式：cast <咒文名称> [<施用对象>]
施法，你必需要指定<咒文名称>，<施咒对象>则可有可无。	
在你使用某一个咒文之前，你必须先用 enable 指令来指定你要使用的咒文系。
HELP
        );
        return 1;
}
