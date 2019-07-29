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
    while(iterate！=NULL&&iterate->pid!=pid)
    {
      preiter=iterate;
      iterate=iterate->next;
    }
    if(iterate==NULL)
    {
      printf("No such pid\n");
      return;
    }
    else if(iterate->pid==pid)
    {
      if(preiter==NULL)
      {
        start=iterate->next;
        free(iterate);
      }
      else
      {
        preiter->next=iterate->next;
        free(iterate);
      }
    }
  }
  else if(type==2)
  {
    int i=1,a=0;
    iterate=start;
    if(iterate==NULL)
    {
      printf("No background jobs\n");
      return ;
    }
    while(iterate!=NULL)
    {
      a=0;
      setbuf(stdout,NULL);
      printf("[%d]",i);
      while(iterate->arg[a]!=NULL)
      {
        printf("%s",iterate->arg[a]);
        a+=1;
      }
      printf("[%d]\n",iterate->pid);
      i+=1;
      iterate=iterate->next;
    }
  }
  return;
}

void bf_exec(char *arg[],int type)
{
  pid_t pid;
  if(type==0)
  {
    if((pid=fork())<0)
    {
      printf("***Error:forking child process failed\n");
      return ;
    }
    else if(pid==0)
    {
      signal(SIGTSTP,SIG_IGN);
      signal(SIGINT,SIG_DFL);
      signal(SIGQUIT,SIG_IGN);
      execvp(arg[0],arg);
    }
    else
    {
      signal(SIGCHLD,bg_signal_handle);
      signal(SIGINT,sig_handle);
      signal(SIGQUIT,sig_handle);
      signal(SIGTSTP,sig_handle);
      pid_t c;
      c=wait(&pid);
      dup2(current_out,1);
      dup2(current_in,0);
      return;
    }
  }
  else
  {
    if((pid=fork())<0)
    {
      printf("***ERROR:forking child process failed\n");
      return;
    }
    else if(pid==0)
    {
      signal(SIGINT, SIG_IGN); 
			signal(SIGQUIT, SIG_IGN); 
			signal(SIGTSTP,SIG_IGN);
            execvp(arg[0], arg);
    }
    else     // 父进程
        {
			signal(SIGCHLD, bg_signal_handle);
			signal(SIGINT, sig_handle); // SIGINT = 2， 用户键入Ctrl-C
			signal(SIGQUIT, sig_handle); /* SIGQUIT = 3 用户键入Ctr+\ */
			signal(SIGTSTP, sig_handle);  // SIGTSTP =20，一般有Ctrl-Z产生
            bg_struct_handle(pid, arg, 0);
            dup2(current_out, 1);
            dup2(current_in, 0);
            return ;
        }
  }
}

void file_out(char *arg[], char *out_file, int type)
{
    int f;
    current_out = dup(1);         
    if(type == 0)        //处理以覆盖的方式重定向“>”
    {
        f = open(out_file, O_WRONLY | O_CREAT, 0777); 
        dup2(f, 1); //复制文件描述符f，并指定为 1，也就是让标准输出重定向到指定的文件
        close(f);
        bf_exec(arg, 0);
    }
    else                 // 处理以追加的方式重定向“>>”
    {
        f = open(out_file, O_WRONLY | O_CREAT | O_APPEND , 0777); //以 O_APPEND 模式打开
        dup2(f, 1);
        close(f);
        bf_exec(arg, 0);
    }
}

/* 处理输入重定向文件的问题 */
void file_in(char *arg[], char *in_file, char *out_file, int type)
{
    int in;
    in = open(in_file, O_RDONLY);
    current_in = dup(0); //
    dup2(in, 0);
    close(in);
    if(type == 0)    // 单一的输入重定向
    {
        printf("Going to execute bf_exec\n");          //debug remove it
        bf_exec(arg, 0);
    }
    else if(type == 1)            // 双重重定向 `< ... >` 
    {
        file_out(arg, out_file, 0);
    }
    else                         // 双重重定向 `< ... >>`
    {
        file_out(arg, out_file, 1);
    }
    return;
}
/* 执行单条命令行语句 */
void execute(char *command)
{
    char *arg[MAX_COMM];
    char *try;
    arg[0] = parse(command, 0);        //获得命令名称的字符串指针，如“ls”
    int t = 1;
    arg[t] = NULL;   
	if (strcmp(arg[0], "exit") == 0) // 为了方便用户退出shell
	{
		puts("试图退出解析器···");
		exit(0);
	}
    if (strcmp(arg[0], "cd") == 0)     // 处理内嵌命令“cd”的情况
    {
        try = parse(command, 1);
        cd(try);
        return ;
    }
	if(strcmp(arg[0],"lsbg"))
	{
		//
	}

    // 循环检测剩下的命令参数，即检测是否：重定向？管道？后台执行？普通命令参数？
    while (1)
    {
        try = parse(command, 1);
        if (try == NULL)
            break;

        else if (strcmp(try, ">") == 0)  // 重定向到一个文件的情况
        {
            try = parse(command, 1);   // 得到输出文件名
            file_out(arg, try, 0);        // 参数 0 代表覆盖的方式重定向
            return;
        }

        else if (strcmp(try, ">>") == 0)   // 追加重定向到一个文件
        {
            try = parse(command, 1);
            file_out(arg, try, 1);        // 参数 1 代表追加的方式重定向
            return;
        }

        else if (strcmp(try, "<") == 0)    // 标准输入重定向
        {
            try = parse(command, 1);      // 输入重定向的输入文件
            char *out_file = parse(command, 1);    // 输出重定向的输出文件
            if (out_file != NULL)
            {
                if (strcmp(out_file, ">") == 0)   // 输入输出文件给定
                {
                    out_file = parse(command, 1);
                    if (out_file == NULL)
                    {
                        printf("Syntax error !!\n");
                        return;
                    }
                    else
                        file_in(arg, try, out_file, 1);     // 参数 1 针对双重定向 < >
                }
                else if (strcmp(out_file, ">>") == 0)
                {
                    out_file = parse(command, 1);
                    if (out_file == NULL)
                    {
                        printf("Syntax error !!\n");
                        return;
                    }
                    else
                        file_in(arg, try, out_file, 2);       // 参数 2 针对双重定向 < >>
                }
            }
            else
            {
                file_in(arg, try, NULL, 0);        // 模式 0 针对单一的输入重定向 
            }
        }
        //处理后台进程
        else if (strcmp(try, "&") == 0)   // 后台进程
        {
            bf_exec(arg, 1);     // bf_exec 的第二个参数为 1 代表后台进程
            return;
        }
        else       //try是一个命令参数
        {
            arg[t] = try;
            t += 1;
            arg[t] = NULL;
        }
    }

    bf_exec(arg, 0);     // 参数 0 表示前台运行
    return;
}
void signal_set(){
	     /* 捕捉信号，当信号发生时调用信号处理函数sig_handle，建议用sigaction改写 */
        signal(SIGINT, sig_handle); // SIGINT = 2， 用户键入Ctrl-C
        signal(SIGQUIT, sig_handle); /* SIGQUIT = 3 用户键入Ctr+\ */
        signal(SIGCHLD, bg_signal_handle); //SIGCHLD = 17，一般在子进程中止时产生
        signal(SIGTSTP, sig_handle);  // SIGTSTP =20，一般有Ctrl-Z产生
		return;
}






















