// Room: /d/wudie/cdt.c
// This is a room made by roommaker. write by Xyx.

inherit ROOM;

void create()
{
        set("short", "彩蝶堂");
        set("long", @LONG
这就是艳蝶堂了，这里什么也没有，只是墙上挂着一副画，画着一
美丽女子，相传就是香香公主，画上还题了一首陈家洛为了祭香香公主
的诗：“浩浩愁，茫茫劫，短歌终，明月缺。郁郁佳城，中有碧血。碧
亦有时尽，血亦有时灭，一缕香魂无断绝！是耶非耶？化为蝴蝶。”
LONG
);
        set("noon", "正午时分堂外花香散近来，配合堂里彩蝶的装饰给人脱俗的感觉。
");
        set("morning", "早晨的空气清新阳光洒满大地，小鸟在枝头鸣唱。
");
        set("sunrise", "此时的太阳一悄悄挂在东方天际，金色的阳光透过窗户射了进来。
");
        set("dawn", "黎明前堂里没有人影。蜡烛已经燃尽看不太清堂里的装饰。
");
        set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"wdt",
  "north" : __DIR__"dyt",
]));
        set("no_clean_up", 0);
        set("midnight", "闪闪烛光拌着深夜的来到，静静的毫无声响。
");
        set("night", "夜晚浓浓花香拌着悦耳琴音让人忘记俗世里的一切。
");
        set("evening", "傍晚的花香特别浓，随香望去堂外花园万只蝴蝶偏偏起舞。
");
        set("afternoon", "午后的阳光懒懒的散进堂内洒在你的身上柔柔的暖暖的。
");

        setup();
        replace_program(ROOM);
}
