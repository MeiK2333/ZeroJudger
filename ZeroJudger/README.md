## 使用

### 直接使用

直接调用 `judger`，可以运行指定程序并获取其资源占用（在 macOS 下内存无法获取）。

```
$ make
$ ./judger echo Hello World
Hello World
cpu time used:       0
real time used:      2
memory used:    684032
exit signum:         0
result:     Not Judged
```

### 题目评测

#### Accepted

通过最基本的 `A + B Problem` 来验证 `judger` 程序。

```
$ echo '1 2' > input.txt
$ echo '3' > answer.txt
$ echo '#include <stdio.h>
  int main() {
  int a, b;
  scanf("%d %d", &a, &b);
  printf("%d\\n", a + b);
  return 0;
}' > main.c
$ ./judger -i input.txt -o output.txt -a answer.txt ./a.out
cpu time used:       1
real time used:      3
memory used:    806912
exit signum:         0
result:       Accepted
```

#### Wrong Answer

使用同一个程序来验证 `Wrong Answer`。

```
$ echo '4' > answer.txt
$ ./judger -i input.txt -o output.txt -a answer.txt ./a.out
cpu time used:       2
real time used:      4
memory used:    806912
exit signum:         0
result:   Wrong Answer
$ cat output.txt
3
```

### 资源限制

死循环占用 CPU 的程序将在指定时间后被中止。

```
$ echo 'int main() { while (1) {}}' > main.c
$ gcc main.c
$ ./judger -t 1000 ./a.out
cpu time used:    1001
real time used:   1003
memory used:    774144
exit signum:        24
result:     Not Judged
```

`sleep 10000` 将在指定时间后被中止。

```
$ ./judger -T 1000 sleep 10000
cpu time used:       1
real time used:   1002
memory used:    679936
exit signum:        14
result:     Not Judged
```
