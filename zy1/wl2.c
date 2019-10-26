#include "/home/ryan/one.h"

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
