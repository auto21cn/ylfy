// chuji_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(HIY"秦风宝箱"NOR,({"boxno1"}));
        set_weight(500);
        
        if( clonep() )
                set_default_object(__FILE__);
        else
       {
            set("long",
                "这是系统奖励的"+this_object()->query("name")+",使用(openbox boxno1)打开看看!\n");
        set("unit","个");
        set("value", 1000000);
        }
}
void init()
{
    if (environment()==this_player())
    add_action("do_openbox","openbox boxno1",1);
}
//打开宝箱的函数
int do_openbox()
{
   int i;
   int num=1;
   object ob;
   
   string *box=
({
"/clone/suit/qinfeng/qf-armor","/clone/suit/qinfeng/qf-boots","/clone/suit/qinfeng/qf-cloth","/clone/suit/qinfeng/qf-hand","/clone/suit/qinfeng/qf-head","/clone/suit/qinfeng/qf-neck",
"/clone/suit/qinfeng/qf-pants","/clone/suit/qinfeng/qf-ring","/clone/suit/qinfeng/qf-shield","/clone/suit/qinfeng/qf-surcoat","/clone/suit/qinfeng/qf-waist","/clone/suit/qinfeng/qf-wrists"
});
  
    object me = this_player();
        if (me->is_busy())
              { write("你上一个动作未完成！\n"); return 1;}
        if( me->is_fighting() )
              { write("战斗中开宝箱？挨宰呀？\n"); return 1;}
       
    message_vision(HIG"$N轻轻打开了["+this_object()->query("name")+"]的盖子,宝箱华为一阵金色光华！\n"NOR,me);
    i=random((int)sizeof(box));
    
    ob = new(box[i]); 

   tell_object(me,""HIY"**************************************************************\n");
  tell_object(me,""HIR"<恭喜>: "NOR" 你从["+this_object()->query("name")+"]中得到了..."+chinese_number(num)+ob->query("unit")+HIY+"<< "+ob->query("name")+HIY+" >>"+NOR+"\n");
 tell_object(me,""HIY"**************************************************************\n");
    ob->move(me); 
    destruct(this_object());
        return 1;
}
int query_autoload()
{
        return 1;
}