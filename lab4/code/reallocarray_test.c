#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int a;
    double b;
    char c;
};

int main() {
    struct sbar *ptr, *newptr;

    ptr = calloc(1000, sizeof(struct sbar));

    if (ptr == NULL) {
        printf("calloc failed\n");
        return 1;
    }

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));

    if (newptr == NULL) {
        printf("reallocarray failed\n");
        free(ptr);
        return 1;
    }

    printf("reallocarray succeeded\n");
    free(newptr);

    return 0;
}
