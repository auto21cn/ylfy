// rm.c
// creator:     Fan@falling-sun.chinesemud.net
// creat time:  1999/04/05


#include "/doc/help.h"
inherit F_CLEAN_UP;
int help(object me);
protected int clean_dir(string dir);
protected int remove_contents(string what);
protected int remove_file(string file, int flag);

protected int directory_exists(string dirname)
{
    return (file_size(dirname) == -2);
}

int main(object me, string str,int flag)
{
   mixed *files, *path, *multi;
   string dir;
   int loop;
 
   if(!str || str == "")  return help(me);
 
   seteuid(getuid(me));
 
   if(sscanf(str, "-r %s", str) == 1
   || sscanf(str, "%s -r", str) == 1)
      flag = 1;
  
   multi = explode(str, " ");

   if(multi && sizeof(multi) > 1) {

      for(loop=0; loop<sizeof(multi); loop++)
          main( me,multi[loop],flag );

      return 1; 
   }
 
 
   //  Check to see if the request is bad ("..*")

   if(str == "..*") {
      write("Rm: 无效的参数。\n");
      return 1; 
   }
 
   str = resolve_path(me->query("cwd"), str);
 
 
   path = explode(str, "/");
   
   dir = "/" + implode( path[0..sizeof(path)-2], "/" ) + "/";
   if(dir == "//")  dir = "";

   if((int)master()->valid_write(dir, previous_object(), "rm") == 0) {
      write("没有足够的权限删除 " + (dir == "" ? "根目录" : dir) + "。\n");
      return 1; 
   }
 
   //   Check for wildcards present in rm request
 
   files = get_dir(str);
 
   if(files) {
      files -= ({ "." });  files -= ({ ".." });
   }
 
   if(!files || !sizeof(files)) {
      write("Rm: 没有这样的文件 : " + str + "\n");
      return 1; 
   }
 
   if(dir == "")  dir = "/";
 
   if(sizeof(files) == 1) 
        return remove_file(dir + files[0], flag);
 
 
   for(loop=0; loop<sizeof(files); loop++) 
        remove_file(dir + files[loop], flag);
   return 1; 
}
 
protected int remove_file(string file, int flag) 
{
   int try;
 
   if((int)master()->valid_write(file, previous_object(), "rm") == 0) {
      write("Rm: " + file + " : 权限不允许。\n");
      return 1; 
   }
 
   if(directory_exists(file)) {

        if(!flag) {
        write("Rm: " + file + " 是一个目录。\n");
        return 1; 
        }

        
        try = clean_dir(file);
        if(!try || !rmdir(file))
               write("删除目录：" + file + "/ 失败！\n");
        else   write("目录："+file + "/ 已经移去。\n");
            return 1; 
   }
   if ( rm(file) )
      write("文件："+file + " 已经移去。\n");
   else
      write("删除文件：" + file + " 失败！\n");
   return 1; 
}

protected int clean_dir(string dir) 
{
//string tmp;
 
    if (!dir || dir == "")
        return 0;
 
    if (file_size(dir) != -2)
        return 0;          //  没有这个目录
 
     return remove_contents(dir + "/");
}
 
protected int remove_contents(string what)
{
    mixed *dir, *subdir;
    string path, subpath,tmp;
    int loop, subloop, cnt = 0;
 
    dir = get_dir(what);
    if (!dir || !(loop = sizeof(dir)))
        return -1;
 
    do {
        reset_eval_cost();
        while (loop--) {
            path = what + dir[loop];
 
            if (file_size(path) == -2) {
                subdir = get_dir(path + "/");
                if (subdir && (subloop = sizeof(subdir))) {
                    while (subloop--) {
                        subpath = path + "/" + subdir[subloop];
                         if (file_size( subpath ) == -2) {
                            while (file_size((tmp = what + subdir[subloop] + cnt)) != -1)
                                cnt++;
                            rename(subpath, tmp);
                         }else rm(subpath);
                    }
                }
                rmdir(path);
            }
 
               else  rm(path);
        }
 
        dir = get_dir(what);
    } while (dir && (loop = sizeof(dir)));
    return 1;
}


int help(object me)
{
  write(@HELP
指令格式 : rm [-r] <档名> [档名] [档名] ....
此指令可让你(你)删除有权修改的档案。
HELP
    );
    return 1;
}
