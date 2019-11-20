#include "/home/ryan/one.h"

int main(){
int pid1,pid2,s1,p1,p2,s2;
if((pid1=fork())&&(pid2=fork())<0){
	perror("failed to fork@\n");
	return -1;
}else if(pid1==0){
	printf("%d: child1 is running now\n",getpid());	
	printf("%d: child1 is exit now\n",getpid());
	exit(120);
}else if(pid2==0){
	printf("%d: child2 is running now\n",getpid());	
	printf("%d: child2 is exit now\n",getpid());
	exit(130);
}else{
	printf("%d :parent is wating zombie now\n",getpid());
	p1=wait(&s1);
	p2=wait(&s2);
	if(WEXITSTATUS(s1)==120){
	printf("child1 %d\n",p1);
}else if(WEXITSTATUS(s2)==130){
	printf("child2 %d\n",p2);
}
}
exit(0);
}
