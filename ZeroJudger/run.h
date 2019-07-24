#ifndef ZEROJUDGER_RUN_H
#define ZEROJUDGER_RUN_H

#define UNLIMITED -1
#define ARGS_MAX_NUMBER 256

struct config {
    int cpu_time_limit;
    int real_time_limit;
    int memory_limit;

    char **args;
    char *input_file_name;
    char *output_file_name;
    char *answer_file_name;
};

struct result {
    int result;
    int cpu_time_used;
    int real_time_used;
    int memory_used;
    int signum;
    int exit_code;
};

void run(struct config *, struct result *);

#endif //ZEROJUDGER_RUN_H
