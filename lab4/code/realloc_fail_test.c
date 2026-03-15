#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(10 * sizeof(int));
    if (!ptr) {
        printf("Initial malloc failed\n");
        return 1;
    }
    printf("Initial allocation successful\n");
    size_t huge_size = (size_t)1024 * 1024 * 1024 * 1024;
    int *new_ptr = realloc(ptr, huge_size);
    if (!new_ptr) {
        printf("realloc failed\n");
        free(ptr);
    } else {
        printf("realloc succeeded\n");
        free(new_ptr);
    }
    return 0;
}
