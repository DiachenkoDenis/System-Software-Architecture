#include <stdio.h>
#include <stdlib.h>

int main() {
    int result = system("sudo cat /etc/shadow");

  
    if (result == -1) {
        perror("Помилка при виконанні команди");
        return 1;
    }

    return 0;
  
}
