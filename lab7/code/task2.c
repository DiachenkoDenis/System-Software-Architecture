#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-" );

    printf( (mode & S_IRUSR) ? "r" : "-" );
    printf( (mode & S_IWUSR) ? "w" : "-" );
    printf( (mode & S_IXUSR) ? "x" : "-" );

    printf( (mode & S_IRGRP) ? "r" : "-" );
    printf( (mode & S_IWGRP) ? "w" : "-" );
    printf( (mode & S_IXGRP) ? "x" : "-" );

    printf( (mode & S_IROTH) ? "r" : "-" );
    printf( (mode & S_IWOTH) ? "w" : "-" );
    printf( (mode & S_IXOTH) ? "x" : "-" );
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat failed");
            continue;
        }

        print_permissions(fileStat.st_mode);

        printf(" %ld", fileStat.st_nlink);
        printf(" %ld", fileStat.st_size);
        printf(" %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
