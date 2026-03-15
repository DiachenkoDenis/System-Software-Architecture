#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Case 1: realloc(NULL, size)\n");
    int *ptr = realloc(NULL, 5 * sizeof(int));
    if (ptr == NULL) {
        printf("realloc returned NULL\n");
    } else {
        printf("realloc worked like malloc\n");
    }
    printf("Case 2: realloc(ptr, 0)\n");
    void *result = realloc(ptr, 0);
    if (result == NULL) {
        printf("realloc(ptr, 0) returned NULL\n");
    } else {
        printf("realloc(ptr, 0) returned non-NULL pointer\n");
    }
    return 0;
}
