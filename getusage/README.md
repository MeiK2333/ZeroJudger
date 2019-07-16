```bash
$ gcc main.c
$ ./a.out echo hello
hello
time used:          2 ms
cpu time used:      0 ms
memory used:   684032 kb  # memory is not valid on macOS
exit code:          0
$ ./a.out sleep 1
time used:       1006 ms
cpu time used:      0 ms
memory used:   684032 kb
exit code:          0
$ gcc return1.c -o return1.out
$ ./a.out ./return1.out
time used:          3 ms
cpu time used:      0 ms
memory used:   778240 kb
exit code:          1
```