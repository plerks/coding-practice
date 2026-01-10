// 极简化的快读快写板子，功能不充分，只有读int和写int，不过大部分情形就是这两种，对大部分情况也够用了

/// ┌──────────────────────────── io template begin ────────────────────────────┐
#include <stdio.h>
int rd() { /// 读入 int，若也要读入 long long 则把函数改成 rd(T& x) 的形式
    int k = 0, f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return f ? k : -k;
}
void wr(int x) { /// 输出 int
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}
/// └──────────────────────────── io template end   ────────────────────────────┘

int main(int argc, char const *argv[]) {
    int x = rd();
    wr(x);
    return 0;
}