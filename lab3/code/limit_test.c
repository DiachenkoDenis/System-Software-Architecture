#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
	int count = 0;
	while (1) {
		int fd = open("/dev/null", O_RDONLY);
		if (fd == -1) {
			perror("open failed");
			printf("Total opened files: %d\n", count);
			break;
		}
		count++;
	}
	return 0;
}
