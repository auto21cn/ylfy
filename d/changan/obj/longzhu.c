//mingzhu.c
inherit ITEM;
void create()
{
        set_name(HIB BLINK "龙珠" NOR, ({ "long zhu" ,"zhu", }) );
        set_weight(100000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long","这是颗龙眼，看来还值几个钱。\n");
                set("value", 1000000);
                set("material", "dainomd");
              }
}
void init()
{
        if (environment()==this_player())
        add_action("do_pushin","pushin");
}
int do_pushin(string arg)
{
        object me=this_player();
        object room=environment(me);
        if(base_name(room) != "/d/changan/dadian3") return 0;
        if (room->query("in_zhu")==2)
                return 0;
        if(!me->query_temp("killer")
        || !me->query_temp("climb")
        || me->query_temp("chan"))
        return 0;
        message_vision("$N捧起一颗"+query("name")+"塞进了石门的洞内。\n",me);
        room->add("in_zhu",1);
        if (room->query("in_zhu")==2){
                room->open_door(me,1);
        }
        destruct(this_object());
        return 1;
}

int query_autoload() { return 1; }