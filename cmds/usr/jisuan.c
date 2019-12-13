void show_help();
int main(object me,string arg)
{
    int num;
    float val;
    if(!arg)
    {
        show_help();
        return 1;
    }
    if(sscanf(arg,"exp %d",num)==1 && num>0)
    {
        val = num/79.37;
        val=val*val*val;
        val=pow(val,0.5);
        printf("%d级技能所需经验级数为：%d\n",num,to_int(val));
    }
    else if(sscanf(arg,"skill %d",num)==1 && num>0)
    {
        val = pow(num*num,0.333333)*79.37;
        printf("%d级经验所能学的技能级数为：%d\n",num,to_int(val));
    }
    else
    {
        show_help();
        return 1;
    }
    return 1;
}

void show_help()
{
    write("使用方法：\n");
    write("计算技能所需的经验等级：jisuan exp <技能级数>\n");
    write("计算经验等级能学的技能：jisuan skill <经验级数>\n");
}
