#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t max_size = (size_t)-1;
    printf("Maximum value of size_t: %zu\n", max_size);
    void *ptr = malloc(max_size);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    } else {
        printf("Memory allocated\n");
        free(ptr);
    }
    return 0;
}
