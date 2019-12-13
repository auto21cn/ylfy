#include <ansi.h>
inherit ITEM;
nosave string *b_names = ({
  "��",
  "��",
  "��",
  "��",
  "��",
  "��",
  "��",
  "���", 
  "���", 
  "����", 
  "ˮ��", 
  "��ɳ", 
  "è��", 
  "��ʯ", 
  "��֮���",
  "��֮���",
  "��֮����",
  "��֮ˮ��",
  "��֮��ɳ",
  "��֮è��",
  "��֮��ʯ",
  "����",
  "���",
  "ɭ��",
  "����",
  "����",
  "��ϼ",
  "ɳĮ",
  "��֮��",
  "��֮��",
  "��֮��",
  "��֮��",
  "��֮��",
  "��֮��",
  "��֮��",
});

nosave mapping names = ([
  "��":       "hong",
  "��":       "blue",
  "��":       "green",
  "��":       "qing",
  "��":       "huang",
  "��":       "zi",
  "��":       "cheng",
  "���":     "manao",
  "���":     "feicui",
  "����":     "chengyu",
  "ˮ��":     "shuijing",
  "��ɳ":     "jinsha",
  "è��":     "maoyan",
  "��ʯ":     "zuanshi",
  "��֮���":  "god manao",
  "��֮���":  "god feicui",
  "��֮����":  "god chengyu",
  "��֮ˮ��":  "god shuijing",
  "��֮��ɳ":  "god jinsha",
  "��֮è��":  "god maoyan",
  "��֮��ʯ":  "god zuanshi",
  "����":      "sun",
  "���":      "sky",
  "ɭ��":      "forest",
  "����":      "sea",
  "����":      "fire",
  "��ϼ":      "sunshine",
  "ɳĮ":      "sand",
  "��֮��":    "justice light",
  "��֮��":    "mercy light",
  "��֮��":    "earth light",
  "��֮��":    "sea light",
  "��֮��":    "fire light",
  "��֮��":    "gods light",
  "��֮��":    "love light",
]);

void setname()
{
    int i, j,k;

    string name,*id;
    k=random(1000);
    //   i=(random(sizeof(names4)/2))*2;
    if(k>995){
	i=21+random(7);
	j=i-21;
	set("is_monitored", 1);
    }else if(k>960){
	i=14+random(7);
	j=i-14;
	set("is_monitored", 1);
    }else if (k>800)
    { i=7+random(7);
	j=i-7;
	set("is_monitored", 1);
    }else
    { i=random(7);
	j=i;}
    set("b_lvl",i+1);


    name=b_names[i]+"��ʯ";
    set("baoshi",b_names[i]);
    id=({names[b_names[i]]+" baoshi","baoshi"});
    set("reward_lvl",j+1);
    if(j==0){
	set_name(HIR+name+NOR,id); }
    if(j==1){
	set_name(HIB+name+NOR,id); }
    if(j==2){
	set_name(HIG+name+NOR,id); }
    if(j==3){
	set_name(HIC+name+NOR,id); }
    if(j==4){
	set_name(HIY+name+NOR,id); }
    if(j==5){
	set_name(HIM+name+NOR,id); }
    if(j==6){
	set_name(YEL+name+NOR,id); }
}
void changename(int i)
{
    int j;
    string name,*id;
    object ob=this_object();
    if(i<0)
	i=random(7);
    if(i>34)
	i=28+random(7);
    if(i>=28){

	j=i-28;
	ob->set("is_monitored", 1);
    }else if(i>=21){

	j=i-21;
	ob->set("is_monitored", 1);
    }else if(i>=14){

	j=i-14;
	ob->set("is_monitored", 1);
    }else if (i>=7)
    {
	j=i-7;
	ob->set("is_monitored", 1);
    }else
    {
	j=i;}
    ob->set("b_lvl",i+1);


    name=b_names[i]+"��ʯ";

    id=({names[b_names[i]]+" baoshi","baoshi"});

    ob->set("baoshi",b_names[i]);

    ob->set("reward_lvl",j+1);

    if(j==0){
	ob->set_name(HIR+name+NOR,id); }
    if(j==1){
	ob->set_name(HIB+name+NOR,id); }
    if(j==2){
	ob->set_name(HIG+name+NOR,id); }
    if(j==3){
	ob->set_name(HIC+name+NOR,id); }
    if(j==4){
	ob->set_name(HIY+name+NOR,id); }
    if(j==5){
	ob->set_name(HIM+name+NOR,id); }
    if(j==6){
	ob->set_name(YEL+name+NOR,id); }
}

void init()
{

    add_action("do_enchase", "enchase");
    add_action("do_enchase", "inset");
}


