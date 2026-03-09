#include <stdio.h>

void recurse(int depth) {
    char buffer[1024]; 
    buffer[0] = depth % 256;

    printf("Depth: %d\n", depth);
    recurse(depth + 1);
}

int main() {
    recurse(1);
    return 0;
}
