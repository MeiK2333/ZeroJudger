//
// Created by MeiK on 2019-05-08.
//
#include <sys/resource.h>

int main() {
    struct rlimit rl;

    // CPU 时间限制（单位：S）
    rl.rlim_cur = rl.rlim_max = 1;
    setrlimit(RLIMIT_CPU, &rl);

    // 实际时间限制（单位：MS）
    struct itimerval rt;
    long t = 1000;
    rt.it_interval.tv_sec = 0;
    rt.it_interval.tv_usec = 0;
    rt.it_value.tv_sec = t / 1000;
    rt.it_value.tv_usec = (int) (t % 1000) * 1000;
    setitimer(ITIMER_REAL, &rt, (struct itimerval *) 0);

    // 内存限制（单位：KB）
    rl.rlim_cur = rl.rlim_max = 65535 * 1024;
    setrlimit(RLIMIT_DATA, &rl);
    setrlimit(RLIMIT_AS, &rl);

    // 栈限制（单位：KB）
    rl.rlim_cur = rl.rlim_max = 65535 * 1024;
    setrlimit(RLIMIT_STACK, &rl);

    // 最大输出文件大小限制（单位：B）
    rl.rlim_cur = rl.rlim_max = 65535 * 1024;
    setrlimit(RLIMIT_FSIZE, &rl);

    return 0;
}