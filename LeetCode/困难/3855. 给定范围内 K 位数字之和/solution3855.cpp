/*
url: https://leetcode.cn/problems/sum-of-k-digit-numbers-in-a-range/
标签: LeetCode第177场双周赛
*/

// 这次双周赛两题

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

class Solution3855 {
public:
    /* 参考灵茶题解，贡献法，
    k 位的数字，每位 [l, r] 之间(0 <= l <= r <= 9)，允许出现前导零，那么第 i 位是 x (x = l, ... , r)有多少贡献？
    10^i * (r - l + 1)^(k - 1) * (l + ... + r) ，再对 i 求和（i 从 0 到 k - 1）
    (l + r) * (r - l + 1) / 2 * (r - l + 1)^(k - 1) * (10^k - 1) / 9
    其中 9 要算逆元

    这题双周赛时没看，不过看起来知道是贡献法之后还是比较好分析的
    */
    int sumOfNumbers(int l, int r, int k) {
        const int inv_9 = fastPow(9, MOD - 2);
        return (l + r) * 1LL * (r - l + 1) / 2LL * (fastPow(10, k) - 1) % MOD * inv_9 % MOD * fastPow(r - l + 1, k - 1) % MOD;
    }
};

int main(int argc, char const *argv[]) {
    Solution3855 solu;
    cout << solu.sumOfNumbers(1, 2, 2) << endl;
    return 0;
}