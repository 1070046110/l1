#include "/home/ryan/one.h"
#include "mylib1.h"

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
