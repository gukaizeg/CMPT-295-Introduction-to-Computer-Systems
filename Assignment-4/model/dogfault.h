#ifndef _DOGFAULT_H_
#define _DOGFAULT_H_

#include <execinfo.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#define DOGFAULT_MAX_BACKTRACE 2048
#define DOGFAULT_ERROR "dogfault error: "
#define DOGFAULT_HANDLER_DOGGO_FORMAT \
"\n\
                 __\n\
 ,             ,\" e`--o  *bork*\n\
((            (  | __,'   Doin me a segfault fren: %p\n\
 \\\\~---------' \\_;/       Good boye bamboozled!\n\
 (               /       *bork*\n\
 /) .________.  )\n\
(( (        (( (\n\
 ``-'        ``-'\n\
"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static void dogfault_sigaction_handler(int sig, siginfo_t* si, void* arg)
{
    fprintf(stderr, DOGFAULT_HANDLER_DOGGO_FORMAT, si->si_addr);

    void* backtrace_buff[DOGFAULT_MAX_BACKTRACE];
    int nframes = backtrace(backtrace_buff, DOGFAULT_MAX_BACKTRACE);
    char** symbols = backtrace_symbols(backtrace_buff, nframes);
    if (!symbols)
    {
        fprintf(stderr, DOGFAULT_ERROR"failed to aquire backtrace symbols\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nframes; ++i)
    {
        fprintf(stderr, "%s\n", symbols[i]);
    }

    exit(EXIT_FAILURE);
}
#pragma GCC diagnostic pop

__attribute__((constructor))
static void dogfault_init(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = dogfault_sigaction_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
}

#endif // !_DOGFAULT_H_
