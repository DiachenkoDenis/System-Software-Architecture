#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>  

int main() {
    const char *directories[] = {
        "~/",   
        "/usr/bin",  
        "/etc"     
    };

    for (int i = 0; i < 3; i++) {
        printf("\nПеревірка каталогу: %s\n", directories[i]);
        char command[256];
        snprintf(command, sizeof(command), "ls -l %s", directories[i]);
        system(command);
        printf("\nПеревірка доступу до файлів у каталозі:\n");
        FILE *fp = popen("ls %s", "r");
        if (fp == NULL) {
            perror("Не вдалося відкрити потік");
            return 1;
        }
        char file[256];
        while (fgets(file, sizeof(file), fp) != NULL) {
            file[strcspn(file, "\n")] = 0; 
            printf("Перевіряємо файл: %s\n", file);  
            if (access(file, R_OK) == 0) {
                printf("Можна читати файл %s.\n", file);
            } else {
                printf("Немає прав на читання файлу %s.\n", file);
            }
            if (access(file, W_OK) == 0) {
                printf("Можна записувати у файл %s.\n", file);
            } else {
                printf("Немає прав на запис у файл %s.\n", file);
            }
            if (access(file, X_OK) == 0) {
                printf("Можна виконати файл %s.\n", file);
            } else {
                printf("Немає прав на виконання файлу %s.\n", file);
            }
        }
        fclose(fp);
    }
    return 0;
}
