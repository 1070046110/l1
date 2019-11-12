e1.c -- e1
_exit();

e2.c -- e2
exit();     生成 test.txt

e3.c -- e3

f1.c -- f1
vfork();

多进程
1-4.c -- 1-4 生成test.dat
1-5.c -- 1-5
1-6.c -- 1-6

1-2.c -- 1-2 通过子进程使进程死锁
1-3.c -- 1-3 调用execl，显示内存使用情况 ，测试用例 test -- test.c
