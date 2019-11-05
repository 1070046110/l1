#include "/home/ryan/one.h"

int main(){
	int ret;
	printf("c1:pid=%d.ppid=%d\n",getpid(),getppid());
	ret=system("./n5 123 abc hello ncu edu");
	printf("after calling ! ret=%d\n",ret);
	return 0;
}
