#include "/home/ryan/one.h"

void main(int argc,char* argv[],int i){
argv[0]="/home/ryan/linux/week9/code/test1";
argv[1]="Hello";
argv[2]="World";
argv[3]=NULL;
printf("test1:pid=%d,ppid=%d\n",getpid(),getppid());
for(i=0;i<argc;i++){
printf("%s\n",argv[i]);
}
}

