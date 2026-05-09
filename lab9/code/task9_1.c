#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_LINE_LENGTH 1024

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *username, *uid_str;
    int uid;
    file = popen("getent passwd", "r");
    if (file == NULL) {
        perror("Не вдалося отримати дані з getent");
        return 1;
    }
    char current_user[MAX_LINE_LENGTH];
    getlogin_r(current_user, sizeof(current_user));
    printf("Звичайні користувачі (окрім вас):\n");
    while (fgets(line, sizeof(line), file)) {

        
        username = strtok(line, ":");
        strtok(NULL, ":");  
        uid_str = strtok(NULL, ":");
        strtok(NULL, ":"); 
        uid = atoi(uid_str);
        if (uid >= 500 && strcmp(username, current_user) != 0) {
            printf("%s (UID: %d)\n", username, uid);
        }
    }

    fclose(file);
    return 0;
}
