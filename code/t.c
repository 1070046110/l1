#include "/home/ryan/one.h"

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

static pthread_rwlock_t rwlock;
static int sem_id1=0;
static int set_semvalue1();
static void del_semvalue1();
static int semaphore_p1();
static int semaphore_v1();

static int sem_id2=0;
static int set_semvalue2();
static void del_semvalue2();
static int semaphore_p2();
static int semaphore_v2();

void *writer1(void *param){
	printf("writer1\n");
	int fd1=(int)param;
	int r;
	pthread_rwlock_wrlock(&rwlock);
	for(int i=0;i<100;i++){
		semaphore_p1();
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
		semaphore_p2();
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
	char buf[100000]="";

	if((len=(lseek(fd3,0,SEEK_CUR)))==-1)
		printf("read error\n");
		lseek(fd3,0,SEEK_SET);
	if((ret=read(fd3,buf,len))==-1)
		printf("read error\n");
	for(int i=0;i<len;i++)
		printf("%c",buf[i]);
	pthread_rwlock_unlock(&rwlock);
	printf("reader over\n");
	semaphore_v1();
	semaphore_v2();


	return NULL;
}

int main(){
	pthread_t tid[3];
	int i=0;
	int fd1=open("./t.txt",O_RDWR|O_CREAT|O_TRUNC,0644);	

	sem_id1=semget((key_t)1234,1,0666|IPC_CREAT);
	sem_id2=semget((key_t)1234,1,0666|IPC_CREAT);
	set_semvalue1();
	set_semvalue2();	

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
	while(i-->0){
		pthread_join(tid[i],NULL);
}

	del_semvalue1();
	del_semvalue2();
	pthread_rwlockattr_destroy(&rwlock_attr);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}

static int set_semvalue1(){
	union semun sem_union1;
	sem_union1.val=1;
	if(semctl(sem_id1,0,SETVAL,sem_union1)==-1)
		return 0;
	return 1;
}

static int set_semvalue2(){
	union semun sem_union2;
	sem_union2.val=1;
	if(semctl(sem_id2,0,SETVAL,sem_union2)==-1)
		return 0;
	return 1;
}

static void del_semvalue1(){
	union semun sem_union1;
	if(semctl(sem_id1,0,IPC_RMID,sem_union1)==-1)
		fprintf(stderr,"failed to delete semaphore\n");
}

static void del_semvalue2(){
	union semun sem_union2;
	if(semctl(sem_id2,0,IPC_RMID,sem_union2)==-1)
		fprintf(stderr,"failed to delete semaphore\n");
}


static int semaphore_p1(){
	struct sembuf sem_b1;
	sem_b1.sem_num=0;
	sem_b1.sem_op=-1;
	sem_b1.sem_flg=SEM_UNDO;
	if(semop(sem_id1,&sem_b1,1)==-1){
		fprintf(stderr,"semaphore_p failed\n");
		return 0;
}
	return 1;
}

static int semaphore_v1(){
	struct sembuf sem_b1;
	sem_b1.sem_num =0;
	sem_b1.sem_op=1;
	sem_b1.sem_flg=SEM_UNDO;
	if(semop(sem_id1,&sem_b1,1)==-1){
		fprintf(stderr,"semaphore_v failed\n");
		return 0;
}
	return 1;
}

static int semaphore_p2(){
	struct sembuf sem_b2;
	sem_b2.sem_num=0;
	sem_b2.sem_op=-1;
	sem_b2.sem_flg=SEM_UNDO;
	if(semop(sem_id2,&sem_b2,1)==-1){
		fprintf(stderr,"semaphore_p failed\n");
		return 0;
}
	return 1;
}

static int semaphore_v2(){
	struct sembuf sem_b2;
	sem_b2.sem_num =0;
	sem_b2.sem_op=1;
	sem_b2.sem_flg=SEM_UNDO;
	if(semop(sem_id2,&sem_b2,1)==-1){
		fprintf(stderr,"semaphore_v failed\n");
		return 0;
}
	return 1;
}

