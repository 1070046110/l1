#include "/home/ryan/one.h"

void main(){
char* argv[4];
argv[1]="Hello";
argv[2]="World";
argv[0]="/home/ryan/linux/week9/code/test1";
argv[3]=NULL;
printf("pid=%d,ppid=%d\n",getpid(),getppid());
execl("/home/ryan/linux/week9/code/test1",argv);
printf("after\n");
}
