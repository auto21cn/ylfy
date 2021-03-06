// human.c

#define BASE_WEIGHT 40000
inherit F_DBASE;
inherit F_SKILL;
mapping *combat_action = ({
    ([  "action":       "$N挥拳攻击$n的$l",
        "damage_type":  "瘀伤",
    ]),
    ([  "action":       "$N往$n的$l一抓",
        "damage_type":  "抓伤",
    ]),
    ([  "action":       "$N往$n的$l狠狠地踢了一脚",
        "damage_type":  "瘀伤",
    ]),
    ([  "action":       "$N提起拳头往$n的$l捶去",
        "damage_type":  "瘀伤",
    ]),
    ([  "action":       "$N对准$n的$l用力挥出一拳",
        "damage_type":  "瘀伤",
    ]),
});
void create()
{
    seteuid(getuid());
    set("unit", "位");
    set("gender", "男性");
    set("can_speak", 1);
    set("attitude", "peaceful");
    set("limbs", ({
        "左肩", "右肩", "左臂", "左脚", "右脚", "右臂",
        "左手", "右手", "腰间", "小腹", "左腿", "右腿",
        "后心", "头部", "颈部", "胸口", 
    }) );
}
void setup_human(object ob)
{
    mapping my;
    int qi_age;
    my = ob->query_entire_dbase();
    ob->set("default_actions", (: call_other, __FILE__, "query_action" :));
    
    if( undefinedp(my["age"]) ) my["age"] = 14;
    if (undefinedp(my["str"])) my["str"] = 10 + random(21);
    if (undefinedp(my["con"])) my["con"] = 10 + random(21);
    if (undefinedp(my["dex"])) my["dex"] = 10 + random(21);
    if (undefinedp(my["int"])) my["int"] = 10 + random(21);
    if (undefinedp(my["per"])) my["per"] = 10 + random(21);
    if (undefinedp(my["kar"])) my["kar"] = 10 + random(21);

	//新增属性
	//-------------------------------------------------------------------------
	if ( !ob->query("xyzx_sys/level") ) ob->set("xyzx_sys/level",0);
	if ( !playerp(ob) && !ob->query("xyzx_sys/jingzhun") ) ob->set("xyzx_sys/jingzhun",10);
	if ( !playerp(ob) && !ob->query("xyzx_sys/lingxing") ) ob->set("xyzx_sys/lingxing",10);
	if ( !playerp(ob) && !ob->query("xyzx_sys/minjie") ) ob->set("xyzx_sys/minjie",10);
	if ( !playerp(ob) && !ob->query("xyzx_sys/fanying") ) ob->set("xyzx_sys/fanying",10);
	//增加对玩家属性的判定，如果大于0则等于0
	if ( playerp(ob) && ob->query("xyzx_sys/jingzhun") >0 ) ob->set("xyzx_sys/jingzhun",0);
	if ( playerp(ob) && ob->query("xyzx_sys/lingxing") >0 ) ob->set("xyzx_sys/lingxing",0);
	if ( playerp(ob) && ob->query("xyzx_sys/minjie") >0) ob->set("xyzx_sys/minjie",0);
	if ( playerp(ob) && ob->query("xyzx_sys/fanying")>0 ) ob->set("xyzx_sys/fanying",0);
	if ( playerp(ob) && ob->query("xyzx_sys/shuxingdian")>0 ) ob->set("xyzx_sys/shuxingdian",0);
	if ( !ob->query("wuxing/mofa") ) ob->set("wuxing/mofa",random(11));

	if ( !ob->query("max_fashufali") )
	{
		ob->set("fashufali",100);
		ob->set("max_fashufali",100);
	}

#ifdef XYZX_SYS_JULI
	//-------------------------------------------------------------------------
	// 横坐标
	if ( !ob->query("xysys_map_xy/x") )
		ob->set("xysys_map_xy/x",random(6) + 1);

	// 横坐标
	if ( !ob->query("xysys_map_xy/y") )
		ob->set("xysys_map_xy/y",random(6) + 1);
	//--------------------------------------------------------------------------
#endif

    if( userp(ob) || undefinedp(my["max_jing"]) ) {
        if( my["age"] <= 14 ) my["max_jing"] = 100;
        else if( my["age"] <= 20 ) my["max_jing"] = 100 + (my["age"] - 14) * 20;
        else if( my["age"] <= 30||(int)ob->query_skill("taoism", 1)> 59) my["max_jing"] = 220;
        else if( my["age"] <= 60 ) my["max_jing"] = 220 - (my["age"] - 30) * 5;
        else my["max_jing"] = 70;
        if( my["max_jingli"] > 0 ) my["max_jing"] += my["max_jingli"] / 4;
    }
    if( userp(ob) || undefinedp(my["max_qi"]) ) {
        
        if( my["age"] <= 14 ) my["max_qi"] = 100;
        else if( my["age"] <= 20 ) my["max_qi"] = 100 + (my["age"] - 14) * my["con"];
        else my["max_qi"] = my["con"] * 6 + 100;
        
        // 道家练气：３０岁前补气，３０岁后长气
                if((qi_age=(int)ob->query_skill("taoism", 1)) > 39)
        {
            qi_age = qi_age/2;
            if (my["age"] <= 30) qi_age -= my["age"];
            else qi_age -= 30;
            // Added by Hop
            //qi_age += my["max_jingli"] / 50;
            // End of appendence            
if (qi_age > 0) my["max_qi"] += qi_age *((int)ob->query_skill("taiji-shengong", 1)/20) ; 	
        }
        
        if( my["max_neili"] > 0 ) my["max_qi"] += my["max_neili"] / 4;
    }
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (ob->query_str()-ob->query("jiali") - 10)* 2000);
    if (!userp(ob)){
        my["eff_qi"]=my["max_qi"];
        my["qi"]=my["max_qi"];
        my["eff_jing"]=my["max_jing"];
        my["jing"]=my["max_jing"];
        if (undefinedp(my["neili"]))    my["neili"]=my["max_neili"];
    }
       if (ob->query("mud_age")<100){
          if  (!ob->query("water")) ob->set("water",ob->max_water_capacity());
          if  (!ob->query("food"))  ob->set("food",ob->max_food_capacity());
    }
}
mapping query_action()
{
    return combat_action[random(sizeof(combat_action))];
}
