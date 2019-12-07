#include "/home/ryan/one.h"

void sigtoutine(int dunno){
	switch(dunno){
		case 1:
			printf("Get a signal SIGHUP\n");
			break;
		case 2:
			printf("Get a signal SIGINT\n");
			break;
		case 3:
			printf("Get a signal SIGQUIT\n");
			break;
}
}

int main(){ 
	printf("process id is %d\n",getpid());
	printf(SIGHUP,sigtoutine);
	printf(SIGINT,sigtoutine);
	printf(SIGQUIT,sigtoutine);
	while(1);
}
