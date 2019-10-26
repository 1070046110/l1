#include "/home/ryan/one.h"

int creat1(){
int fd;
if((fd=open("w1.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR,0777))==-1){
	perror("create error\n");
	exit(1);
}else{
	printf("create ok!\n");
}
return fd;
}

void write1(int fd,char *s){
if(write(fd,s,strlen(s))<strlen(s)){
	perror("write error\n");
	exit(1);
}else{
	printf("write ok!\n");
}
}

void read1(int fd){
int size=0;
int ret;
int len;
char buf[100]="";

if((len=(lseek(fd,0,SEEK_CUR)))==-1)
	printf("read error\n");
lseek(fd,0,SEEK_SET);
if((ret=read(fd,buf,len))==-1)
	printf("read error\n");
for(int i=0;i<len;i++)
	printf("%c",buf[i]);

printf("\n");
printf("read ok!\n");
}
