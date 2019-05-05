//
// Created by MeiK on 2019-05-05.
//
#include "baserun.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [Code File] [Input File]\n", argv[0]);
        return 0;
    }
    BaseRun(argv[1], argv[2]);
    return 0;
}