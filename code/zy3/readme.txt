创建两个子进程child1,child2，向同一个文件text3.txt中写入。
父进程读出

f2.c --f2 text3.txt

最终结果child2写入完之后child1写入，内容都会保存没有覆盖
验证亲缘子进程间共用文件指针

