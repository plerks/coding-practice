/*
url: https://leetcode.cn/problems/sorted-gcd-pair-queries/
参考: https://www.bilibili.com/video/BV15y1iYUE2h/
      https://leetcode.cn/problems/sorted-gcd-pair-queries/solutions/2940415/mei-ju-rong-chi-qian-zhui-he-er-fen-pyth-ujis/
标签: LeetCode第418场周赛, 数论, 最大公约数gcd, 容斥原理, 调和级数, 数对, 序偶
*/

#include <bits/stdc++.h>

using namespace std;

// 这次周赛2题

class Solution3312 {
public:
    /* 参考灵茶山艾府题解，朴素的想法是枚举数对求gcd，但是n == nums.length <= 10^5，肯定会超时。
    所以反转下思路，枚举gcd的值域，求gcd == x的数对有多少个。
    假设x在nums的范围内有c个倍数，则gcd含x为因子的就有 c(c - 1) / 2 个数对，我们还需要排除gcd为
    2x, 3x, ...的数对，于是，我们需要倒序遍历去计算数对数。
    */
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> cnt_gcd(mx + 1); // cnt_gcd[x]表示gcd为x的数对有多少个

        vector<int> cnt_x(mx + 1); // x在nums中的出现次数
        for (int &x : nums) {
            cnt_x[x]++;
        }

        // 这里的两层循环的时间复杂度是 mx / mx + mx / (mx - 1) + ...，是mx * log(mx)级别的，所以不会超时
        for (int x = mx; x >= 1; x--) {
            int c = 0;
            for (int i = x; i <= mx; i += x) {
                c += cnt_x[i];
                // 把2x, 3x, ...的剪掉，这里多减了一次cnt_gcd[x]，但是cnt_gcd[x]是0，不影响
                cnt_gcd[x] -= cnt_gcd[i];
            }
            cnt_gcd[x] += (long long)c * (c - 1) / 2;
        }
        // 现在知道了gcd为x的数对有多少个，queries[i]要求的是在i位置的gcd
        vector<int> prefixSum(mx + 1, 0);
        for (int x = 1; x <= mx; x++) {
            prefixSum[x] = prefixSum[x - 1] + cnt_gcd[x];
        }
        // 求前缀和，然后查找的是第一个前缀和 >= (queries[i] + 1)的x
        int n = queries.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int q = queries[i];
            int left = 1;
            int right = mx;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (prefixSum[mid] < q + 1) left = mid + 1;
                else right = mid - 1;
            }
            ans[i] = left;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3312 solu;
    vector<int> nums = {2,3,4};
    vector<long long> queries = {1,2,2};
    auto a = solu.gcdValues(nums, queries);
    return 0;
}
