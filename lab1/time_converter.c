#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int seconds;
	int hours, minutes, secs;
	int is_negative = 0;
	printf("Enter the number of seconds: ");
	scanf("%d", &seconds);
	
	if (seconds < 0) {
		is_negative = 1;
		seconds = abs(seconds);
	}

	hours = seconds/3600;
	minutes = (seconds % 3600) / 60;
	secs = seconds % 60;

	if (is_negative) {
		printf("%d seconds is equivalent to %d hours %d minutes %dseconds in the past./n", -seconds, hours, minutes, secs);
	}
	else {
		printf("%d seconds is equivalent to %d hours %d minutes %d seconds./n", seconds, hours, minutes, secs);
	}
	return 0;
}
