#include "/home/ryan/one.h"

int main(){
	pid_t r;
	int r_num;
	int pipefd[2];
	int i;
	char buf[65536];
	memset(buf,0,sizeof(buf));
	if(pipe(pipefd)<0){
	perror("pipe failed.\n");
	return -1;
}
	r=fork();
	if(r<0){
	perror("fork failed.\n");
	return -1;
}else if(r==0){
	printf("child running!\n");
	close(pipefd[0]);
	for(i=0;i<65537;i++){
	write(pipefd[1],"a",1);
}
	printf("child write ok.\n");
	close(pipefd[1]);
}else{
	wait(&r);
	close(pipefd[1]);
	if(r_num=read(pipefd[0],buf,65536)>0)
		printf("parent read from pipe:%s\n",buf);
	close(pipefd[0]);
	exit(0);
	return 0;
}
}
