/*
url: https://leetcode.cn/problems/find-the-count-of-monotonic-pairs-ii/
参考: https://leetcode.cn/problems/find-the-count-of-monotonic-pairs-ii/solutions/2876190/qian-zhui-he-you-hua-dppythonjavacgo-by-3biek/
      https://www.bilibili.com/video/BV1Cf421v7Ky/
相关: LeetCode3519. 统计逐位非递减的整数
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3251 {
public:
    /* 视频里的记忆化搜索解法，时间复杂度 O(n * m * m) 过不了。
    从右边开始填，dfs(i, j) 表示 arr1[i] 填 j 时，整体的合法方案数
    arr1[i] 填 j ，则 arr2[i] = nums[i] - j ，于是有：
        0 <= arr1[i - 1] <= nums[i - 1]
        0 <= arr1[i - 1] <= j
        0 <= nums[i - 1] - arr1[i - 1] >= nums[i] - j
    于是得到: 0 <= arr1[i - 1] <= min(nums[i - 1], j, nums[i - 1] - nums[i] + j)
    */
    int countOfPairs_tle(vector<int>& nums) {
        const long long mod = 1e9 + 7;
        int n = nums.size();
        array<long long, 1001> arr;
        fill(arr.begin(), arr.end(), -1);
        vector<array<long long, 1001>> memo(n, arr);
        auto dfs = [&](auto& dfs, int i, int j) -> long long {
            // 进到此处时 i 已经填了，并且是合法的
            if (i == 0) return 1;
            if (memo[i][j] >= 0) return memo[i][j];
            // 枚举 i - 1 的填法
            long long res = 0;
            int mx = min({nums[i - 1], j, nums[i - 1] - nums[i] + j});
            for (int k = 0; k <= mx; k++) {
                res += dfs(dfs, i - 1, k);
                res %= mod;
            }
            memo[i][j] = res;
            return res;
        };
        long long ans = 0;
        for (int k = 0; k <= nums[n - 1]; k++) {
            ans += dfs(dfs, n - 1, k);
            ans %= mod;
        }
        return ans;
    }

    // 灵茶题解解法一，改成 dp，再用前缀和优化
    int countOfPairs(vector<int>& nums) {
        const long long mod = 1e9 + 7;
        int n = nums.size();
        vector<array<long long, 1001>> f(n);
        array<long long, 1001> pre;
        // f[i][j] = ∑ f[i - 1][0...min({nums[i - 1], j, nums[i - 1] - nums[i] + j})]
        for (int j = 0; j <= nums[0]; j++) f[0][j] = 1;
        for (int i = 1; i < n; i++) {
            partial_sum(f[i - 1].begin(), f[i - 1].end(), pre.begin());
            for (int j = 0; j <= nums[i]; j++) {
                int mx = min({nums[i - 1], j, nums[i - 1] - nums[i] + j});
                if (mx >= 0) f[i][j] = pre[mx];
                f[i][j] %= mod;
            }
        }
        long long ans = 0;
        for (int k = 0; k <= nums[n - 1]; k++) {
            ans += f[n - 1][k];
            ans %= mod;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3251 solu;
    cout << solu.countOfPairs(*new vector<int>{5,5,5,5}) << endl;
    return 0;
}