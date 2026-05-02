#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    int flags = fcntl(fd[1], F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl get");
        return 1;
    }

    if (fcntl(fd[1], F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl set");
        return 1;
    }

    char buffer[1024];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t count;
    size_t total = 0;

    while (1) {
        count = write(fd[1], buffer, sizeof(buffer));

        if (count == -1) {
            perror("write");
            break;
        }

        total += count;

        if (count != (ssize_t)sizeof(buffer)) {
            printf("Partial write detected\n");
            printf("Requested: %zu bytes\n", sizeof(buffer));
            printf("Actually written: %zd bytes\n", count);
            break;
        }
    }

    printf("Total written before failure/partial write: %zu bytes\n", total);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
