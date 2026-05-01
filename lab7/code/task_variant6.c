#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define THRESHOLD 3

int main(void) {
    FILE *file;
    char filename[256];
    int usage_count;
    struct stat fileStat;

    file = fopen("usage.txt", "r");

    if (file == NULL) {
        perror("fopen failed");
        return 1;
    }

    while (fscanf(file, "%255s %d", filename, &usage_count) == 2) {

        if (stat(filename, &fileStat) == -1) {
            perror("stat failed");
            continue;
        }

        printf("File: %s, usage count: %d\n", filename, usage_count);

        if (usage_count >= THRESHOLD) {
            mode_t new_mode = fileStat.st_mode | S_IROTH;

            if (chmod(filename, new_mode) == -1) {
                perror("chmod failed");
            } else {
                printf("Read permission for others was added.\n");
            }
        } else {
            mode_t new_mode = fileStat.st_mode & ~S_IROTH;

            if (chmod(filename, new_mode) == -1) {
                perror("chmod failed");
            } else {
                printf("Read permission for others was removed.\n");
            }
        }

        printf("\n");
    }

    fclose(file);

    return 0;
}
