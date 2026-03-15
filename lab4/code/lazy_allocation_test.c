#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_mem() {
    FILE *f = fopen("/proc/self/status", "r");
    char line[256];

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "VmSize:", 7) == 0 ||
            strncmp(line, "VmRSS:", 6) == 0) {
            printf("%s", line);
        }
    }

    fclose(f);
}

int main() {

    size_t size = 1024L * 1024L * 1024L; 

    printf("Before malloc:\n");
    print_mem();

    char *ptr = malloc(size);

    printf("\nAfter malloc:\n");
    print_mem();

    for (size_t i = 0; i < size; i += 4096) {
        ptr[i] = 1;
    }

    printf("\nAfter touching memory:\n");
    print_mem();

    free(ptr);

    return 0;
}
