#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "run.h"
#include "limit.h"
#include "result.h"

void init_config(struct config *conf) {
    conf->answer_file_name = NULL;
    conf->output_file_name = NULL;
    conf->input_file_name = NULL;
    conf->cpu_time_limit = UNLIMITED;
    conf->real_time_limit = UNLIMITED;
    conf->memory_limit = UNLIMITED;
}

void run(struct config *conf, struct result *res) {
    int status;
    struct rusage ru;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid == 0) {  // child
        // 设置资源限制和流
        set_limit(conf);

        execvp(conf->args[0], conf->args);
        exit(-1);
    } else {  // parent
        // 等待子进程执行完成
        wait4(pid, &status, WSTOPPED, &ru);

        gettimeofday(&end, NULL);
        res->real_time_used = (end.tv_sec * 1000 + end.tv_usec / 1000) -
                              (start.tv_sec * 1000 + start.tv_usec / 1000);
        res->cpu_time_used = ru.ru_utime.tv_sec * 1000
                             + ru.ru_utime.tv_usec / 1000
                             + ru.ru_stime.tv_sec * 1000
                             + ru.ru_stime.tv_usec / 1000;
        if (WIFEXITED(status)) {
            res->signum = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            res->signum = WTERMSIG(status);
        } else if (WIFSTOPPED(status)) {
            res->signum = WSTOPSIG(status);
        }
        res->memory_used = ru.ru_maxrss;
        if (conf->output_file_name != NULL && conf->answer_file_name != NULL) {
            res->result = check_result(conf->answer_file_name, conf->output_file_name);
        } else {
            res->result = "Not Judged";
        }
    }
}