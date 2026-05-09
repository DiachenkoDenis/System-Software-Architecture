#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("testfile.txt", "w");
    if (file == NULL) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fprintf(file, "Це тестовий файл.\n");
    fclose(file);

    int result = system("sudo cp testfile.txt ~");
    if (result == -1) {
        perror("Не вдалося копіювати файл від імені root");
        return 1;
    }
    printf("Файл успішно скопійовано в домашній каталог користувача.\n");
    result = system("echo 'Зміни у файлі' >> ~/testfile.txt");
    if (result == -1) {
        perror("Не вдалося змінити файл");
        return 1;
    }
    printf("Файл змінено.\n");
    result = system("rm ~/testfile.txt");
    if (result == -1) {
        perror("Не вдалося видалити файл");
        return 1;
    }
    printf("Файл видалено.\n");
    return 0;
}
