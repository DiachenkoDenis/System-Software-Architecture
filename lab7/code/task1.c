#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *input;
    FILE *output;
    char buffer[256];

    input = popen("rwho", "r");
    if (input == NULL) {
        perror("popen rwho");
        return 1;
    }

    output = popen("more", "w");
    if (output == NULL) {
        perror("popen more");
        pclose(input);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        fputs(buffer, output);
    }

    pclose(input);
    pclose(output);

    return 0;
}
