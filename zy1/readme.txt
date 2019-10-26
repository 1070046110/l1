项目版本1 - zy1

mylib1.h - 头文件
wl1.c - 功能实现文件1   -wl1.o 
wl2.c - 功能实现文件2   -wl2.o
w1t.c - 项目main函数文件  -w1t.o

静态库文件 - libone.a
静态库可执行文件 - -w1t

动态库文件 - libone.so
动态库可执行文件 - w1t

creat1() - 创建文件  - 创建生成w1.txt
write1() - 写文件
read1() - 读文件
access() - 显示文件权限
rccess() - 更改文件权限
