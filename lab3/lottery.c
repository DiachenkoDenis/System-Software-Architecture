#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>


void on_cpu_limit(int sig) {
	(void)sig;
	const char msg[] = "\nCPU time limit reached! Program stopped correctly. \n";
	write(1, msg, sizeof(msg) - 1);
	_exit(0);
}

void pick_unique(int *out, int k, int max) {
	int used[50] = {0};
	int count = 0;
	
	while (count < k) {
		int x = (rand() % max) + 1;
		if (!used[x]) {
			used[x] = 1;
			out[count] = x;
			count++;
		}
	}
}

int main(void) {
	signal(SIGXCPU, on_cpu_limit);
	srand((unsigned)time(NULL));
	
	int a[7], b[6];
	while (1) {
		pick_unique(a, 7, 49);
		pick_unique(b, 6, 36);
		
		printf("7/49: ");
		for (int i = 0; i < 7; i++) printf("%d ", a[i]);
		printf("\n");
		
		printf("6/36: ");
		for (int i = 0; i < 6; i++) printf("%d ", b[i]);
		printf("\n\n");
		
		volatile unsigned long long s = 0;
		for (unsigned long long i = 0; i < 50000000ULL; i++){
			s += 1;
		}
	}

	return 0;
}
