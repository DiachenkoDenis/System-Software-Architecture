#include <stdio.h>
#include <time.h>
#include <limits.h>

int main(void) {
	printf("sizeof(time_t) = %zu bytes\n", sizeof(time_t));
	time_t t_end;

	if (sizeof(time_t) == 4) {
		t_end=(time_t)INT_MAX;
		printf("Assuming 32-bit time_t.\n");
	}
		else {
		t_end = (time_t)LLONG_MAX;
	}
	printf("End value = %lld\n", (long long)t_end);
	char *s = ctime(&t_end);
	if (s) {
		printf("End date = %s", s);
	}
	else {
		printf("ctime() cannot convert this value on this system.\n");
	}
	return 0;
}
