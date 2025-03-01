/*
url: https://leetcode.cn/problems/maximum-sum-with-at-most-k-elements/
参考: https://www.bilibili.com/video/BV1hiAUeWEUG/
      https://leetcode.cn/problems/maximum-sum-with-at-most-k-elements/solutions/3086172/cong-da-dao-xiao-tan-xin-pythonjavacgo-b-vjt2/
标签: LeetCode第438场周赛, 贪心 > dp, partition, 快速选择
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3462 {
public:
    /* 周赛时写的超时dp做法，584 / 594 个通过的测试用例，然后以为是能优化dp的一维，结果是要贪心。
    这题dp要O(n^3)，然后 500^3 = 125000000，大概1e8，然后超时。
    必须要用贪心的思路，不能dp，时间复杂度完全不一样。
    */
    long long maxSum_tle(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            sort(grid[i].rbegin(), grid[i].rend());
        }
        vector<vector<long long>> gsum(n, vector<long long>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    gsum[i][j] = grid[i][j];
                    continue;
                }
                gsum[i][j] = grid[i][j] + gsum[i][j - 1];
            }
        }
        vector<vector<long long>> dp(n, vector<long long>(k + 1));
        for (int j = 0; j <= min(k, limits[0]); j++) {
            dp[0][j] = j - 1 == -1 ? 0 : gsum[0][j - 1];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                for (int x = 0; x <= j && x <= limits[i]; x++) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - x] + (x - 1 == -1 ? 0 : gsum[i][x - 1]));
                }
            }
        }
        return dp[n - 1][k];
    }

    /* 灵茶题解解法一，
    如果没有每行limit[i]的限制，则应该选最大的k个数，所以，要做的是把每行小的多于limit[i]的数全丢掉，
    然后这样就没有limit的限制，然后选最大的k个数。
    时间复杂度O(mnlog(mn))
    */
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<pair<int, int>> nums;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                nums.push_back({grid[i][j], i});
            }
        }
        sort(nums.rbegin(), nums.rend());
        long long ans = 0;
        for (int i = 0; i < nums.size() && k > 0; i++) {
            auto &[num, row] = nums[i];
            if (limits[row] > 0) {
                ans += num;
                limits[row]--;
                k--;
            }
        }
        return ans;
    }

    /* 灵茶题解解法二，使用快速选择
    不需要完整的排序，只需要partition就行了，时间复杂度O(mn)
    */
    long long maxSum_implementation2(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        vector<int> nums;
        for (int i = 0; i < n; i++) {
            auto &row = grid[i];
            // nth_element()对begin, nth, end做partition，不返回值，结束之后已经划分好
            nth_element(row.begin(), row.end() - limits[i], row.end());
            nums.insert(nums.end(), row.end() - limits[i], row.end());
        }
        nth_element(nums.begin(), nums.end() - k, nums.end());
        return accumulate(nums.end() - k, nums.end(), 0LL);
    }
};

int main(int argc, char const *argv[]) {
    Solution3462 solu;
    cout << solu.maxSum_tle(*new vector<vector<int>>{{1,2},{3,4}}, *new vector<int>{1,2},2) << endl;
    cout << solu.maxSum(*new vector<vector<int>>{{1,2},{3,4}}, *new vector<int>{1,2},2) << endl;
    cout << solu.maxSum_implementation2(*new vector<vector<int>>{{1,2},{3,4}}, *new vector<int>{1,2},2) << endl;
    return 0;
}