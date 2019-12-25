#include "/home/ryan/one.h"

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

static pthread_rwlock_t rwlock;
static int sem_id=0;
static int set_semvalue();
static void del_semvalue();
static int semaphore_p();
static int semaphore_v();

void *writer1(void *param){
	printf("writer1\n");
	int fd1=(int)param;
	int r;
	pthread_rwlock_wrlock(&rwlock);
	for(int i=0;i<100;i++){
		//semaphore_p();
		char buf1[1000]="";
		r=rand()%10000+1;
		sprintf(buf1,"work1:%d\t",r);
		write(fd1,buf1,strlen(buf1));		
}
	pthread_rwlock_unlock(&rwlock);
	printf("writer1 over\n");
	return NULL;
}

void *writer2(void *param){
	printf("writer2\n");
	int fd2=(int)param;
	int r;
	pthread_rwlock_wrlock(&rwlock);
	for(int i=0;i<100;i++){
		//semaphore_v();
		//semaphore_p();
		char buf2[100000]="";
		r=rand()%10000+10001;
		sprintf(buf2,"work2:%d\t",r);
		write(fd2,buf2,strlen(buf2));
}	
	pthread_rwlock_unlock(&rwlock);
	printf("writer2 over\n");
	return NULL;
}

void *reader(void *param){
	int fd3=(int)param;
	printf("reader\n");
	pthread_rwlock_rdlock(&rwlock);
	int size=0;
	int ret;
	int len;
	int a;
	char buf3[100000]="";

	if((len=(lseek(fd3,0,SEEK_CUR)))==-1)
		printf("read1 error\n");
	lseek(fd3,0,SEEK_SET);
	if((ret=read(fd3,buf3,len))==-1)
		printf("read2 error\n");
	for(int i=0;i<len;i++)
		printf("%c",buf3[i]);
	pthread_rwlock_unlock(&rwlock);
	printf("\nreader over\n");
	//semaphore_v();


	return NULL;
}

int main(){
	pthread_t tid[3];
	int i=1;
	int fd1=open("./t2.txt",O_RDWR|O_CREAT|O_TRUNC,0644);	

	sem_id=semget((key_t)1234,1,0666|IPC_CREAT);
	set_semvalue();	

	pthread_rwlockattr_t rwlock_attr;
	pthread_rwlockattr_init(&rwlock_attr);
	#ifdef WRITER_FIRST					       pthread_rwlockattr_setkind_np(&rwlock_attr,PTHREAD_RWLOCK_PREFER_WRITTER_NONRECURSIVE_NP);
	#endif
	pthread_rwlock_init(&rwlock,&rwlock_attr);
	pthread_rwlock_rdlock(&rwlock);

	for(i=1;i<=3;i++){
		if(i==1){
			pthread_create(&tid[i],NULL,reader,(void*)fd1);
}else if(i==2){
			pthread_create(&tid[i],NULL,writer2,(void*)fd1);
}else if(i==3){
			pthread_create(&tid[i],NULL,writer1,(void*)fd1);
}
}

	pthread_rwlock_unlock(&rwlock);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);

	del_semvalue();
	pthread_rwlockattr_destroy(&rwlock_attr);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}

static int set_semvalue(){
	union semun sem_union;
	sem_union.val=1;
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)
		return 0;
	return 1;
}

static void del_semvalue(){
	union semun sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
		fprintf(stderr,"failed to delete semaphore\n");
}


static int semaphore_p(){
	struct sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=-1;
	sem_b.sem_flg=SEM_UNDO;
	if(semop(sem_id,&sem_b,1)==-1){
		fprintf(stderr,"semaphore_p failed\n");
		return 0;
}
	return 1;
}

static int semaphore_v(){
	struct sembuf sem_b;
	sem_b.sem_num =0;
	sem_b.sem_op=1;
	sem_b.sem_flg=SEM_UNDO;
	if(semop(sem_id,&sem_b,1)==-1){
		fprintf(stderr,"semaphore_v failed\n");
		return 0;
}
	return 1;
}



