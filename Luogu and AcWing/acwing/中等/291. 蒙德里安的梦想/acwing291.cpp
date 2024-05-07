/*
参考: https://www.bilibili.com/video/BV1cv411b7EG/
标签: 状态压缩dp, 状压dp, 位运算
*/

#include <bits/stdc++.h>

using namespace std;

// 棋盘行数列数<=11
const int N = 12;

const int S = 1 << N; // 状态位数不超过11，因此S足以表示所有状态

long long f[N][S]; // f[i][j]表示第i列的状态，第i列最多11位的状态，那一位为1表示这一列横着放，并向下一列伸出，为0表示这一列竖着放，或者由前一列伸出

bool state[S]; // 用来记录一列对应的位是哪些取值时是："无奇数个连续0"的状态

int main(int argc, char const *argv[]) {
    int n, m;
    while (cin >> n >> m, n > 0 || m > 0) {
        for (int i = 0; i < 1 << n; i++) {
            state[i] = true;
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) { // 第j位是1
                    if (count % 2 == 1) { // 或者用count & 1
                        state[i] == false;
                        break;
                    }
                    else count = 0;
                }
                else count++;
            }
            if (count % 2 == 1) state[i] = false;
        }
        memset(f, 0, sizeof(f));
        f[0][0] = 1; // 第0列，对下一列没伸出的状态有一种摆法
        for (int i = 1; i <= m; i++) { // 枚举列
            for (int j = 0; j < 1 << n; j++) { // 枚举第i列状态
                for (int k = 0; k < 1 << n; k++) { // 枚举第i-1列状态
                    /* 两列状态兼容的条件是，不能出现重叠的1，也不能出现|后有连续奇数个0，关于这里，具体见笔记.md */
                    if ((j & k) == 0 && state[j | k]) {
                        f[i][j] += f[i - 1][k];
                    }
                }
            }
        }
        cout << f[m][0] << endl;
    }
}

// 用时858ms

// 一个用例
// 1 2
// 1 3
// 输出
// 1
// 0