// 宝箱

#include <ansi.h>
inherit ITEM;
int do_open(string arg);
             
void create()
{
	set_name(HIG"宝箱"NOR, ({"bao xiang", "bao", "xiang"}));        
	set_weight(100);
	set_weight(10);
    set("icon","00012");
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个用红木制作而成的"+HIG"宝箱，"NOR+"似乎可以打开(openbox)获得意想不到的物品。\n");
		set("unit", "个");
		set("value", 100000000);
	}
}


void init()
{
   add_action("do_open","openbox");
}

int do_open(string arg)
{ 
    object me=this_player(),ob;
        if(me->query("gender")=="男性")
    tell_object(me,"你迫不及待地将"+HIG+"宝箱"NOR+"打开，\n");
        else
    tell_object(me,"你小心翼翼地将"+HIY+"宝箱"NOR+"打开，\n");

    if( me->over_encumbranced() )
    return notify_fail("身上带的东西太多了，拿不动了。\n");

    /*if(random(300) < 3)
      {
        ob=new("clone/tzbox/qf-box");        
        ob->move(me);
        tell_object(me,"发现了一个"+HIY"秦风宝箱"NOR+"。\n"NOR);
      } */ 
    else if(random(300) < 299)
      {
        ob=new("clone/money/thousand-gold.c");        
        ob->move(me);
        tell_object(me,"发现了一张"+YEL"一千两金票"NOR+"。\n"NOR);
      }  
	else if(random(300) < 10)
      {
        ob=new("clone/map/obj/fangbao-fu.c");       
        ob->move(me);
        tell_object(me,"发现了一张"+HIM"防爆符"NOR+"。\n"NOR);
      }  
	else if(random(300) < 20)
      {
        ob=new("clone/map/obj/longwen-chijin.c");       
        ob->move(me);
        tell_object(me,"发现了一块"+CYN"龙纹赤金"NOR+"。\n"NOR);
      }   	
    else if(random(300) < 4)
      {
        ob=new("clone/map/obj/bangding-stone.c");       
        ob->move(me);
        tell_object(me,"发现了一张"+MAG"绑定石"NOR+"。\n"NOR);
      }  
    else if(random(300) < 150)
      {
        ob=new("clone/winbox/box.c");       
        ob->move(me);
        tell_object(me,"发现了一个"+HIG"宝箱"NOR+"。\n"NOR);
      }  	  
	destruct(this_object());         
        return 1;
} 