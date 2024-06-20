// Lab Xv6 and Unix utilities
// pingpong.c

// 引入声明类型的头文件
#include "kernel/types.h"
// 引入声明系统调用和 user/ulib.c 中其他函数的头文件
#include "user/user.h"
#include "stddef.h"

// int main(int argc,char* argv[])
// argc 是命令行总的参数个数
// argv[] 是 argc 个参数，其中第 0 个参数是程序的全名，以后的参数是命令行后面跟的用户输入的参数
int main(int argc, char *argv[])
{
    int ptoc[2], ctop[2];
    // 使用pipe创建管道
    pipe(ptoc);
    pipe(ctop);
    char buf[8];
    if (fork() == 0)
    {
        // child
        read(ptoc[0], buf, 4);
        printf("Child pid %d: receive %s\n", getpid(), buf);
        write(ctop[1], "pong", strlen("pong"));
    }
    else
    {
        // parent
        write(ptoc[1], "ping", strlen("ping"));
        wait(NULL);
        read(ctop[0], buf, 4);
        printf("Parent pid %d: received %s\n", getpid(), buf);
    }
    exit(0);
}
