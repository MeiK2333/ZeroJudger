#include "parse.h"
#include "run.h"

int main(int argc, char *argv[]) {
    struct config conf;
    struct result res;
    // 解析命令行参数
    parse_args(argc, argv, &conf);
    // 执行
    run(&conf, &res);
    return 0;
}
