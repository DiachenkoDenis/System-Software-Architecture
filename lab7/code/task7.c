#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int is_c_file(const char *filename) {
    size_t len = strlen(filename);

    if (len < 3) {
        return 0;
    }

    return strcmp(filename + len - 2, ".c") == 0;
}

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");

    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

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
        if (!is_c_file(entry->d_name)) {
            continue;
        }

        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat failed");
            continue;
        }

        printf("\nFile: %s\n", entry->d_name);
        printf("Current permissions: ");
        print_permissions(fileStat.st_mode);
        printf("\n");

        printf("Give read permission to others? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            mode_t new_mode = fileStat.st_mode | S_IROTH;

            if (chmod(entry->d_name, new_mode) == -1) {
                perror("chmod failed");
            } else {
                printf("Read permission for others was added.\n");
            }
        } else {
            printf("Permission was not changed.\n");
        }
    }

    closedir(dir);

    return 0;
}
