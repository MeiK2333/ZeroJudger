//
// Created by MeiK on 2019-05-08.
//
#include <sys/resource.h>

int main() {
    struct rlimit rl;
    rl.rlim_cur = rl.rlim_max = 1;
    setrlimit(RLIMIT_CPU, &rl);
    while (1) {
    }
}