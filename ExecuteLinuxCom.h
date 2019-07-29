#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/utsname.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/ptrace.h>
#include<sys/types.h>
#include<pwd.h>
#define MAX 1024
#define MAX_COMM 100


void print_prompt();
void bj_struct_handle(pid_t pid,char *arg[],int type);
char cwd[MAX];
char *all[MAX];
int current_out=4;
int current_in=5;
int fd[4];

typedef struct proc{
  pid_t pid;
  int status;
  char *arg[MAX_COMM];
  struct proc *next;
} proc;

proc *start=null;

