#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define PAGE_SIZE 20

int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE];
    int line_count = 0;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("fopen failed");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        line_count++;

        if (line_count % PAGE_SIZE == 0) {
            printf("\nPress Enter to continue:");
            getchar();
        }
    }

    fclose(file);

    return 0;
}