int do_enchase(string arg)
{
    object in_obj;
    string item,mats;

    int inset_num ,i,j,k;
    object me = this_player();
    object ob = this_object();

    if(environment(ob) != me)
	return 0;
    if(!arg) return notify_fail("��Ҫ�ѱ�ʯ��Ƕ��ʲô�ϣ�\n");
    if(sscanf(arg, "%s", item)!=1) return notify_fail("��Ҫ�ѱ�ʯ��Ƕ��ʲô�ϣ�\n");
    if(!objectp(in_obj = present(item, me))) return notify_fail("������û������������\n");

    if( in_obj->query("equipped") )
	return notify_fail("��������������Ʒ��װ��������Ƕ��ʯ��\n");
    //added by wuyou,lest one player inset baoshi in another player
    if( in_obj->is_character() )
	return notify_fail("���ѵ����ˣ���ô�ܰѱ�ʯ��Ƕ�������ϣ�\n");
    if( in_obj->query("no_zm")||in_obj->query_unique())
        return notify_fail("���װ��������Ƕ��ʯ��\n");
    if(in_obj->query_amount())
	return notify_fail("�������������Ƕ��ʯ��\n");
    i=ob->query("b_lvl");
    if(i>28) k=7;
    else if(i>21) k=5;
    else if(i > 14) k=3;
    else if(i > 7) k=2;
    else k=1;
    j=ob->query("reward_lvl");
    mats = in_obj->query("material");       //װ��������
    inset_num = in_obj->query("inset_num");  // Ƕ�˼�����
    if(!inset_num) inset_num = 1;
    else inset_num = inset_num + 1;
    if(inset_num > 6) return notify_fail(in_obj->query("name")+"���Ѿ���Ƕ��̫��ı�ʯ��!\n");

    if(in_obj->query("armor_prop/armor"))   //����
    {

	message_vision(CYN"$N��$n"+CYN"��Ƕ��"+in_obj->query("name")+CYN"�� \n"NOR,me,ob);
	tell_room(environment(me),HIB"ֻ��"+ob->name()+HIB"����һ��"+ob->query("baoshi")+"��,������"+in_obj->query("name")+HIB"����,������! \n"NOR);
	//�ж�ͬ�౦ʯ
	if(j==1){
	    in_obj->add("armor_prop/dodge",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø�����ӯ�ˣ�\n"NOR,me);
	}
	if(j==2){
	    in_obj->add("armor_prop/force",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��ӳ����ˣ�\n"NOR,me);
	}
	if(j==3){
	    in_obj->add("armor_prop/constitution",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);
	}
	if(j==4){
	    in_obj->add("armor_prop/parry",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø�������ˣ�\n"NOR,me);
	}
	if(j==5){

	    in_obj->add("armor_prop/unarmed",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��ӳ��������ˣ�\n"NOR,me);
	}
	if(j==6){
	    in_obj->add("armor_prop/intelligence",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��ӳ��������ˣ�\n"NOR,me);
	}
	if(j==7){
	    in_obj->add("armor_prop/strength",k*2+random(k*5));

	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��ӳ��������ˣ�\n"NOR,me);
	}
	
	//  me->add("bellicosity",1000);
	in_obj->set_weight(in_obj->query_weight()+1000);

	in_obj->set("inset_num",inset_num);
	in_obj->set("no_sell",1);
	in_obj->add("inset_b",inset_num);  //װ��b
	in_obj->set("name",HIG+in_obj->query("name")+NOR);
	if(!in_obj->query("old_long"))
	    in_obj->set("old_long",in_obj->query("long"));

	if(!in_obj->query("old_ee"))
	    in_obj->set("old_ee",ob->query("name"));
	else in_obj->set("old_ee",in_obj->query("old_ee")+" "+ob->query("name"));

	in_obj->set("long",in_obj->query("old_long")+"����Ƕ����"+HIW+chinese_number(inset_num)+"�ű�ʯ:"+in_obj->query("old_ee")+"��\n"NOR);

	in_obj->set("xyzx_save_item", 1);
	// �󶨵ı�ʯ��Ƕװ������ôװ��Ҳ�ᱻ��
	if ( mapp(ob->query("bind_master_level")) ) {
	    in_obj->set("bind_master_level/"+me->query("id"), 1);
	}
	in_obj->set("owner_id", 1);
	in_obj->save();
	destruct(ob);
	return 1;
    } 
    else if(in_obj->query("weapon_prop/damage"))
    {
	//����
	message_vision(CYN"$N��$n"+CYN"��Ƕ��"+in_obj->query("name")+CYN"�� \n"NOR,me,ob);
	tell_room(environment(me),HIB"ֻ��"+ob->name()+HIB"����һ��"+ob->query("baoshi")+"��,������"+in_obj->query("name")+HIB"����,������! \n"NOR);

	message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø������������ˣ�\n"NOR,me);
	if(k>2) {
	    in_obj->set("material","diamond");
	    message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);}
	in_obj->add("weapon_prop/damage",k*2+random(k*5));
	in_obj->add("weapon_prop/intelligence",k*2+random(k*5));
	in_obj->set_weight(in_obj->query_weight()+1000);
	in_obj->set("no_sell",1);
	in_obj->set("inset_num",inset_num);
	in_obj->add("inset_b",inset_num);  //װ��g
	in_obj->set("name",HIG+in_obj->query("name")+NOR);
	if(!in_obj->query("old_long"))
	    in_obj->set("old_long",in_obj->query("long"));

	if(!in_obj->query("old_ee"))
	    in_obj->set("old_ee",ob->query("name"));
	else in_obj->set("old_ee",in_obj->query("old_ee")+" "+ob->query("name"));

	in_obj->set("long",in_obj->query("old_long")+"����Ƕ����"+HIW+chinese_number(inset_num)+"�ű�ʯ:"+in_obj->query("old_ee")+"��\n"NOR);
	in_obj->set("xyzx_save_item", 1);
	// �󶨵ı�ʯ��Ƕװ������ôװ��Ҳ�ᱻ��
	if ( mapp(ob->query("bind_master_level")) ) {
	    in_obj->set("bind_master_level/"+me->query("id"), 1);
	}
	in_obj->set("owner_id", 1);
	in_obj->save();
	destruct(ob);
	return 1;
    }
    return notify_fail("����Ƕ��ʯʧ���ˣ�\n");
}