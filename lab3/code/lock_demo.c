#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>

int main() {
    size_t size = 1024 * 1024; 
    char *ptr = malloc(size);
    if (!ptr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    memset(ptr, 0, size);

    if (mlock(ptr, size) != 0) {
        printf("mlock failed: %s\n", strerror(errno));
        free(ptr);
        return 1;
    }

    printf("Memory locked successfully\n");

    munlock(ptr, size);
    free(ptr);
    return 0;
}
