// Room: /d/taishan/.c
// Date: CSWORD 96/03/25
inherit ROOM;
void create()
{
    set("short", "封禅台");
    set("long", @LONG
如今这里是推选天下武林总盟主之处，各路英雄如能技压群雄，
比武夺魁，便能问鼎盟主宝座，成为统领中原武林的领袖。高台上
摆放着汉白玉宝座，盟主便在此坐堂议事。台上高高立着一竿旗，
上书：替天行道 四个大字。 盟主左右各侍立着两位白衣武士，两
边都放着一长排虎皮交椅，时常有武林前辈高手前来参见盟主。
LONG
    );
        set("valid_startroom", 1);
    set("exits", ([
		"up" : __DIR__"fengchan",
        "down" : __DIR__"yuhuang",
        "east" : __DIR__"xiayi-new",
        "west" : __DIR__"zhengqi-new",
    ]));
    set("objects",([
                "/d/taishan/npc/meng-zhu-new" : 1,
        __DIR__"npc/wei-shi1" : 2,
    ]));
        set("no_clean_up", 1);
    set("outdoors", "taishan");
    setup();
}

void update_here()
{
	remove_call_out("reset");
	call_out("reset", 1);
}