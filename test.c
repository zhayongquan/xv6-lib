
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
// #include <unistd.h>
// #include <string.h>

// int main(int argc, char *argv[]) {
//     int parent2child[2];  // 父 → 子
//     int child2parent[2];  // 子 → 父
//     char buf[128];

//     if (pipe(parent2child) < 0 || pipe(child2parent) < 0) {
//         perror("pipe failed");
//         exit(1);
//     }

//     int pid = fork();
//     if (pid < 0) {
//         perror("fork failed");
//         exit(1);
//     }

//     if (pid == 0) {
//         // 子进程
//         close(parent2child[1]);  // 关闭写端
//         close(child2parent[0]);  // 关闭读端

//         // 从父进程读取数据
//         memset(buf, 0, sizeof(buf));
//         read(parent2child[0], buf, sizeof(buf));
//         printf("%d: received ping: %s\n", getpid(), buf);

//         // 回复父进程
//         write(child2parent[1], "pong", 5);

//         close(parent2child[0]);
//         close(child2parent[1]);
//         exit(0);
//     } else {
//         // 父进程
//         close(parent2child[0]);  // 关闭读端
//         close(child2parent[1]);  // 关闭写端

//         // 给子进程发消息
//         write(parent2child[1], "ping", 5);

//         // 接收子进程回复
//         memset(buf, 0, sizeof(buf));
//         read(child2parent[0], buf, sizeof(buf));
//         printf("%d: received pong: %s\n", getpid(), buf);

//         close(parent2child[1]);
//         close(child2parent[0]);
//         exit(0);
//     }

//     return 0;
// }




int main(int argc, char *argv[]) {
    int parent2child[2];
    int child2parent[2];
    char buf[128];

    if (pipe(parent2child) < 0 || pipe(child2parent) < 0) {
        printf("pipe failed\n");
        exit(1);
    }

    int pid = fork();
    if(pid < 0) {
        printf("fork failed\n");
        exit(1);
    }

    if(pid == 0) {    //childe process
        close(parent2child[1]);  // close parents read end
        close(child2parent[0]);  // close childe write end

        memset(buf, 0, sizeof(buf));
        read(parent2child[0], buf, sizeof(buf));
        printf("pid is : %d: received ping:%s\n", getpid(),buf);

        write(child2parent[1], "pong", sizeof("pong"));

        close(parent2child[0]);
        close(child2parent[1]);
        exit(0);
    } else {    //parent process
        close(parent2child[0]);
        close(child2parent[1]);

        write(parent2child[1], "ping", sizeof("ping"));

        memset(buf, 0, sizeof(buf));
        read(child2parent[0], buf, sizeof(buf));
        printf("pid is : %d: received pong:%s\n", getpid(),buf);

        close(parent2child[1]);
        close(child2parent[0]);
        exit(0);    
    }
    return 0;
}