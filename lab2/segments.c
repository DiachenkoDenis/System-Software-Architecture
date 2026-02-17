#include <stdio.h>
#define MODE 1

#if MODE == 2
int g_arr[1000];
#elif MODE == 3
int g_arr[1000] = {1};
#endif

int main (void) {
#if MODE == 4
	int local1[1000];
	int local2[1000] = {1};
	local1[0]=5;
	printf("Hello, world! %d\n", local2[0] + local1[0]);
	#else
		printf("Hello, world!\n");
	#endif
		return 0;
}
