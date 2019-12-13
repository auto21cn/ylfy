// Room: xiuxishi.c
// By Marz
inherit ROOM;
void init();
void close_men();
int do_open(string);
int do_close(string);
void create()
{
        set("short", "��Ϣ��");
        set("long", @LONG
���Ǽ�������᷿������(men)�������ţ����ߺܻ谵������������
ֻ���м����һ����ʰ����������Ĵ󴲣����ž�������˯����
LONG
        );
        set("sleep_room", 1);
        set("no_fight", 1);
        setup();
}
void init()
{
    add_action("do_open", "open");
    add_action("do_close", "close");
}
void close_men()
{
    object room;
    if(!( room = find_object(__DIR__"liantai")) )
        room = load_object(__DIR__"liantai");
    if(objectp(room))
    {
        delete("exits/east");
            message("vision", "��֨֨ѽѽ���Լ������ˡ�\n", this_object());
        room->delete("exits/west");
        message("vision", "��֨֨ѽѽ���Լ������ˡ�\n", room);
    }
}
int do_close(string arg)
{
    if (!query("exits/east"))
        return notify_fail("���Ѿ��ǹ��ŵ��ˡ�\n");
    if (!arg || (arg != "men" && arg != "door"))
        return notify_fail("��Ҫ��ʲô��\n");
    message_vision("$N����Ź��ϡ�\n", this_player());
    remove_call_out("close_men");
    call_out("close_men", 2);
    return 1;
}
int do_open(string arg)
{
    object room;
    object me = this_player();
    if (query("exits/east"))
        return notify_fail("�����Ѿ��ǿ����ˡ�\n");
    if (!arg || (arg != "men" && arg != "door" && arg != "west"))
        return notify_fail("��Ҫ��ʲô��\n");
    if(!( room = find_object(__DIR__"liantai")) )
        room = load_object(__DIR__"liantai");
    if(objectp(room))
    {
        set("exits/east", __DIR__"liantai");
        message_vision("$N������ŵذ��Ŵ򿪡�\n", this_player());
        room->set("exits/west", __FILE__);
        
        if (me->query_temp("sleeped"))
        {
        message("vision", "֨��һ����"+me->query("name")+"��������ش�������Ŵ��ˡ�\n",
        room);
        } else 
        {
        message("vision", "���һ����"+me->query("name")+"��������Ŵ򿪣�һ���Ĳ��ͷ���\n",
             room);
        }   
        
        remove_call_out("close_men");
        call_out("close_men", 10);
    }
    return 1;
}
int valid_leave(object me, string dir)
{
    object room;
    if ( !::valid_leave(me, dir) ) 
        return 0;
    
    if(!(room = find_object(__FILE__)) )
        room = load_object(__FILE__);
    if(objectp(room))
    {
        room->add_temp("person_inside", -1);    
        if ((int)room->add_temp("person_inside", -1) <= 0)
            room->delete_temp("person_inside"); 
    }
    
    return 1;
}