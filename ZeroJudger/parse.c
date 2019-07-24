#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "run.h"

static const char *opt_string = "i:o:a:t:T:m:h?";


void display_usage() {
    const char *usage = ""
                        "Usage: ./judger COMMAND\n"
                        "E.g: ./Judger -i input.txt -o output.txt -a answer.txt -t 1000 -T 1000 -m 65535 echo Hello World\n"
                        "\n"
                        "Options:\n"
                        "  -i  string   输入文件\n"
                        "  -o  string   程序输出文件\n"
                        "  -a  string   答案文件\n"
                        "  -t  integer  CPU 时间限制 (ms)\n"
                        "  -T  integer  实际时间限制 (ms)\n"
                        "  -m  integer  内存占用限制 (kb)\n"
                        "\n";
    fprintf(stderr, "%s", usage);
    exit(0);
}

void parse_args(int argc, char *argv[], struct config *conf) {
    if (argc < 2) {
        display_usage();
    }
    int opt;
    char *str_to;

    while ((opt = getopt(argc, argv, opt_string)) != -1) {
        switch (opt) {
            case 'h':
                display_usage();
                break;
            case 'i':
                conf->input_file_name = optarg;
                break;
            case 'o':
                conf->output_file_name = optarg;
                break;
            case 'a':
                conf->answer_file_name = optarg;
                break;
            case 't':
                conf->cpu_time_limit = strtol(optarg, &str_to, 10);
                break;
            case 'T':
                conf->real_time_limit = strtol(optarg, &str_to, 10);
                break;
            case 'm':
                conf->memory_limit = strtol(optarg, &str_to, 10);
                break;
            default:
                display_usage();
                break;
        }
    }
    // 将剩余未匹配的参数都传递给 conf
    conf->args = argv + optind;
}