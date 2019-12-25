#include "/home/ryan/one.h"

int i=0;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void *writer1(void *param){
	printf("writer1\n");
	int fd1=(int)param;
	int r;
	for(int i=0;i<100;i++){
		if(i!=0)
			pthread_cond_wait(&cond,&lock);

		char buf1[1000]="";
		r=rand()%10000+1;
		sprintf(buf1,"work1:%d\t",r);
		write(fd1,buf1,strlen(buf1));

		pthread_mutex_lock(&lock);
		i=1;
		pthread_mutex_unlock(&lock);
		if(i==1)
			pthread_cond_signal(&cond);		
}
	printf("writer1 over\n");
}

void *writer2(void *param){
	printf("writer2\n");
	int fd2=(int)param;
	int r;
	for(int i=0;i<100;i++){	
		if(i!=1)
			pthread_cond_wait(&cond,&lock);

		char buf2[100000]="";
		r=rand()%10000+10001;
		sprintf(buf2,"work2:%d\t",r);
		write(fd2,buf2,strlen(buf2));
		
		pthread_mutex_lock(&lock);
		i=0;
		pthread_mutex_unlock(&lock);
		if(i==0)
			pthread_cond_signal(&cond);	
}	
	printf("writer2 over\n");
}

void *reader(void *param){
	int fd3=(int)param;
	printf("reader\n");
	int size=0;
	int ret;
	int len;
	char buf3[100000]="";

	if((len=(lseek(fd3,0,SEEK_CUR)))==-1)
		printf("read1 error\n");
	lseek(fd3,0,SEEK_SET);
	if((ret=read(fd3,buf3,len))==-1)
		printf("read2 error\n");
	for(int i=0;i<len;i++)
		printf("%c",buf3[i]);
	printf("\nreader over\n");
}

int main(){
	pthread_t tid[3];
	int i=0;
	int fd1=open("./t1.txt",O_RDWR|O_CREAT|O_TRUNC,0644);	

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

	pthread_mutex_destroy(&lock);	
	pthread_cond_destroy(&cond);
	return 0;
}


