//
// Created by MeiK on 2019-04-29.
//
#include "stdcheck.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [Answer File] [Output File]\n", argv[0]);
        return 0;
    }
    int ans = StdCheck(argv[1], argv[2]);
    switch (ans) {
        case ACCEPTED:
            printf("Accepted\n");
            break;
        case WRONG_ANSWER:
            printf("Wrong Answer\n");
            break;
    }
    return 0;
}
