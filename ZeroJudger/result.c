#include <stdio.h>

#include "result.h"

const char *check_result(char *answer_file_name, char *output_file_name) {
    FILE *answer_file, *output_file;
    answer_file = fopen(answer_file_name, "r");
    output_file = fopen(output_file_name, "r");

    int ans, out;
    const char * res;
    res = "Accepted";

    while (1) {
        ans = fgetc(answer_file);
        out = fgetc(output_file);
        if (ans == EOF || out == EOF) {  // 文件读取结束时，值为 EOF
            if (ans != out) {  // 如果两个文件没有同时结束，代表两个文件内容不同
                res = "Wrong Answer";
            }
            goto END;
        }
        if (ans != out) {
            res = "Wrong Answer";
            goto END;
        }
    }

    END:
    fclose(answer_file);
    fclose(output_file);
    return res;
}
