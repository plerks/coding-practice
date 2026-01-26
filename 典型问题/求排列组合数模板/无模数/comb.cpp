/*
描述: 题目范围较小不会爆 long long 时，题目并不会求取模意义下的答案，而是直接计算，这时候的预处理组合数求法：
      用 C_{n}^{m} = C_{n - 1}^{m - 1} + C_{n - 1}^{m} 去递推。
      这个递推的方式比先算阶乘再除的方式更好，会直接在组合数的大小范围内计算，而不用先求出更大的可能爆 long long 的阶乘再除。
相关: LeetCode3821. 二进制中恰好K个1的第N小整数
*/
#include <bits/stdc++.h>

using namespace std;

/// ┌──────────────────────────── comb template begin ────────────────────────────┐
constexpr int MX = 50; // 可以取等到的最大范围
long long comb[MX + 1][MX + 1];
auto init = [] {
    // 用 C_{n}^{m} = C_{n - 1}^{m - 1} + C_{n - 1}^{m} 递推预处理组合数
    for (int i = 0; i <= MX; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    return 0;
}();
/// └──────────────────────────── comb template end   ────────────────────────────┘

int main(int argc, char const *argv[]) {
    cout << comb[5][2] << endl;
    return 0;
}