#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *pathname, int flags, ...) {
    static int (*real_open)(const char *pathname, int flags, ...) = NULL;

    if (!real_open) {
        real_open = dlsym(RTLD_NEXT, "open");
    }

    printf("[LD_PRELOAD] open called: pathname=%s, flags=%d\n", pathname, flags);

    if (flags & O_CREAT) {
        va_list args;
        va_start(args, flags);
        mode_t mode = va_arg(args, mode_t);
        va_end(args);

        printf("[LD_PRELOAD] mode=%o\n", mode);
        return real_open(pathname, flags, mode);
    }

    return real_open(pathname, flags);
}
