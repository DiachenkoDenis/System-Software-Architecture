#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_DIRS 100
#define MAX_NAME 256

int compare_names(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(void) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    char dirs[MAX_DIRS][MAX_NAME];
    int count = 0;

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

        if (S_ISDIR(fileStat.st_mode)) {
            if (count < MAX_DIRS) {
                strncpy(dirs[count], entry->d_name, MAX_NAME - 1);
                dirs[count][MAX_NAME - 1] = '\0';
                count++;
            }
        }
    }

    closedir(dir);

    qsort(dirs, count, sizeof(dirs[0]), compare_names);

    printf("Subdirectories in alphabetical order:\n");

    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
    }

    return 0;
}
