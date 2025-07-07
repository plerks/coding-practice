/*
url: https://leetcode.cn/problems/concatenation-of-consecutive-binary-numbers/
参考: https://leetcode.cn/problems/concatenation-of-consecutive-binary-numbers/solutions/510956/lian-jie-lian-xu-er-jin-zhi-shu-zi-by-ze-t40j/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1680 {
public:
    int concatenatedBinary(int n) {
        long long ans = 0;
        constexpr long long MOD = 1e9 + 7;
        for (int i = 1; i <= n; i++) {
            ans = ((ans << (__lg(i) + 1)) % MOD + i) % MOD;
        }
        return ans;
    }

    /* 参考zerotrac题解，按[1, n]中的数的位的长度来分组，同一组可以用公式快速求和。
    例如 [1, 6] 可以分为：
    110 101 100
    11 10
    1
    按组求，比如第一轮会去求 [100, 101, 110] 的拼接结果100_101_110，
    [a - t, a] 的数(二进制长度都为k)，拼接结果为：(a - t) * 2^{tk} + (a - t + 1) * 2^{(t - 1)k} + ... + a
    这是个差比数列，求和可得 S = { (a - t) * 2^{(t + 1)k} + 2^k * (1 - 2^{tk}) / (1 - 2^k) - a } / (2^k - 1)
    如果后面有更高的组，这个 S 也要移位，所以，我们从高位到底位遍历，并记录后缀总长度。

    时间复杂度 O((logn)^2)
    */
    int concatenatedBinary_implementation2(int n) {
        constexpr long long MOD = 1e9 + 7;
        int suf_len = 0; // 后面的数积累的二进制总长
        long long ans = 0;
        while (n > 0) {
            int l = 1 << __lg(n); // l是个2^i形式的数，是此轮的组的下界。此轮的组为 [l, n]

            int k = __lg(l) + 1; // 此组的二进制长度
            
            // 计算 [l, n] 的 S，[n - (n - l), n]
            long long a = n, t = n - l;
            // 一部分一部分地算，以下是计算S的过程
            long long p1 = (a - t) * fast_pow(2, (t + 1) * k) % MOD;
            long long p2 = fast_pow(2, k) * (fast_pow(2, t * k) - 1) % MOD;
            long long p3 = fast_pow(2, k) - 1;
            long long p3_inv = fast_pow(p3, MOD - 2); // 逆元
            long long S = (p1 + p2 * p3_inv % MOD - a + MOD) * p3_inv % MOD;

            S = S * fast_pow(2, suf_len) % MOD;

            ans = (ans + S) % MOD;
            suf_len += (t + 1) * k; // 后缀多了 t + 1 个二进制长为 k 的数，加到 suf_len 里
            n = l - 1;
        }
        return ans;
    }

    long long fast_pow(long long a, long long b) {
        constexpr long long MOD = 1e9 + 7;
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution1680 solu;
    cout << solu.concatenatedBinary(3) << endl;
    cout << solu.concatenatedBinary(12) << endl;

    cout << solu.concatenatedBinary_implementation2(3) << endl;
    cout << solu.concatenatedBinary_implementation2(12) << endl;
    return 0;
}