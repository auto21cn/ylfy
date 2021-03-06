
// Create by rongg@XBTXIII
// diviemagic.c
// 神圣魔法.传说中的大魔法师恩利斯使用的魔法,该魔法一千年以来一直由迷雾岛的精灵们掌握.
// 拥有该魔法的魔法师必须由迷雾岛的精灵们挑选,一旦获得修习该魔法的资格,也意味着此人肩负
// 起了保卫迷雾岛的责任.
// 神圣魔法有7个攻击型魔法 终极魔法1个,5割辅助魔法
// 0-40 暴风弹 40-80 风牙  80-120 光歼破弹 120-150 风曜十字斩
// 150-180  流星风暴 180-250 以太风暴
// 终极魔法 250 辉耀天堂
// 辅助性魔法 治愈术10 魔法盾 移动法愿 精灵魔法(召唤) 瞬间移动(200) 天眼通
inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage=="magic"; }

int valid_learn(object me)
{
	if( (int)me->query_skill("spell",1) < (int)me->query_skill("divinemagic")/2 )
		return notify_fail("你的基本法术修为不够，无法领悟更高深的神圣魔法。\n");
	return 1;
}

string cast_spell_file(string spell)
{
	return CLASS_D("divine") + "/divinemagic/" + spell;
}

string scribe_spell_file(string spell)
{
	return CLASS_D("divine") + "/divinemagic/" + spell;
}

int practice_skill(object me)
{	

	if( (int)me->query("mana") < 10 )
		return notify_fail("你的法力不够。\n");

	if( (int)me->query("sen") < 30 )
		return notify_fail("你的精神无法集中。\n");

	me->add("mana", -10);
	me->receive_damage("sen", 30);

	write("你闭上双眼,回忆起记忆深处神圣魔法的某些咒语......\n");
	return 1;
}
void skill_improved(object me)
{
        int s;
    if( (int)me->query_skill("magic",1) < 10
    ||  (int)me->query_skill("magic",1) <= (int)me->query_skill("divinemagic",1) )
        {
        s = (int)me->query_skill("divinemagic",1);
        me->set_skill("divinemagic",s-1);
        tell_object(me,"神圣魔法咒语的某些字句太深奥了,你一直无法领会\n");
        }
}
