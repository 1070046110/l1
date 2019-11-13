fork()
f.c -- f  生成test1.txt

vfork()
vf.c --vf 生成test2.txt

经测试，无论父子进程谁先运行，后运行的进程会把先运行进程的写入覆盖掉，
所以父子进程使用独自的文件指针
