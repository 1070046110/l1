#include "/home/ryan/one.h"

void main(){
pid_t pid;
pid=fork();
int fd;
fd=open("test1.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR,0777);

if(pid<0){
	perror("fork error!\n");
}else if(pid==0){
	printf("child running! pid=%d\n",getpid());
	for(int i=0;i<10;i++){
	char b[1000]="";
	sprintf(b,"child: %d\t",i);
	printf("%s",b);
	write(fd,b,strlen(b));
}
	exit(0);
}else{
	//sleep(2);
	printf("parent running! pid=%d\n",getpid());
	for(int i=0;i<10;i++){
	char c[1000]="";
	sprintf(c,"parent: %d\t",i);
	printf("%s",c);
	write(fd,c,strlen(c));
}
	exit(0);
}
}
