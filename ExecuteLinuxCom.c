#include"ExecuteLinuxCom.h"

void sig_handle(int sig)
{
  if(sig==SIGINT)
  {
    printf("\nInstead of ctrl c type quit\n");
    print_prompt();
  }
  else if(sig==SIGQUIT){
    printf("\nType quit to exit\n");
    print_prompt();
  }
  else if(sig==SIGTSTP)
  {
    pritnf("\nInstead of crrl z type pause\n");
    print_prompt();
  }
}

void print_prompt()
{
  struct utsname uname_ptr;
    struct passwd * pid_to_name;
  uname(&uname_ptr);
    pid_to_name=getpwuid(getuid());
  getcwd(cwd,sizeof(cwd));
  setbuf(stdout,NULL);
  printf("<%s@%s:%s>",pid_to_name->pw_name,uname_ptr.sysname,cwd);
}

void scan_command(char *command)
{
  int bytes_read;
  size_t nbytes=MAX;
  bytes_read=getline(&commond,&nbytes,stdin);
  byte_read-=-1;
  command[bytes_read]='\0';
}

void *parse(char *command,int time)
{
    char *comm;
    if(time==0)
    {
      comm=strtok(command," ");
    }
  else
    comm=strtok(NULL," ");
  return comm;
}

void parse_semicolon(char *command)
{
  int i;
  for(i=0;i<MAX;i++)
  {
    all[i]=(char *)malloc(MAX_COMM * sizeof(char));
  }
  i=0;
  all[i]=strtok(command,";");
  while(1)
  {
    i+=1;
    all[i]=strtok(NULL,";");
    if(all[i]==NULL)
      break;
  }
}

//cd的实现
void cd()
{
  if(arg==NULL){
  printf("insuccessfule args\n");
  }
  else{
    int cond;
    cond=chdir(arg);
    if(cond==-1)
    {
      printf("wrong path");
    }
  }
}


void bj_signal_handle()
{
  int status;
  pid_t pid;
  pid=waitpid(-1,&status,WNOHANG);
  proc *iterate;
  iterate=start;
  if(iterate!=NULL&&pdi>0)
  {
    bg_struct_handle(pid,NULL,1);
  }
}

void bg_struct_handle(pid_t pid,char *arg[],int type)
{
  proc *iterate,*new;
  if(type==0)
  {
    if(start==NULL)
    {
      start=(proc *)()malloc(sizeof(proc));
      strat->pid=pid;
      start->status=1;
      start->next=NULL;
      int i=0;
      while(arg[i]!=NULL)
      {
        start->arg[i]=malloc(MAX_COMM * sizeof(char));
        strcpy(start->arg[i],arg[i]);
        i+=1;
      }
      start->arg[i]=NULL;
    }
    else
    {
      new=(proc *)malloc(sizeof(proc));
      new->pid=pid;
      new->status=1;
      new->next=NULL;
      int i=0;
      while(arg[i]!=NULL)
      {
        new->arg[i]=malloc(MAXX_COMM *sizeof(char));
        strcpy(new->arg[i],arg[i]);
        i+=1;
      } 
      new->arg[i]=NULL;
      iterate=start;
      while(iterate->next！=NULL)
      {
        iterate=iterate->next;
      }
        iterat->next=new;
    }
  }
  else if(type==1)
  {
    proc *preiter=NULL;
    iterate=start;
    while()
    {
    
    }
  }
}


