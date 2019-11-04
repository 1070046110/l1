#include "/home/ryan/one.h"

void main(){
	int i;
	pid_t pid;
	pid=fork();
	if(pid==0){
	printf("child:pid=%d,ppid=%d\n",getpid(),getppid());
	i=system("ls -l");
}else if(pid<0){
	printf("error\n");
}else{
	sleep(10);
	printf("father:pid=%d,ppid=%d\n",getpid(),getppid());
	i=system("ping www.baidu.com");
}
}
