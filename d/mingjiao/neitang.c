// Room: neitang.c

inherit ROOM;

void create()
{
        set("short", "内堂");
        set("long", @LONG
经过小路，到了一间大堂。这是一个极大的建筑，而且十
分宽敞，就算有三十队舞龙狮在这儿，也还有余裕。这地方共
有七十二道柱梁，每梁上雕有麒麟、龙、凤、犀等七十二种不
同的动物，栩栩如生。而屋顶成拱形，雕有七彩唐僧取经图，
更是生动，天花板中央，只雕了个遒劲万钧的“明”字，地板
上也刻着齐天大圣大闹天宫图，而正中厅堂，雕的是太上老君
将孙悟空放在丹炉里熬炼的雕画。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"diecong1",
  "north" : __DIR__"shanlu4",
]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

