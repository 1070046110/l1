#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void raccess(char* argv){
if(access(argv,R_OK)<0){
	perror("access error\n");
	exit(1);
}else
	printf("read access ok\n");

if(access(argv,W_OK)<0){
	perror("access error\n");
	exit(1);
}else
	printf("write access ok\n");
}

void caccess(char *argv){
int a;
printf("选择希望增加的权限：\n1.用户读权限 \n2.用户写权限\n");
scanf("%d",&a);
switch(a){
case 1:
if(chmod(argv,S_IRUSR)<0){
	perror("add read access error\n");
}else
	printf("add read access ok\n");
break;
case 2:
if(chmod(argv,S_IWUSR)<0){
	perror("add write access error\n");
}else
	printf("add write access ok\n");
break;
}
}


int main(){
int fd,a;
char *s="hello world\n";
while(1){
printf("========================\n");
printf("       0.退出           \n");
printf("       1.创建文件       \n");
printf("       2.写文件         \n");
printf("       3.读文件         \n");
printf("       4.查看文件权限   \n");
printf("       5.修改文件权限   \n");
printf("========================\n");
scanf("%d",&a);

switch(a){
case 0:return 0;
case 1:fd=creat1();break;
case 2:write1(fd,s);break;
case 3:read1(fd);break;
case 4:raccess("w1.txt");break;
case 5:caccess("w1.txt");break;
}
}
}


