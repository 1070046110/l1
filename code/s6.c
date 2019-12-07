#include "/home/ryan/one.h"

static volatile sig_atomic_t sigflag=0;
static void sig_usr (int signo){
	psignal(signo," recieved");
}
static void sig_intr (int signo){
	psignal(signo," received");
	sigflag=1;
}
void wait_for_signal(int sig,volatile sig_atomic_t *sflag){
	static sigset_t mask,oldmask;
	sigemptyset(&mask);
	sigaddset(&mask,sig);
	if(sigprocmask(SIG_BLOCK,&mask,&oldmask)<0){
		printf("SIG_BLOCK error");
		exit(1);
}
	sigdelset(&oldmask,SIGUSR1);
	sigdelset(&oldmask,SIGUSR2);
	while(!*sflag){
		printf("door opened\n");
		sigsuspend(&oldmask);
		printf("door closed\n");
}
	*sflag=0;
	if(sigprocmask(sig,&oldmask,NULL)<0)
		printf("SIG_SETMASK error");
}

int main(void){
	pid_t pid;
	static sigset_t mask,oldmask;
	signal(SIGUSR1,sig_usr);
	signal(SIGUSR2,sig_usr);
	signal(SIGINT,sig_intr);
	sigemptyset(&mask);
	sigaddset(&mask,SIGUSR1);
	sigaddset(&mask,SIGUSR2);
	if(sigprocmask(SIG_BLOCK,&mask,&oldmask)<0){
		printf("SIG_BLOCK error");
		exit(1);
}
	if((pid=fork())==0){
		kill(getppid(),SIGUSR1);
		kill(getppid(),SIGUSR2);
		printf("child ok");
		while(1);
}else{
		wait_for_signal(SIGINT,&sigflag);
		printf("Now,I can do my work.\n");
		kill(pid,SIGTERM);
}
		exit(0);
}
