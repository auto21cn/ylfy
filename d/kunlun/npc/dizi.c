// �����ɵĵ���
inherit NPC;
#define SET_SKILL   50         // ��������书��ֵ���Զ����ɾ���
#define SPE_SKILL   40          // ���������书��ֵ

string *first_name = ({ "֣","��","��","��","��","����","Ǯ","��","��","��","��",
        "��","��" });
string *name_words = ({ "־","��","��","־","��","��","��","��","��","Ԫ","��","��",
        "Т","��","��","��","��","��","��","��","ʤ","��","��","��","��","ΰ" });
string *rnd_id = ({"ra","ma","ta","pu","gu","du","so","po","lo","phi","tri","ne","she"});
string *rnd_id_tail = ({"ng","gh","ss","h","le","d","ck","m","tte"});

string *name_wordss = ({ "Ӣ","��","��","��","ӯ","С","��","��","�","С","��","��",
        "��","��","��","�","��","��","��","��","��","��","�","��","��","��" });

void create()
{
        string name, id;
        name = first_name[random(sizeof(first_name))];

        if (random(3)>1){
            set("gender", "����");
            name += name_words[random(sizeof(name_words))];
            if( random(10) > 2 ) name += name_words[random(sizeof(name_words))];
        }else{
            set("gender", "Ů��");
            name += name_wordss[random(sizeof(name_wordss))];
            if( random(10) > 2 ) name += name_wordss[random(sizeof(name_wordss))];
        }
        id = rnd_id[random(sizeof(rnd_id))];
        if( random(10) > 4 ) id += rnd_id[random(sizeof(rnd_id))];
        id += rnd_id_tail[random(sizeof(rnd_id_tail))];
        set_name(name, ({ id+" dizi", "dizi" }) );
        set("age", random(10)+14);
        set("long", name+"�հ�ʦѧ�ղ��ã�����������\n");        
        set("attitude", "peaceful");
        set("str", 25);

        set("int", random(20)+2);
        set("con", random(20)+2);
        set("str", random(20)+2);
        set("dex", random(20)+2);

        set("jingli",1000);
        set("max_jingli",200);
        set("neili", 900);
        set("max_neili", 500);
        set("jiali",300);
        set("combat_exp",SET_SKILL*SET_SKILL*SET_SKILL/10);
 
        set_skill("force",   SET_SKILL);
        set_skill("sword",   SET_SKILL);
        set_skill("unarmed", SET_SKILL);
        set_skill("parry",   SET_SKILL);
        set_skill("dodge",   SET_SKILL);
        set_skill("literate",SET_SKILL);

        set_skill("xuantian-wuji",SPE_SKILL);
        set_skill("liangyi-jian", SPE_SKILL);
        set_skill("yaoming-dodge", SPE_SKILL);
        set_skill("kunlun-zhang",SPE_SKILL);
           
           map_skill("dodge", "yaoming-dodge");
           map_skill("force", "xuantian-wuji");
           map_skill("parry", "liangyi-jian");
           map_skill("sword", "liangyi-jian");
           map_skill("unarmed","kunlun-zhang");   
 

    create_family("������", 16, "����");
    setup();
    carry_object("//clone/cloth/long_cloth")->wear();
    carry_object("/clone/weapon/changjian")->wield();
}

