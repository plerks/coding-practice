/*
url: https://leetcode.cn/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/
参考: https://leetcode.cn/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/solutions/3033292/chun-shu-xue-ti-pythonjavacgo-by-endless-mxj7/
相关: 典型问题/求排列组合数模板
标签: LeetCode第430场周赛
*/

// 这次周赛2题，第三题倒是想到了一个能通过的写法，但是时间不够没写出来

#include <bits/stdc++.h>

using namespace std;

const int MX = 100000; // 具体题目需要涉及到的最大范围
const int MOD = (int)(1e9 + 7); // 具体题目要mod的素数

long long fac[MX];
long long inv_fac[MX];

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
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

long long arrange(int n, int m) {
    return fac[n] * inv_fac[n - m] % MOD;
}

class Solution3405 {
public:
    /* 周赛的时候没时间看，周赛结束之后想了下，有想法但是方向不对，n个元素有n-1次相邻相等机会，
    考虑从n-1个隔板中找k个相邻相等位置，这是C(n-1, k)，然后相邻相等就相当于把这些元素合成一个，
    然后考虑这些各自独特的元素，然后从总共用了多少个互不相同的元素构成来考虑，就不知道怎么处理这样的问题:
    1 1 1 2 2，然后右边又是可以出现1的。
    参考灵茶山艾府题解，应该这样考虑，把相邻相等元素合成之后共有 n - k 个互不相同的元素，从左到右看，
    第一个元素有 m 种选法，其余n - k - 1个元素要和左边不相等，有 m - 1 种选法，因此答案为
    C(n - 1, k) * m * (m - 1)^(n - k - 1)
    */
    int countGoodArrays(int n, int m, int k) {
        return comb(n - 1, k) % MOD * m % MOD * fastPow(m - 1, n - k - 1) % MOD;
    }

    /* 这题也能dp做，f[i][j]表示[0,i]有j次相邻相等(不用设具体的值)，
    对f[i][j]，i位置要么和i-1位置相等，则有f[i - 1][j]种情况，
    要么与i-1位置不等，有 (m - 1) * f[i - 1][j]种情况，
    于是f[i][j] = f[i - 1][j] + (m - 1) * f[i - 1][j - 1]，
    最后结果为f[n - 1][k]。
    把 i 和 j都弄上基础的偏移量1以防止越界，i的范围仍然不变，公式
    变成f[i + 1][j + 1] = f[i][j + 1] + (m - 1) * f[i][j]，
    最后结果为f[n][k + 1]。
    不过由于这题1 <= n <= 10^5，0 <= k <= n - 1，dp会超内存
    */
    int countGoodArrays_mle(int n, int m, int k) {
        int MOD = 1e9 + 7;
        vector<vector<long long>> f(n + 1, vector<long long>(k + 2));
        f[0][0] = m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k + 1; j++) {
                f[i + 1][j + 1] = (f[i][j + 1] + (m - 1) * f[i][j] % MOD) % MOD;
            }
        }
        return f[n][k + 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution3405 solu;
    cout << solu.countGoodArrays(3, 2, 1) << endl;
    return 0;
}
