//
// cangjingge.c 雪山藏经室
// by secret
inherit ROOM;
string* books = ({
    "/d/xueshan/obj/skin",
    "/d/xueshan/obj/jing",
    "/clone/book/book-bamboo",
    "/clone/book/book-silk",
    "/clone/book/book-stone",
    "/clone/book/book-iron",
});
void create()
{
        set("short", "雪山藏经室");
    set("long", @LONG
这里是雪山寺的藏经室，靠墙是一排书架，摆满了各种拳谱、书籍。
大多是当年掌门人鸠摩智翻译的佛经和从少林寺取来的武学典籍。
LONG
    );
    set("exits", ([
                "southeast" : __DIR__"dating",
    ]));
    set("objects", ([
        books[random(sizeof(books))] : 1,
        books[random(sizeof(books))] : 1,
        books[random(sizeof(books))] : 1,
                CLASS_D("xueshan")+"/daerba" : 1,
    ]));
    setup();
    replace_program(ROOM);
}
