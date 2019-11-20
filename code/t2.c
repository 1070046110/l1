#include "/home/ryan/one.h"

int main(){
int pid,s,p;
if((pid=fork())<0){
	perror("failed to fork@\n");
	return -1;
}else if(pid==0){
	printf("%d: child1 is running now\n",getpid());	
	printf("%d: child1 is exit now\n",getpid());
	exit(120);
}else{
	printf("%d :parent is wating zombie now\n",getpid());
	while((p=waitpid(pid,&s,WNOHANG))!=-1){
	printf("%d :parent is exiting now\n",getpid());
	if(WIFEXITED(s)){
	printf("child %d is exiting normally.exit code = %d\n",pid,WEXITSTATUS(s));
}else if(WIFSIGNALED(s)){
	printf("child %d exit by signal.signal no=%d\n",pid,WTERMSIG(s));
}else{
	printf("Not know!\n");
}
}
}
exit(0);
}
