#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define CHILDREN 3
#define WRITES 5

void run_test(const char *filename, int use_append) {
    int flags = O_CREAT | O_WRONLY | O_TRUNC;

    if (use_append) {
        flags |= O_APPEND;
    }

    int fd = open(filename, flags, 0644);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("\nTest file: %s\n", filename);
    printf("Mode: %s\n", use_append ? "with O_APPEND" : "without O_APPEND");

    for (int i = 0; i < CHILDREN; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            close(fd);
            exit(1);
        }

        if (pid == 0) {
            char buffer[128];

            for (int j = 0; j < WRITES; j++) {
                if (!use_append) {
                    lseek(fd, 0, SEEK_SET);
                }

                snprintf(buffer, sizeof(buffer), "child %d write %d\n", i + 1, j + 1);
                write(fd, buffer, strlen(buffer));
                usleep(10000);
            }

            close(fd);
            exit(0);
        }
    }

    for (int i = 0; i < CHILDREN; i++) {
        wait(NULL);
    }

    close(fd);
}

void print_file(const char *filename) {
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return;
    }

    char buffer[1024];
    ssize_t count;

    printf("\nContent of %s:\n", filename);

    while ((count = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[count] = '\0';
        printf("%s", buffer);
    }

    close(fd);
}

int main(void) {
    run_test("without_append.txt", 0);
    run_test("with_append.txt", 1);

    print_file("without_append.txt");
    print_file("with_append.txt");

    return 0;
}
