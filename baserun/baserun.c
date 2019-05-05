//
// Created by MeiK on 2019-05-05.
//
#include "baserun.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BaseRun(char *code_file_name, char *input_file_name) {
    char cmd[1024];
    strcpy(cmd, "gcc ");
    strcpy(cmd + 4, code_file_name);
    system(cmd);
    int pid = fork();
    if (pid == 0) {
        FILE *input_file = fopen(input_file_name, "r");
        dup2(fileno(input_file), STDIN_FILENO);
        execl("a.out", (char *) NULL);
    }
}
