#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc ,char *argv) {
	pid_t pid;        	// 定义一个进程号类型的变量 pid
						// 在此程序中，此时只有一个进程在运行
    pid = fork();       // 在此程序中，此时只有两个进程在运行，默认先进性父进程再进行主进程
						// 子进程的pid=0，父进程的pid>0
    if(pid < 0) {
		printf("error in fork!");
		fprintf(stderr,"Fork Failed\n");
		exit(-1);
	} else if (pid == 0) {
		printf("I am the child process,ID is %d\n",getpid());
		//execlp("/bin/ls","ls",NULL);
	} else {
		//printf("parent is going to wait...\n");
		//wait(NULL);
		printf("I am the parent process,ID is %d\n",getpid());
	}
    return 0;
}
