#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static void on_sigxfsz(int sig) {
    (void)sig;
    const char msg[] = "File size limit exceeded\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    const char *src = argv[1];
    const char *dst = argv[2];

    signal(SIGXFSZ, on_sigxfsz);

    FILE *in = fopen(src, "rb");
    if (!in) {
        printf("Cannot open file %s for reading\n", src);
        return 1;
    }

    FILE *out = fopen(dst, "wb");
    if (!out) {
        printf("Cannot open file %s for writing\n", dst);
        fclose(in);
        return 1;
    }

    char buf[4096];
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            // часто тут буде EFBIG, якщо вичерпано file size limit
            printf("File size limit exceeded\n");
            fclose(in);
            fclose(out);
            return 1;
        }
    }

    if (ferror(in)) {
        // якщо була помилка читання
        printf("Cannot open file %s for reading\n", src);
        fclose(in);
        fclose(out);
        return 1;
    }

    fclose(in);
    fclose(out);
    return 0;
}
