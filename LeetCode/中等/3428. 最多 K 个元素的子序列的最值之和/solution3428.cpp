/*
url: https://leetcode.cn/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/
参考: https://www.bilibili.com/video/BV17RwBeqErJ/
相关: LeetCode3430. 最多 K 个元素的子数组的最值之和
标签: LeetCode第433场周赛, 贡献法, 子序列, 子序列可排序, 组合数学
*/

#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 1; // MX = 具体题目需要涉及到的最大范围 + 1，阶乘最多算到(MX - 1)!
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
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    if (m > n) return 0;
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

class Solution3428 {
public:
    /* 参考灵茶题解，贡献法。
    周赛的时候想过考虑每个nums[i]为最小值，然后看i左右有多少个大于nums[i]的元素，但是不知道这样怎么处理有相同元素时，
    产生重复计数的问题。
    首先，虽然子序列有顺序，但是这题求序列中的最大最小对于子序列的顺序是无关的，因此可以对子序列排序。
    假设 1 2 3 4 5，以3为最小值，子序列最长为k，则只能从右边选 0、1、2、 ... 、k-1 个数(注意，若3左边还有3，是不考虑的，这样就不重不漏)，
    也就是说，枚举的方式是以每个数为左边界。
    则以 nums[i] 为最小值的贡献为 m * (C(n-1-i, 0) + C(n-1-i, 1) + ... + C(n-1-i, min(k-1, n-1-i)))
    以以 nums[i] 为最大值的贡献为 M * (C(i, 0) + C(i, 1) + ... + C(i, min(k-1, i)))
    对于求最大值 M 的贡献，以 nums[i] 为最小值和以 nums[n-1-i]为最大值，情况种数是相同的(左右可选长度相同)，所以可以合并起来。
    即: (M + m) * (C(i, 0) + C(i, 1) + ... + C(i, min(k-1, i)))
    这样时间复杂度为O(nk)，还能优化

    对于和式 ∑(j=0, min(k-1,i)) C(i, j) 的计算，可以递推，

    从考虑m=3的贡献 到 考虑m=4的贡献，从i个数中选至多k-1个数的种数，到从i+1个数中选至多k-1个数的种数，要么不选nums[i+1]，合法，
    要么选nums[i+1]，这时有部分是不合法的，不合法的部分是前面选了k-1个数的情况，
    所以，从i+1个数中选至多k-1个数的种数：
        (i+1, <=k-1) = (i, <=k-1) + (i, <=k-1) - (i, k-1)
    */
    int minMaxSums(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long count = 1; // 递推的和式
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + (nums[i] + nums[n - 1 - i]) * count % MOD) % MOD;
            count = ((count << 1) - comb(i, k - 1) + MOD) % MOD; // 注意这里减法要加上MOD，不然出负数后负数%MOD的计算逻辑不是正数
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3428 solu;
    cout << solu.minMaxSums(*new vector<int>{1,2,3}, 2) << endl;
    return 0;
}