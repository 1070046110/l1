#include "/home/ryan/one.h"
#define NUM_THREADS 4
void hello(void * t){
	pthread_t my_tid;
	my_tid=pthread_self();
	int x=0;
	for(int i=1;i<101;i++){
	x=x+i;
}
	printf("\tThread %d:my tid is %lx,x=%d\n",t,my_tid,x);
}

int main(){
	pthread_t tid;
	int rv,t;
	for(t=0;t<NUM_THREADS;t++){
	rv=pthread_create(&tid,NULL,(void*(*)())hello,(void*)t);
	if(rv!=0){
		printf("thread create failed!\n");
		return -1;
}
	printf("Create thread %lx\n",tid);
	pthread_join(tid,NULL);
}
	printf("Good bye!\n");
	//pthread_join(tid,NULL);
	//pthread_exit(NULL);
	return 0;
}
