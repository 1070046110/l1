fork()

通过sleep使子进程先于父进程运行
n3.c -- n3

通过wait使子进程先于父进程运行
n4.c -- n4

exec()

n2.c -- test1.c
n1.c -- test.c

回调函数
n5.c -- n5  
n6.c -- n6  -- while无限循环

system  c1.c  -- 调用n5
execvp  c2.c  -- 调用n5

内存错误测试
memtest.c -- mt

长跳转
j1.c -- j1
