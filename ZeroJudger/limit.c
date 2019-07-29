#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "limit.h"

void set_limit(const struct config *conf) {
    struct rlimit rl;

    /* set cpu time limit (seconds) */
    if (conf->cpu_time_limit != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t)((conf->cpu_time_limit + 999) / 1000);
        setrlimit(RLIMIT_CPU, &rl);
    }

    /* set real time limit */
    if (conf->real_time_limit != UNLIMITED) {
        struct itimerval rt;
        long t = conf->real_time_limit;
        rt.it_interval.tv_sec = 0;
        rt.it_interval.tv_usec = 0;
        rt.it_value.tv_sec = t / 1000;
        rt.it_value.tv_usec = (int) (t % 1000) * 1000;
        setitimer(ITIMER_REAL, &rt, (struct itimerval *) 0);
    }

    /* set memory limit */
    if (conf->memory_limit != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t) conf->memory_limit;
        setrlimit(RLIMIT_AS, &rl);
    }

    /* redirect in_file to stdin */
    if (conf->input_file_name != NULL) {
        FILE *in_file;
        in_file = fopen(conf->input_file_name, "r");
        dup2(fileno(in_file), STDIN_FILENO);
    }

    /* redirect stdout to out_file */
    if (conf->output_file_name != NULL) {
        FILE *out_file;
        out_file = fopen(conf->output_file_name, "w");
        dup2(fileno(out_file), STDOUT_FILENO);
    }
}