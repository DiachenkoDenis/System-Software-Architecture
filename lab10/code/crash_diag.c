#define _GNU_SOURCE
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <unistd.h>
#include <stdlib.h>

static void wr_all(const char *s, unsigned long n) {
    while (n > 0) {
        ssize_t r = write(STDERR_FILENO, s, n);
        if (r <= 0) return;
        s += r;
        n -= (unsigned long)r;
    }
}

static void crash_handler(int sig, siginfo_t *si, void *ctx) {
    int saved_errno = errno;
    wr("\n=== crash captured ===\n");
    wr("signal: ");
    wr_dec(sig);
    wr("\n");

    if (si != NULL) {
        wr("fault address: ");
        wr_ptr(si->si_addr);
        wr("\n");
    }

    if (ctx != NULL) {
        ucontext_t *uc = (ucontext_t *)ctx;
        greg_t *g = uc->uc_mcontext.gregs;
        wr("RIP: "); wr_hex((uint64_t)g[REG_RIP]); wr("\n");
        wr("RSP: "); wr_hex((uint64_t)g[REG_RSP]); wr("\n");
    }

    errno = saved_errno;
    _exit(128 + sig);
}

static void install_crash_handlers(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = crash_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigaction(SIGSEGV, &sa, NULL);
}

static void crash_here(void) {
    volatile int *p = (int *)0;
    *p = 42;  
}

int main(void) {
    install_crash_handlers();
    wr("About to crash. PID=");
    wr_dec((long)getpid());
    wr("\n");

    crash_here();  
    return 0;
}
