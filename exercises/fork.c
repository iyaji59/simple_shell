#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
        exit(1);
    }
    if (pid1 == 0) {
        printf("I am the first child process! My PID is %d, my parent's PID is %d\n", getpid(), getppid());
        exit(0);
    }
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork2");
        exit(1);
    }
    if (pid2 == 0) {
        printf("I am the second child process! My PID is %d, my parent's PID is %d\n", getpid(), getppid());
        exit(0);
    }
    printf("I am the parent process! My PID is %d\n", getpid());
    return 0;
}

