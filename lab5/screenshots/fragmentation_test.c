#include <stdio.h>

#define ARENA_SIZE 64

static int used[ARENA_SIZE];

int alloc_block(int size) {
    int count = 0;
    int start = -1;

    for (int i = 0; i < ARENA_SIZE; i++) {
        if (used[i] == 0) {
            if (count == 0) {
                start = i;
            }
            count++;

            if (count == size) {
                for (int j = start; j < start + size; j++) {
                    used[j] = 1;
                }
                return start;
            }
        } else {
            count = 0;
            start = -1;
        }
    }

    return -1;
}

void free_block(int start, int size) {
    for (int i = start; i < start + size; i++) {
        used[i] = 0;
    }
}

void print_arena() {
    for (int i = 0; i < ARENA_SIZE; i++) {
        printf("%c", used[i] ? '#' : '.');
    }
    printf("\n");
}

int count_free_memory() {
    int total = 0;

    for (int i = 0; i < ARENA_SIZE; i++) {
        if (used[i] == 0) {
            total++;
        }
    }

    return total;
}

int main() {

    int a = alloc_block(8);
    int b = alloc_block(16);
    int c = alloc_block(8);
    int d = alloc_block(16);
    int e = alloc_block(8);

    printf("Initial allocation:\n");
    print_arena();

    free_block(b, 16);
    free_block(d, 16);

    printf("After freeing two middle blocks:\n");
    print_arena();

    printf("Total free memory: %d bytes\n", count_free_memory());

    int big = alloc_block(24);

    if (big == -1) {
        printf("Large allocation failed\n");
    } else {
        printf("Large allocation succeeded at %d\n", big);
    }

    return 0;
}
