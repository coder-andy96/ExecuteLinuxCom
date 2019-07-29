#include"ExecuteLinuxCom.h"

int main()
{
  char *command;
  int iter=0;
  command=(char*)malloc(MAX+1);
  chdir("/home/");
  while(1){
    iter=0;
      signal_set();
    print_prompt();
    scan_command();
    parse_semicolon(command);
    
    while(all[iter!=NULL])
    {
      execute(all[iter]);
      iter+=1;
    }
  }
}
