/*
描述: 求 C(n, k) mod m 的值，这里m不一定为素数，所以不能用费马小定理那样写
参考: https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/3086169/mo-shu-wei-he-shu-shi-de-zu-he-shu-by-en-8x7t/
      https://oi-wiki.org/math/number-theory/lucas/
      https://oi-wiki.org/math/number-theory/crt/
相关: LeetCode3463. 判断操作后字符串中的数字是否相等 II, 洛谷P4720 【模板】扩展卢卡斯定理/exLucas
*/

// `LeetCode3463. 判断操作后字符串中的数字是否相等 II`灵茶题解还有个把n!和m的公共素因子提取出来的做法

#include <bits/stdc++.h>

using namespace std;

// 这里仅以模数为10来举例，且这里每次计算comb时是重新算了，没有记忆化打表，时间复杂度O(nlogn)，lucas()的时间复杂度为O(log_p {n})
const int MX = 5;
int c[MX][MX];

// 预处理组合数
auto init = []() {
    for (int i = 0; i < MX; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    return 0;
}();

// 计算C(n, m) % p，要求p为质数
int lucas(int n, int m, int p) {
    if (m == 0) return 1;
    return c[n % p][m % p] * lucas(n / p, m / p, p) % p;
}

// 求C(n, m) % 10
int comb(int n, int m) {
    return 5 * lucas(n, m, 2) + 6 * lucas(n, m, 5);
}

int main(int argc, char const *argv[]) {
    cout << comb(6, 3) << endl;
    cout << comb(7, 4) << endl;
    return 0;
}
