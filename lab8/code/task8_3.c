#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 100000

int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int is_sorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }
    return 1;
}

long long get_time_ms(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000LL + t.tv_nsec / 1000000LL;
}

void fill_random(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void fill_sorted(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

void fill_reversed(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void fill_equal(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 1;
    }
}

void run_test(const char *name, void (*fill_func)(int[], int)) {
    int *arr = malloc(SIZE * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    fill_func(arr, SIZE);

    long long start = get_time_ms();
    qsort(arr, SIZE, sizeof(int), compare_ints);
    long long end = get_time_ms();

    printf("Test: %s\n", name);
    printf("Time: %lld ms\n", end - start);
    printf("Sorted correctly: %s\n\n", is_sorted(arr, SIZE) ? "yes" : "no");

    free(arr);
}

int main(void) {
    srand(time(NULL));

    run_test("random array", fill_random);
    run_test("already sorted array", fill_sorted);
    run_test("reversed array", fill_reversed);
    run_test("equal elements array", fill_equal);

    return 0;
}
