
#include <ansi.h>
#include <room.h>

int discmds();
inherit ROOM;

void create()
{
        set("short",HIY "【 会议厅 】" NOR);
        set("long", 
""HIC"  这里便是夕阳再现巫师组开会的地方，有很多决策都在这里经过讨论而决定，	
  看着眼前"HIM"“ 会议厅”"NOR""HIC"三个朱色大字，给人一种庄严的"NOR"\n"
""HIR"感觉，你不知不觉加快了脚步。"NOR"
              "HIM"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
              　         "HIG"会          议           厅            　
　            　                                 "HIB"--"BLINK+HIY"夕阳再现"HIW"  "NOR+HIM" 题㊣　	
              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"NOR"\n"
                                                                                                               

        );


         set("objects",([
 //  "/d/wizard/guanjia" : 1,
//   "/d/wizard/mishu" : 1,
           ]));
         set("exits",([
			 "west" : __DIR__"wizard_room",
			 ]));
		 set("objects", ([
			 "/d/wizard/npc/player":1,
			 ]));
         set("no_sleep", 1);
         set("valid_startroom",1);
         set("no_fight",1);
         set("no_steal",1);
         setup();  
         call_other("/clone/board/towiz_b", "???");	
                          
}

void init()
{
    if(!wizardp(this_player())) {
        "/cmds/std/look"->look_room(this_player(),this_object());
// this_player()->set("startroom", __FILE__);
       add_action("discmds",({"es","quit","goto","home","summon","kickout","dest","snoop","sleep","kill","fight","hit","chat","chat*","rumor","rumor*","tell","reply","to","new","go","new*"}));
        }
}

int discmds()
{
        tell_object(this_player(),HIY"现在正在开会，还是乖乖的呆在这等候指示吧！！！\n"NOR);
        return 1;

}
