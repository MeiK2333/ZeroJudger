#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "run.h"

void run(struct config *conf, struct result *res) {
    int status;
    struct rusage ru;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork error!\n");
        exit(1);
    } else if (pid == 0) {  // child
        execvp(conf->args[0], conf->args);
        exit(-1);
    } else {  // parent
        wait4(pid, &status, WSTOPPED, &ru);

        gettimeofday(&end, NULL);
        res->real_time_used = (end.tv_sec * 1000 + end.tv_usec / 1000) -
                              (start.tv_sec * 1000 + start.tv_usec / 1000);
        res->cpu_time_used = ru.ru_utime.tv_sec * 1000
                             + ru.ru_utime.tv_usec / 1000
                             + ru.ru_stime.tv_sec * 1000
                             + ru.ru_stime.tv_usec / 1000;
        printf("cpu time used:  %5d ms\n", res->cpu_time_used);
        printf("real time used: %5d ms\n", res->real_time_used);
    }
}