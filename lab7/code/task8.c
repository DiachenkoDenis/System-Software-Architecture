#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char answer;

    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat failed");
            continue;
        }

        if (!S_ISREG(fileStat.st_mode)) {
            continue;
        }

        printf("File: %s\n", entry->d_name);
        printf("Delete this file? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            if (remove(entry->d_name) == 0) {
                printf("File deleted.\n");
            } else {
                perror("remove failed");
            }
        } else {
            printf("File was not deleted.\n");
        }

        printf("\n");
    }

    closedir(dir);

    return 0;
}
