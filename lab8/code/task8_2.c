#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd;
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    fd = open("bytes.bin", O_CREAT | O_TRUNC | O_RDWR, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write(fd, data, sizeof(data)) != (ssize_t)sizeof(data)) {
        perror("write");
        close(fd);
        return 1;
    }

    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    if (read(fd, buffer, sizeof(buffer)) != (ssize_t)sizeof(buffer)) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("File bytes: 4 5 2 2 3 3 7 9 1 5\n");
    printf("After lseek(fd, 3, SEEK_SET) and read 4 bytes:\n");
    printf("Buffer contains: ");

    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }

    printf("\n");

    close(fd);
    return 0;
}
