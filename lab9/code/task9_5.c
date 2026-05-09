#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("tempfile.txt", "w");
    if (file == NULL) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fprintf(file, "Це тимчасовий файл.\n");
    fclose(file);

    printf("Зміна власника та прав доступу файлу від імені root...\n");
    system("sudo chown root:root tempfile.txt");
    system("sudo chmod 644 tempfile.txt");

    if (access("tempfile.txt", R_OK) == 0) {
        printf("Можна читати файл.\n");
    } else {
        printf("Немає прав на читання файлу.\n");
    }

    if (access("tempfile.txt", W_OK) == 0) {
        printf("Можна записувати у файл.\n");
    } else {
        printf("Немає прав на запис у файл.\n");
    }
    if (remove("tempfile.txt") != 0) {
        perror("Не вдалося видалити файл");
        return 1;
    }
    printf("Файл успішно видалено.\n");
    return 0;
}
