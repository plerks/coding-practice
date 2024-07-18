/*
url: https://leetcode.cn/problems/maximize-total-cost-of-alternating-subarrays/
参考: https://www.bilibili.com/video/BV1MZ421M74P/
标签: LeetCode第403场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3196 {
public:
    /* 我的解法。朴素的想法是dp[i]定义为对nums[0...i]的最大值，这样考虑i所在的子数组，以i位置为右边界，考虑枚举左边界，
    时间复杂度O(n^2)，nums.length <= 10^5，会超时。然后这样考虑，nums[i]要么以原值贡献，要么以相反值贡献。
    若nums[i]以原值贡献，则其在子数组的偶数位上，则其所在的子数组长这样：... nums[i]，枚举左边界是会超时的，
    但是这里有这样一个特点，把... nums[i]分割成... | nums[i]，算出来的值是一样的，因此是不需要枚举左边的。
    若nums[i]以相反值贡献，则其所在子数组：... nums[i - 1] nums[i]，同样，... | nums[i - 1] nums[i]的值
    是和这个子数组相等的，因此也不需要枚举左边界。
    */
    long long maximumTotalCost(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        vector<long long> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[1] + nums[0], nums[0] - nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1] + nums[i], dp[i - 2] + nums[i - 1] - nums[i]);
        }
        return dp[n - 1];
    }

    /* 从左往右记忆化搜索，对于第一个位置，一定是取原值。对于某个位置i,
    若i - 1位置是取的原值，则i位置可以取原值(在i前面分割一下)，也可以取相反值(在i前面不分割即可)，
    若i - 1位置是取的相反值，则i位置一定只能取原值(分不分割都是取的原值)。
    然后剩下的右侧又是一个类似的子问题。
    这里用function<long long(int, int)> dfs的话会超时，得用auto dfs = [&](auto& dfs, int i, int j)的写法
    */
    long long maximumTotalCost_implementation2(vector<int>& nums) {
        int n = nums.size();

        vector<vector<long long>> memo(n, vector<long long>(2, -1));

        // dfs(i, 0)表示i - 1位置取原值情况下的最大收益，dfs(i, 1)表示i - 1位置取相反值情况下的最大收益
        auto dfs = [&](auto& dfs, int i, int j) {
            if (i == n) return 0LL;
            if (memo[i][j] != -1) return memo[i][j];
            if (j == 0) {
                memo[i][j] = max(dfs(dfs, i + 1, 0) + nums[i], dfs(dfs, i + 1, 1) - nums[i]);
                return memo[i][j];
            }
            else {
                memo[i][j] = dfs(dfs, i + 1, 0) + nums[i];
                return memo[i][j];
            }
        };
        
        long long ans = nums[0] + dfs(dfs, 1, 0);
        return ans;
    }

    // 灵茶山艾府题解的记忆化搜索写法，从右往左，然后改成dp就和maximumTotalCost()一样
    long long maximumTotalCost_implementation3(vector<int>& nums) {
        int n = nums.size();

        vector<long long> memo(n, -1);

        /* dfs(i)表示nums[0, i]的最大收益，考虑最后一次划分的位置。要么i取原值，在i的前面划分，要么i取相反值，在i - 1的前面划分，让i - 1和i为一组。
        这里其实用到maximumTotalCost()划分后缀不影响值的性质 */
        auto dfs = [&](auto& dfs, int i) -> long long {
            if (i < 0) return 0LL;
            if (i == 0) return nums[0];
            if (memo[i] != -1) return memo[i];
            long long res = 0;
            res = max(dfs(dfs, i - 1) + nums[i], dfs(dfs, i - 2) + nums[i - 1] - nums[i]);
            memo[i] = res;
            return res;
        };

        return dfs(dfs, n - 1);
    }
};

int main(int argc, char const *argv[]) {
    Solution3196 solu;
    vector<int> nums = {1,-2,3,4};
    cout << solu.maximumTotalCost(nums) << endl;
    cout << solu.maximumTotalCost_implementation2(nums) << endl;
    cout << solu.maximumTotalCost_implementation3(nums) << endl;
    return 0;
}
