
// 每次执行指令数
#define XYZX_XIULIAN_CISHU 5
// 每次触发最多执行的指令数
#define MAX_CHUFA_CMDS 5

string xiulian_cmds_jiexi(string str);

int do_xyzx_xiulian()
{
	string file, *file_list, hy;
	int i, m, year, mon, day;

	// 每次执行程式都初试化为0，以便记录
	m = 0;

	if ( !this_object()->query("lixian/biguan") || interactive(this_object()) )
		return 0;
	
	// 非注册会员潜能不够，程式终止
	if ( stringp(hy = this_object()->query("xy_huiyuan")) )
	{
		if ( !sscanf(hy, "%d年%d月%d日", year, mon, day) )
		{
			if ( !this_object()->query("potential") || this_object()->query("potential") < 1 )
				return 0;
		}
	}
	else
	{
		// 非会员潜能不够，程式终止
		if ( !this_object()->query("potential") || this_object()->query("potential") < 1 )
			return 0;
	}

	// 检查指令集文件是否存在
	if ( file_size(DATA_DIR + "biguan/" + this_object()->query("id") + __SAVE_EXTENSION__) == -1 )
		return 0;
	
	// 读取文件内容
	file = read_file(DATA_DIR + "biguan/" + this_object()->query("id") + __SAVE_EXTENSION__);
	// 解析文件内容为指令集
	file_list = explode(file,"\n");

	if ( this_object()->query_temp("do_xiulian_num") )
	{
		if ( i >= sizeof(file_list) )
			i = 0;
		else
			i = this_object()->query_temp("do_xiulian_num");
	}
	else
		i = 0;

	for (i = 0; i < sizeof(file_list); i++)
	{
		// 有 Busy 结束指令执行
		if ( this_object()->is_busy() )
			break;

		// 身体状况太差结束指令执行
		if ( this_object()->query("jing") * 100 / this_object()->query("max_jing") < 5 || this_object()->query("qi") * 100 / this_object()->query("max_qi") < 5 )
			break;

		// 睡梦、昏迷中中断指令执行
		if ( this_object()->query_temp("block_msg") )
			break;

		// 执行 XYZX_XIULIAN_CISHU 次时终止该次运作
		if ( m >= XYZX_XIULIAN_CISHU )
			break;

		// 非注册会员潜能不足中断指令执行
		if ( stringp(hy) )
		{
			if ( !sscanf(hy, "%d年%d月%d日", year, mon, day) )
			{
				if ( !this_object()->query("potential") || this_object()->query("potential") < 1 )
					break;
			}
		}
		else
		{
			// 非会员潜能不足中断指令执行
			if ( !this_object()->query("potential") || this_object()->query("potential") < 1 )
				break;
		}

		this_object()->command(this_object()->xiulian_cmds_jiexi(file_list[i]));
		// 记录指令集执行的位置
		this_object()->add_temp("do_xiulian_num", 1);
		m++;
		
		// 非会员需要消耗潜能
		if ( stringp(hy) )
		{
			if ( !sscanf(hy, "%d年%d月%d日", year, mon, day) )
				this_object()->add("potential",-1);
		}
		else
			this_object()->add("potential",-1);

		if ( this_object()->query_temp("do_xiulian_num") == sizeof(file_list) )
		{
			this_object()->delete_temp("do_xiulian_num");
			break;
		}
	}

	return 1;
}

// 离线触发练功
int do_xyzx_chufa(string cmds)
{
	string *cmd, cmd_buffer, *cmded;
	int i, v;

	if ( !stringp(cmds) ) 
	{ // 只能是字符串
		this_object()->delete_temp("chufa_buffer");
		return 0;
	}
	if ( !sscanf(cmds, "%*s-%*s") )
	{ // 只有一条命令
		this_object()->command(this_object()->xiulian_cmds_jiexi(cmds));
		this_object()->delete_temp("chufa_buffer");
		return 1;
	}

	cmd = explode(cmds, "-");
	v = sizeof(cmd);
	cmded = ({ });

	for ( i=0; i<v; i++ )
	{
		if ( i >= MAX_CHUFA_CMDS ) break; // 每次最多只执行 MAX_CHUFA_CMDS 条指令
		if ( this_object()->is_busy() ) break; // 有 Busy 结束指令执行
		if ( this_object()->query("jing") * 100 / this_object()->query("max_jing") < 5 
			|| this_object()->query("qi") * 100 / this_object()->query("max_qi") < 5 )
			break; // 身体状况太差结束指令执行
		if ( this_object()->query_temp("block_msg") ) break; // 睡梦、昏迷中中断指令执行
		this_object()->command(this_object()->xiulian_cmds_jiexi(cmd[i])); // 执行指令
		cmded += ({ cmd[i] });
	}
	
	cmd -= cmded;

	if ( !arrayp(cmd) || !sizeof(cmd) ) // 所有指令成功执行完毕
		this_object()->delete_temp("chufa_buffer");
	else
	{ // 有未执行完的指令放入缓存区
		cmd_buffer = implode(cmd, "-");
		this_object()->set_temp("chufa_buffer", cmd_buffer);
	}

	return 1;
}

// 指令解析
string xiulian_cmds_jiexi(string str)
{
	mapping alias = this_object()->query_all_alias();
	string cmd, argstr, *args;
	int i, j;

	if( mapp(alias) ) 
	{
        if( !undefinedp(alias[str]) )
            return replace_string( alias[str], "$*", "" );
        
		if( sscanf(str, "%s %s", cmd, argstr)==2 && !undefinedp(alias[cmd]) ) 
		{
			if ( sscanf(alias[cmd], "%*s$%*s") )
			{
				cmd = replace_string( alias[cmd], "$*", argstr );
				if ( sscanf(argstr, "%*s %*s") )
				{
					args = explode(argstr, " ");
					if( (j = sizeof(args)) )
					{
						for(i=0; i<j; i++)
						{
							cmd = replace_string( cmd, "$" + (i+1), args[i] );
						}
					}
				}
			}
			else
				cmd = alias[cmd] + " " + argstr;
			return cmd;
        }
    }

	cmd = (string)ALIAS_D->process_global_alias(str);
	if ( this_object()->query_temp("big5") ) cmd = LANGUAGE_D->Big52GB(cmd);
	return cmd;
}