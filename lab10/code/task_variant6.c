#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;
    for (i = 1; i <= 5; i++) {
        pid = fork(); 
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        
        if (pid == 0) {
            printf("Child %d, PID: %d\n", i, getpid());
            exit(0);  
        }
    }
    for (i = 1; i <= 5; i++) {
        wait(NULL); 
    }
    printf("All child processes have finished. Parent PID: %d\n", getpid());
    return 0;
}
