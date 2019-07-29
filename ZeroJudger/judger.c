#include <stdio.h>

#include "parse.h"
#include "run.h"

void print_result(struct result *);

int main(int argc, char *argv[]) {
    struct config conf;
    struct result res;

    init_config(&conf);
    // 解析命令行参数
    parse_args(argc, argv, &conf);
    // 执行
    run(&conf, &res);

    // 输出结果
    print_result(&res);
    return 0;
}

void print_result(struct result *res) {
    printf("cpu time used:  %6d\n", res->cpu_time_used);
    printf("real time used: %6d\n", res->real_time_used);
    printf("memory used:    %6d\n", res->memory_used);
    printf("exit signum:    %6d\n", res->signum);
    printf("result: %14s\n", res->result);
}