#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void handler(int sig) {
	printf("\nFile size limit reached!\n");
	exit(0);
}

int main(int argc, char *argv[]) {
	const char *filename = "results.txt";
	if (argc >= 2) filename = argv[1];
	
	signal(SIGXFSZ, handler);
	FILE *f = fopen(filename, "w");
	if (!f) {
		printf("Cannot open file\n");
		return 1;
	}
	
	srand(time(NULL));
	int count = 0;
	long long i = 0;
	while (1) {
		int dice = (rand() % 6) + 1;
		count++;
		
		fprintf(f, "%d: %d/n", count, dice);
		fflush(f);
	}
	fclose(f);
	return 0;
}
