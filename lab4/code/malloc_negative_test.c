#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 50000;
    int xb = 50000;
    int num = xa * xb;
    printf("xa = %d\n", xa);
    printf("xb = %d\n", xb);
    printf("num = xa * xb = %d\n", num);
    void *ptr = malloc(num);

    if (ptr == NULL) {
        printf("malloc failed\n");
    } else {
        printf("malloc succeeded\n");
        free(ptr);
    }

    return 0;
}
