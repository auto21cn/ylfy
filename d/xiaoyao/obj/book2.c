// book0.c
inherit ITEM;
void create()
{
    set_name("�׽��ѧƪ", ({ "shu", "book" }));
    set_weight(50);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "��");
        set("long", "����һ��������С�ᣬ�������������д����ӬͷС�����˹����¡�\n");
        set("value", 500);
        set("no_sell",1);
        set("material", "silk");
        set("skill", ([
            "name": "literate", // name of the skill
            "exp_required": 0,  // minimum combat experience required
            "jing_cost":    0,  // jing cost every time study this
            "difficulty":   0, // the base int to learn this skill
"max_skill":    100  // the maximum level you can learn
        ]) );
    }
}
int query_autoload() { return 1; }