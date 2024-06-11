/*
url: https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/description/
参考: https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/solutions/2805408/zu-he-shu-xue-o1-gong-shi-pythonjavacgo-0fbgt/
      https://www.bilibili.com/video/BV1h7421R78s/
      https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/solutions/2805420/shu-xue-by-tsreaper-jvvj/
      https://leetcode.cn/circle/discuss/mDfnkW/
标签: LeetCode第401场周赛, 杨辉三角, 组合数学, 费马小定理, 计算阶乘模板
*/

#include <bits/stdc++.h>

using namespace std;

// 这里是灵茶山艾府题解中计算阶乘的模板
const int MX = 2001;
const int MOD = (int)(1e9 + 7);

long long fac[MX]; // 题目范围1 <= n, k <= 1000
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

long long comb(int n, int k) {
    // 模p意义下，通过逆元，把除法变成了乘法
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD;
}

class Solution3179 {
public:
    // 周赛时的解法，直接模拟。当时感觉应该能推公式，ai = ai旧 + Σ(0, i - 1)ak旧，然后不知道怎么做了，又是第二题，就直接模拟了
    int valueAfterKSeconds(int n, int k) {
        vector<int> nums(n, 1);
        vector<int> prefixSum(n, 0);
        int MOD = (int)(1e9 + 7);
        prefixSum[0] = 1;
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + 1;
        }
        vector<int> oldPre(n, 0);
        for (int i = 0; i < k; i++) {
            oldPre = prefixSum;
            for (int j = 1; j < n; j++) {
                nums[j] = (nums[j] + oldPre[j - 1]) % MOD;
                prefixSum[j] = (prefixSum[j] + prefixSum[j - 1]) % MOD;
            }
        }
        return nums[n - 1];
    }

    /* 参考题解的做法，这里是得有行列号两个变量，f(i, j) = f(i - 1, j) + f(i, j - 1)，
    这是组合数C(n, m) = C(n, m - 1) + C(n - 1, m)的关系，也代表一个数是上面加左侧的元素之和，斜着看数组的变化过程也能看出是杨辉三角。
    于是，答案是C(n - 1 + k, k)
    */
    int valueAfterKSeconds_implementation2(int n, int k) {
        return comb(n - 1 + k, k);
    }
};

int main(int argc, char const *argv[]) {
    Solution3179 solu;
    cout << solu.valueAfterKSeconds_implementation2(4, 5) << endl;
    return 0;
}
