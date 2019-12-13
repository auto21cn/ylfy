// Room: room11.c
inherit ROOM;
int do_pull(string);
void create()
{
        set("short", "����֮��");
        set("long", @LONG
����ǰ��һƬһ���޼ʵ�«έ��������Զ����«έһֱ���ӵ���
�ߣ�����Ե��ر�Ͱ���«έ�е�ˮ�ݷ�������Ķ����ˮ���«έ
���ƺ���Щ���������������ٴ˵أ�ʹ�˸е�һ��Ī���Ŀ־塣
LONG
        );
        set("exits", ([ 
  "east" : __DIR__"room8",
  "north" : __DIR__"huozhao4",
  "south" : __DIR__"room12",
]));

        setup();
}
void init()
{
        object me=this_player();
        add_action("do_pull", "pull");
        if (random(me->query("kar"))<10){
            message_vision(RED "$N����ͻȻ�³�... ...\n" NOR,me);
            me->set_temp("drop_zhaoze",1);
        }
}
int do_pull(string arg)
{
    object ob;
    object me = this_player(); 

    if (!arg)
        return notify_fail("��Ҫ��˭��\n");

    if (!ob = present(arg,this_object()))
        return notify_fail("��Ҫ��˭��\n");

    if (me->query_temp("drop_zhaoze"))
        return notify_fail("���Լ��������ѱ��ˣ����������ˣ�\n");

    if (!ob->query_temp("drop_zhaoze"))
        return notify_fail(ob->name()+"����������\n");

    message_vision("�㳶ס$N���֣�ʹ����$n����������\n",me,ob);
    ob->delete_temp("drop_zhaoze");
    return 1;
}
int valid_leave(object me, string dir)
{
        if (dir=="south" && me->query_temp("drop_zhaoze")){
                message_vision("$Nʹ������һ�£���ͼ������̶.....\n",me);
                if (random(10)>5){   
                        me->apply_condition("scorpoin_poison",20);
                        tell_object(me,RED "\n��ͻȻ���ýű�ʲô��������һ��... ...\n" NOR);
                }
                if (random(me->query_skill("dodge",1))>600){
                        message_vision("$N����һ�ݣ�Ծ����̶��\n",me);
                        return 1;
                }else{
                        message_vision("$N���Խ��Խ�\n",me);
                        me->set_temp("die_for","�ݽ�������");
                        me->receive_wound("qi",200);
                       return notify_fail("���������󣬶������á�\n");
                }
        }
        return 1;
}