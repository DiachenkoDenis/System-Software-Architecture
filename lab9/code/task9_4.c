#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Виконуємо команду whoami:\n");
    system("whoami");
  
    printf("\nВиконуємо команду id:\n");
    system("id");

    return 0;
}
