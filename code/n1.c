#include "/home/ryan/one.h"
void main(){
printf("call:pid=%d,ppid=%d\n",getpid(),getppid());
system("/home/ryan/linux/week9/code/test");
printf("after calling\n");
}
