#include <stdio.h>

void deep(int level) {
	int local[256];
	local[0] = level;
	
	printf("Level: %d local addr: %p\n", level, (void*)&local);
	deep(level + 1);
	}
	
	int main() {
	deep(1);
	return 0;
}
