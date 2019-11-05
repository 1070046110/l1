#include "/home/ryan/one.h"

int main(){
	char *arg[]={"./n5","123","abc","hello","ncu","edu",NULL};
	int ret;
	printf("c1:pid=%d.ppid=%d\n",getpid(),getppid());
	ret=execvp("n5",arg);
	printf("after calling ! ret=%d\n",ret);
	return 0;
}
