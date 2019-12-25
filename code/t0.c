#include "/home/ryan/one.h"
#include <semaphore.h>

sem_t sem_A,sem_B,sem_C;

void *writer1(void *param){
	//printf("writer1\n");
	int fd1=(int)param;
	int r;
	for(int a=0;a<10;a++){
	sem_wait(&sem_A);
	char buf1[100000]="";
	r=rand()%10000+1;
	time_t t;
	time(&t);
	struct tm *ptime;
	ptime=localtime(&t);
	sprintf(buf1,"%d:work1:%d\ttime:%02d:%02d:%02d\t",a,r,ptime->tm_hour,ptime->tm_min,ptime->tm_sec);
	write(fd1,buf1,strlen(buf1));
	sem_post(&sem_B);
}

	//printf("writer1 over\n");
}

void *writer2(void *param){
	//printf("writer2\n");
	int fd2=(int)param;
	int r;
	for(int a=0;a<10;a++){
	sem_wait(&sem_B);
	char buf2[100000]="";
	r=rand()%10000+10001;
	time_t t;
	time(&t);
	struct tm *ptime;
	ptime=localtime(&t);
	sprintf(buf2,"work2:%d\ttime:%02d:%02d:%02d\n",r,ptime->tm_hour,ptime->tm_min,ptime->tm_sec);
	write(fd2,buf2,strlen(buf2));
	sem_post(&sem_C);	
}	

	//printf("writer2 over\n");
}

void *reader(void *param){

	int fd3=(int)param;
	//printf("reader\n");
	int size=0;
	int ret;
	int len;
	char buf3[100000]="";
	for(int a=0;a<10;a++){
	sem_wait(&sem_C);
	if((len=(lseek(fd3,0,SEEK_CUR)))==-1)
		printf("read1 error\n");
	lseek(fd3,0,SEEK_SET);
	if((ret=read(fd3,buf3,len))==-1)
		printf("read2 error\n");
	for(int i=0;i<len;i++)
		printf("%c",buf3[i]);
	printf("\n");
	//printf("\nreader over\n");
	sem_post(&sem_A);
}
}

int main(){
	pthread_t tid[3];
	int i=0;
	sem_init(&sem_A,0,1);
	sem_init(&sem_B,0,0);
	sem_init(&sem_C,0,0);
	int fd1=open("./t0.txt",O_RDWR|O_CREAT|O_TRUNC,0644);	

	for(i=0;i<3;i++){
		if(i==0){
			pthread_create(&tid[i],NULL,reader,(void*)fd1);
}else if(i==1){
			pthread_create(&tid[i],NULL,writer2,(void*)fd1);
}else if(i==2){
			pthread_create(&tid[i],NULL,writer1,(void*)fd1);
}
}

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	
	sem_destroy(&sem_A);
	sem_destroy(&sem_B);
	sem_destroy(&sem_C);
	return 0;
}

