/*
url: https://leetcode.cn/problems/find-the-count-of-monotonic-pairs-ii/
参考: https://leetcode.cn/problems/find-the-count-of-monotonic-pairs-ii/solutions/2876190/qian-zhui-he-you-hua-dppythonjavacgo-by-3biek/
      https://www.bilibili.com/video/BV1Cf421v7Ky/
相关: LeetCode3519. 统计逐位非递减的整数, LeetCode3906. 统计网格路径中好整数的数目
*/
#include <bits/stdc++.h>

using namespace std;

const int MX = 3001; // MX = 具体题目需要涉及到的最大范围 + 1，阶乘最多算到(MX - 1)!
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
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        // (1 * 2 * ... * i-1)的逆元(1 * 2 * ... * i-1)^-1 = (i - 1)^-1 * (i - 2)^-1 ... 1^-1，于是(1 * 2 * ... * i-1)的逆元可由(1 * 2 * ... * i)的逆元算出
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    if (m > n) return 0;
    // 模p意义下，通过逆元，把除法变成了乘法
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

class Solution3251 {
public:
    /* 灵茶题解解法二，组合数学，
    先考虑 nums[i] 全为一个数的情况，那么只要 arr1 是单增，arr2 就一定会是单减。
    要单增，相当于从 (0, 0) 往右往上走到 (n, nums[n - 1] = m) 位置，答案为 C_{n+m}^{n}。
    泛化到 nums[i] 不全相等的情况，设 arr1[i - 1] = x，arr1[i] = y，则必须满足：
    x <= y && nums[i - 1] - x >= nums[i] - y，即
    y >= max(x, nums[i] - nums[i - 1] + x)
    如果 nums[i] - nums[i - 1] <= 0，和之前没什么不同，
    如果 nums[i] - nums[i - 1] > 0，这意味着 y >= nums[i] - nums[i - 1] + x，这一步要往上至少跳 nums[i] - nums[i - 1] 步。
    记 d_i = max(0, nums[i] - nums[i - 1])，则答案为
    C_{n + m - d1 - d2 - ... d_{n - 1}}^{n}
    */
    int countOfPairs(vector<int>& nums) {
        int n = nums.size(), m = nums.back();
        for (int i = 1; i < n; i++) {
            m -= max(0, nums[i] - nums[i - 1]);
            if (m < 0) return 0;
        }
        return comb(n + m, m);
    }
};

int main(int argc, char const *argv[]) {
    Solution3251 solu;
    cout << solu.countOfPairs(*new vector<int>{5,5,5,5}) << endl;
    return 0;
}