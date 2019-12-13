inherit FORCE;
int valid_enable(string usage)
{
    return usage == "force";
}
int valid_learn(object me)
{
    string master;
    int lvl = (int)me->query_skill("fanyun-force", 1);
    master=me->query("family/master_id");
    
                    
    if ( me->query("gender") == "无性" && lvl > 49)
        return notify_fail("你无根无性，阴阳不调，难以领会高深的翻云神功。\n");
    if ((int)me->query_skill("force", 1) < 30)
        return notify_fail("你的基本内功火候还不够，无法领会翻云神功。\n");
    if (me->query_skill("force",1)<=lvl)
        return notify_fail("你的基本内功基础不够扎实，再学下去会走火入魔的。\n");
 return 1;
}
string exert_function_file(string func)
{
    return __DIR__"fanyun-force/" + func;
}
int practice_skill(object me)
{
        return notify_fail("翻云神功只能用学的，或是从运用(exert)中增加熟练度。\n");
}

