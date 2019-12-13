#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIB"龙丹"NOR, ({ "dragon dan" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","听说这个丹的功效和龙元的功效一样,不知道是不是真的!\n");
                set("unit", "颗");
                set("value", 50000);
                set("no_drop",1);
        }
        setup();
}

void init()
{
  if(this_player()==environment())
  add_action("boost_skill","eat");
}

int boost_skill()
{
        int force_limit, neili_limit, force_skill;

        object ob;
        string theskill;
        int thelevel = 0;
        mapping skl, lrn, map;
        string *sname, *mapped;
        int i;
        ob = this_player();
        skl = ob->query_skills(); 

        force_limit = ob->query_skill("force")*10;
        neili_limit = ob->query("max_neili");
        force_skill = ob->query_skill("force", 1); 

        if(!sizeof(skl)) {
                write( "你目前并没有学会任何技能。\n");
                return 1;
        }
        sname  = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);

       for(i=0; i<sizeof(skl); i++) {
                if(skl[sname[i]] > thelevel) {theskill = sname[i]; thelevel = skl[sname[i]];} 
        }
        ob->set_skill(theskill, (int)thelevel+1);
message_vision(HIG"$N的"+to_chinese(theskill)+"增强了。\n"NOR, this_player());
destruct(this_object());
return 1;
}

