#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec start, end;
    long long milliseconds;
    volatile long long sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long long i = 0; i < 100000000; i++) {
        sum += i;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    milliseconds = (end.tv_sec - start.tv_sec) * 1000LL;
    milliseconds += (end.tv_nsec - start.tv_nsec) / 1000000LL;

    printf("Sum = %lld\n", sum);
    printf("Execution time: %lld ms\n", milliseconds);

    return 0;
}
