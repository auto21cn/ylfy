// clean_up.c
// by Annihilator@ES2

int clean_up()
{
    object *inv;
    int i;

    if ( !clonep() && this_object()->query("no_clean_up") ) return 1; // 非复制的，且有参数 no_clean_up
    if ( interactive(this_object()) ) return 1; // 可互动的
    // If we are contained in something, let environment do the clean
    // up instead of making recursive call. This will prevent clean-up
    // time lag.
    if ( environment() ) return 1; // 有环境的
    inv = all_inventory();
    for ( i = sizeof(inv) - 1; i >= 0; i-- )
	{
        if ( interactive(inv[i]) ) return 1; // 内包含有可互动的
	}
    destruct(this_object());
    return 0;
}
