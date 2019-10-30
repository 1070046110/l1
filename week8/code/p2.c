#include <stdio.h>
#include <malloc.h>
void print(char *,int);
int main(){
	char *s1="abcde";  //abcde 作为字符串常量存储在常量区 s1,s2,s5拥有相同地址
	char *s2="abcde";
	char s3[]="abcd";
	long int *s4[100];
	char *s5="abcde";
	int a=5;
	int b=6;
	
	printf("variables address in main function:s1=%p s2=%p s3=%p s4=%p s5=%p a=%p b=%p \n",s1,s2,s3,s4,s5,&a,&b);
	printf("variables address in processcall:n");
	print("ddddddddd",5); //参数入栈从右至左进行，p先进栈，str后进栈 &p>&ptr
	printf("main=%p print=%p \n",main,print);  //编译时先编译的地址低，后编译的地址高 main<print
}

void print(char *str,int p){
	char *s1="abcde";  //abcde在常量区，s1在栈上
	char *s2="abcde";  //&s1>&s2
	char s3[]="abcdeee"; //abcdeee在常量区，s3在栈上，数组保存内容为abcdeee的一份拷贝
	long int *s4[100];
	char *s5="abcde";
	int a=5;
	int b=6;
	int c;
	int d;             //a,b,c,d 均在栈上，&a>&b>&c>&d地址反向增长
	char *q=str;
	int m=p;
	char *r=(char *)malloc(1);
	char *w=(char *)malloc(1);   //r<w 堆正向增长

	printf("s1=%p s2=%p s3=%p s4=%p s5=%p a=%p b=%p c=%p d=%p str=%p q=%p p=%p m=%p r=%p w=%p \n",s1,s2,s3,s4,s5,&a,&b,&c,&d,&str,q,&p,&m,r,w);
}

