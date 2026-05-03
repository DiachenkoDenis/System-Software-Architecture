#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    printf("fork returned: %d\n", pid);

    if (pid == 0) {
        printf("This is child process\n");
    } else {
        printf("This is parent process, child PID = %d\n", pid);
    }

    return 0;
}
