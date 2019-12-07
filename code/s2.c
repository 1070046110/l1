#include "/home/ryan/one.h"
#define PROWPT "Do you want terminate program?"
char *prompt=PROWPT;
void ctrl_c(signo){
	fprintf(stderr,prompt);
}

int main(){
	struct sigaction act;
	act.sa_handler=ctrl_c;
	sigemptyset(&act.sa_mask);
	if(sigaction(SIGINT,&act,NULL)<0){
		fprintf(stderr,"Install Signal Action Error:%s\n",strerror(errno));
		exit(1);
}
printf("process id is %d\n",getpid());
while(1);
}
