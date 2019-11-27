#include "/home/ryan/one.h"

#define S 4095


int main(void){
	char a[S];
	char b[S];
	char c[S];
	int i;
	memset(a,'A',sizeof(a));
	memset(b,'B',sizeof(b));
	memset(c,'C',sizeof(c));
	int fd[2];
	int ret=pipe(fd);
	if(ret==-1){
		fprintf(stderr,"create pipe error (%s)\n",strerror(errno));
		exit(-1);
}
	pid_t pid;
	pid=fork();
	if(pid==-1){
		fprintf(stderr,"first fork error (%s)\n",strerror(errno));
		exit(-2);
}else if(pid==0){
		close(fd[0]);
		for(i=0;i<4096;i++){
		write(fd[1],"a",1);
}
		printf("[child1] pid=%d write a ok.\n",getpid());
		exit(0);
}
	pid=fork();
	if(pid==-1){
		fprintf(stderr,"second:fork error (%s)\n",strerror(errno));
		exit(-3);	
}else if(pid==0){
		close(fd[0]);
	for(i=0;i<4096;i++){
		write(fd[1],"b",1);
}
	printf("[child2] pid=%d write b ok.\n",getpid());
	exit(0);
}	
	pid=fork();
	if(pid==-1){
		fprintf(stderr,"third:fork error (%s)\n",strerror(errno));
		exit(-4);
}else if(pid==0){
		close(fd[0]);
	for(i=0;i<4096;i++){
		write(fd[1],"c",1);
}
	printf("[child3] pid=%d write c ok.\n",getpid());
	exit(0);
}

	close(fd[1]);
	sleep(2);
	int fd1=open("./test1.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
	char buf[4096]={0};
	int n=1;
	while(1){
		ret=read(fd[0],buf,sizeof(buf));
		if(ret==0)
			break;
		printf("%d pid=%d read %d bytes from pipe buf[4095]=%c\n",n++,getpid(),ret,buf[4095]);	
		write(fd1,buf,ret);
}
	return 0;
}
