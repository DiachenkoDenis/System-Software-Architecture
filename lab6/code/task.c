#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *ptr = malloc(32);

    if (ptr == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    strcpy(ptr, "Hello from heap memory");
    printf("Before free: %s\n", ptr);

    free(ptr);

    ptr[0] = 'X';

    printf("After free: %s\n", ptr);

    return 0;
}
