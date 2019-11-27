#include "/home/ryan/one.h"

int main(){
	pid_t r1,r2,r3;
	int r_num;
	int pipefd[2];
	int i;
	char buf[4095];
	memset(buf,0,sizeof(buf));
if(pipe(pipefd)<0){
	perror("pipe failed.\n");
	return -1;
}
	r1=fork();
	if(r1==0){
	printf("child1 running! pid=%d,ppid=%d\n",getpid(),getppid());
	close(pipefd[0]);
	for(i=0;i<4096;i++){
	write(pipefd[1],"a",1);
}
	close(pipefd[1]);
	exit(0);
}else{
	wait(&r1);
	r2=fork();
	if(r2==0){
	printf("child2 running! pid=%d,ppid=%d\n",getpid(),getppid());
	close(pipefd[1]);
	if(r_num=read(pipefd[0],buf,4096)>0)
		printf("child2 read from pipe:%s\n",buf);
	close(pipefd[0]);
	exit(0);
}
	wait(&r2);
	r3=fork();
	if(r3==0){
	printf("child3 running! pid=%d,ppid=%d\n",getpid(),getppid());
	exit(0);
}
	wait(&r3);
	close(pipefd[1]);
	if(r_num=read(pipefd[0],buf,4096)>0)
		printf("parent read from pipe:%s\n",buf);
	close(pipefd[0]);
	exit(0);
	return 0;
}
}
