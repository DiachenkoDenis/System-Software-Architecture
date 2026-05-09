#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_system_user(const char *username) {
    const char *system_users[] = {"root", "daemon", "bin", "sys", "sync", "games", "man", "lp", "mail", "news", "uucp", "proxy", "www-data", "backup", "list", "irc", "gnats", "nobody", "systemd", NULL};
    for (int i = 0; system_users[i] != NULL; i++) {
        if (strcmp(username, system_users[i]) == 0) {
            return 1;
        }
    }
    return 0; 
}

int main() {
    FILE *file = fopen("/etc/passwd", "r");
    if (file == NULL) {
        perror("Не вдалося відкрити файл /etc/passwd");
        return 1;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *username = strtok(line, ":");
        if (is_system_user(username)) {
            printf("Користувач %s є системним.\n", username);
        } else {
            printf("Користувач %s не є системним.\n", username);
        }
    }
    fclose(file);
    return 0;
}
