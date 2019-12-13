// news_cloth.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

string do_wear();

void create()
{
        set_name(HIG "���¶���ѥ" NOR, ({"new boots"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", "����һ���¶���ѥ����suimeng�ر�Ϊ���˶����ġ�\n");
                set("material", "boots");    //����
                set("armor_prop/armor", 500);  //����
                set("armor_prop/warm", 3);   //��ů
                set("value", 1000);   //��ֵ
				set("no_sell",1);
                set("wear_msg", (: do_wear :));  //װ����Ϣ
       //---------------------------------------------------------------
              //��װ����
                set("suit",HIG"�¶���װ"NOR);  //��װ����
                set("suit_lvl",1);             //��װ�ȼ�
                set("suit_count",3);           //��װ��������
              //��װ������
                set("suit_mod/cloth","�¶�����");
                set("suit_mod/boots","�¶���ѥ");
                set("suit_mod/pants","�¶�����");
             
              //��װȫ�������츳Ч��  
                set("suit_eff/strength",5000);      //����
                set("suit_eff/constitution",5000);      // ��� 
                set("suit_eff/intelligence",5000);      //����  
				set("suit_eff/dexerity",5000); 
                set("suit_eff/armor",5000);      //    һ��
                //set("suit_eff/composure",1);      //����
                //set("suit_eff/personality",1);      // ��� 
                //set("suit_eff/constitution",1);      //����  
                //set("suit_eff/karma",1);      //    һ��
                //��װȫ�����Ӽ���Ч��     
               set("suit_eff_skill/literate",1000);                 			   
               set("suit_eff_skill/unarmed",1000);
			   set("suit_eff_skill/parry",1000);
			   set("suit_eff_skill/dodge",1000);
       //---------------------------------------------------------------
        }
        setup();
}

string do_wear()
{
        object me;
        string msg;
        int per;

        me = this_player();
        per = me->query("per");
        if (me->query("gender") == "Ů��")
        {
                if (per >= 30)
                        msg = HIC "$N" HIC "���Ὣһ��$n" HIC "���ڽ��ϣ���̬����֮����\n";
                else if (per >= 25)
                        msg = HIG "$N" HIG "��$n" HIG "չ�������ڽ��ϡ�\n";
                else if (per >= 20)
                        msg = YEL "$N" YEL "��$n" YEL "���ڽ��ϣ����������ӡ�\n";
                else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "���ڽ��ϡ�\n";
        } else
        {
                if (per >= 30)
                        msg = HIC "$N" HIC "����һ�ӣ���$n" HIC "���ڽ��ϣ���������֮����\n";
                else if (per >= 25)
                        msg = HIG "$N" HIG "��$n" HIG "չ�������ڽ��ϡ�\n";
                else if (per >= 20)
                        msg = YEL "$N" YEL "��$n" YEL "���ڽ��ϣ����˳��½ǣ����������ӡ�\n";
                else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "���ڽ��ϣ����������\n";
        }
        return msg;
}

int query_autoload()
{
        return 1;
}