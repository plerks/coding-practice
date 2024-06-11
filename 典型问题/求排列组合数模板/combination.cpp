/*
描述: 计算组合数的模板
参考: https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/solutions/2805408/zu-he-shu-xue-o1-gong-shi-pythonjavacgo-0fbgt/
      https://leetcode.cn/circle/discuss/mDfnkW/
相关: LeetCode3179. K 秒后第 N 个元素的值
标签: 组合数学, 组合数, 费马小定理
*/

#include <bits/stdc++.h>

using namespace std;

// 这是LeetCode3179[灵茶山艾府题解](https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/solutions/2805408/zu-he-shu-xue-o1-gong-shi-pythonjavacgo-0fbgt/)中的求组合数模板
const int MX = 2001; // 具体题目需要涉及到的最大范围
const int MOD = (int)(1e9 + 7); // 具体题目要mod的素数

long long fac[MX];
long long inv_fac[MX]; // 逆元

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

auto init = []() {
    fac[0] = 1;
    for (int i = 1; i < MX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    /* 由费马小定理，a为整数，p为质数，则有a^p ≡ a (mod p)，若a不是p的倍数，则gcd(a, p) = 1，则由同余除法的性质，有a^(p - 1) ≡ 1 (mod p)。
    于是a^(p - 2)是a在模p意义下的逆元。
    */
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        // (1 * 2 * ... * i-1)的逆元(1 * 2 * ... * i-1)^-1 = (i - 1)^-1 * (i - 2)^-1 ... 1^-1，于是(1 * 2 * ... * i-1)的逆元可由(1 * 2 * ... * i)的逆元算出
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    // 模p意义下，通过逆元，把除法变成了乘法
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

int main(int argc, char const *argv[]) {
    cout << comb(5, 3) << endl;
    return 0;
}
