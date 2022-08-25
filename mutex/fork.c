#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
        int data=0;
        pid_t pid=fork();
        if(pid==0) {
                data=10;
                printf("child:%d\n", data);
                exit(0);
        } else {
                printf("parent:%d\n", data);
                waitpid(pid, NULL, 0);
                printf("parent end:%d\n", data);
        }
        return 0;
}