#include "/home/ryan/one.h"

static jmp_buf g_stack_env;

static void fun1(int *a,int *b,int *c);
//static void fun2(void);

int main(void){
	int a=1;
	int b=2;
	int c=3;

	if(0==setjmp(g_stack_env)){
		printf("Normal flow\n");
		printf("1:a=%d,b=%d,c=%d\n",a,b,c);
		fun1();
}else{
		printf("Long jump flow\n");
		printf("2:a=%d,b=%d,c=%d\n",a,b,c);
}
	return 0;
}

static void fun1(void){
	printf("Enter fun1\n");
	++(*a);
	++(*b);
	++(*c);
	
	//fun2();
}

/*static void fun2(void){
	printf("Enter fun2\n");
	longjmp(g_stack_env,1);
	printf("Leave func2\n");
}*/
