#include "/home/ryan/one.h"

void main(){

	pid_t pid;
	pid=fork();

if(pid<0){
	printf("error\n");
}else if(pid==0){
	printf("child:pid=%d,ppid=%d\n",getpid(),getppid());
	exit(1);
}else{
	wait(NULL);
	printf("father:pid=%d,ppid=%d\n",getpid(),getppid());
}
}
