// module: report
// function: report bugs,suggest
// author: ken@XAJH
// time: 98-7-23

#define BOARD "/clone/board/towiz_b"

inherit F_CLEAN_UP;


int help(object me);
void auto_report(string author,string title,string text,string body);

private mapping TYPE = ([
        "bug"           : "错误：",
        "suggest"       : "建议：",
        "reply"         : "答复：",
]);

void create() { seteuid(getuid()); }

int main(object me,string arg) {

        string type,report_title,body;
        mixed title;
        int number;
        mapping *notes;

        if( !arg ) {
                help(me);
                return 1;
        }

        if( sscanf(arg, "%s %s", type, title) != 2) {
                help(me);
                return 1;
        }

        if( undefinedp(TYPE[type]) ) {
                help(me);
                return 1;
        }

        body = "";

        if( type == "reply" ) {
                if( !wizardp(me) )
                        return notify_fail("只有巫师才能作出回答。\n");

                if( !sscanf(title, "%d", number ) )
                        return notify_fail("你要答复哪张留言？\n");

                notes = BOARD->query("notes");
                if( number < 1 || number > sizeof(notes) )
                        return notify_fail("没有这张留言。\n");
                number--;
                report_title = sprintf("%s [%s]", TYPE[type],notes[number]["title"] );
                body += sprintf("\n%s在( %s )提到：\n"
                                "----------------------------------------------------------\n%s",
                                notes[number]["author"],
                                ctime(notes[number]["time"]),
                                notes[number]["msg"]);
        } else report_title = TYPE[type] + title;

        me->edit((: auto_report,
                        sprintf("%s(%s)",
                                me->query("name"),
                                me->query("id")
                        ), // author of report
                        report_title,
                        body
                :));
        return 1;
}


int help(object me) {
        write(@HELP
指令格式： report bug|suggest 标题。

这个指令让你报告 Bug 或 发送你的建议给巫师公会，如果你是巫师请
用 report reply 留言号 给予答复。

HELP);
return 1;
}

void auto_report(string author,string title,string text,string body) {

        mapping note;
        object report;

        if( sizeof(body) < 2 ) return;

        if( objectp(report=load_object(BOARD)) )
        {
                note=([]);
                note["title"] = title;;
                note["author"] = author;
                note["time"] = time();
                report->done_post(this_player(),note,body+text);
        }
        return;
}

