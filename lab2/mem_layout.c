#include <stdio.h>
#include <stdlib.h>

int global_init = 10;
int global_bss;

void test_stack() {
	int local_array[1000];
	printf("Stack inside function: %p\n", &local_array);
	}
int main() {
	int local_var;
	int *heap_var=malloc(sizeof(int));
	printf("Function (TEXT): %p\n", main);
	printf("Global init (DATA): %p\n", &global_init);
	printf("Global bss (BSS): %p\n", &global_bss);
	printf("Heap (malloc): %p\n", &heap_var);
	printf("Stack (local var): %p\n", &local_var);
	printf("\nCalling function to grow stack...\n");
	test_stack();
	
	free(heap_var);
	return 0;

}
