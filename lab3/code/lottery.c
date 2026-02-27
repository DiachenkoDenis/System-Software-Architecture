#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <unistd.h>


void cpu_limit_handler(int sig) {
    (void)sig;
    printf("\nCPU time limit reached! Program stopped.\n");
    fflush(stdout);
    exit(0);
}


void generate_numbers(int arr[], int k, int max) {
    int used[50] = {0};
    int count = 0;

    while (count < k) {
        int num = rand() % max + 1;   // число 1..max
        if (!used[num]) {
            used[num] = 1;
            arr[count] = num;
            count++;
        }
    }
}

int main() {
    struct rlimit limit;
    limit.rlim_cur = 1;  // soft limit
    limit.rlim_max = 2;  // hard limit
    setrlimit(RLIMIT_CPU, &limit);

    signal(SIGXCPU, cpu_limit_handler);

    srand(time(NULL));

    int a[7], b[6];

    while (1) {
        generate_numbers(a, 7, 49);
        generate_numbers(b, 6, 36);

        printf("7/49: ");
        for (int i = 0; i < 7; i++)
            printf("%d ", a[i]);
        printf("\n");

        printf("6/36: ");
        for (int i = 0; i < 6; i++)
            printf("%d ", b[i]);
        printf("\n\n");

        volatile unsigned long long x = 0;
        for (unsigned long long i = 0; i < 20000000ULL; i++)
            x += i;
    }

    return 0;
}
