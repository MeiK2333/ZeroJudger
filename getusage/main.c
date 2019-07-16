//
// Created by MeiK on 2019-07-08.
//
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s cmd\n", argv[0]);
        printf("e.g: %s echo Hello\n", argv[0]);
        return 1;
    }

    struct timeval start, end;
    pid_t pid;
    int time_used, cpu_time_used, memory_used, signum;


    gettimeofday(&start, NULL);  // 运行前计时
    if ((pid = fork()) == 0) {
        execvp(argv[1], &argv[1]);
    }

    int status;
    struct rusage ru;
    wait4(pid, &status, 0, &ru);

    gettimeofday(&end, NULL);  // 运行后计时
    time_used = (int) (end.tv_sec * 1000 + end.tv_usec / 1000 - start.tv_sec * 1000 -
                       start.tv_usec / 1000);
    cpu_time_used =
            ru.ru_utime.tv_sec * 1000 + ru.ru_utime.tv_usec / 1000 +
            ru.ru_stime.tv_sec * 1000 + ru.ru_stime.tv_usec / 1000;

    memory_used = ru.ru_maxrss;
    if (WIFEXITED(status)) {
        signum = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        signum = WTERMSIG(status);
    } else if (WIFSTOPPED(status)) {
        signum = WSTOPSIG(status);
    } else {
        signum = 0;
    }


    printf("time used:     %6d ms\n", time_used);
    printf("cpu time used: %6d ms\n", cpu_time_used);
    printf("memory used:   %6d kb\n", memory_used);
    printf("exit code:     %6d\n", signum);
    return 0;
}
