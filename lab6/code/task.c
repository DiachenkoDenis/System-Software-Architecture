#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);

    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    printf("File opened successfully, fd = %d\n", fd);

    close(fd);
    return 0;
}
