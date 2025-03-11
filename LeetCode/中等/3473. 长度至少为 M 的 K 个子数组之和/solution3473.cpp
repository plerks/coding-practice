/*
url: https://leetcode.cn/problems/sum-of-k-subarrays-with-length-at-least-m/
参考: https://www.bilibili.com/video/BV1QP9bY3EL6/
标签: LeetCode第439场周赛, 划分型dp, dp > 记忆化, 必须dp
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3473 {
public:
    // 周赛时写的记忆化搜索，555 / 624 个通过的测试用例，超时
    int maxSum_tle(vector<int>& nums, int k, int m) {
        int n = nums.size();
        int ans = INT_MIN;

        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + nums[i];
        }

        unordered_map<long long, int> memo;
        
        auto dfs = [&](auto & dfs, int start, int k) { // 从>=start的位置，选k段出来，能得到的最大值
            if (memo.count(start * 10001 + k)) return memo[start * 10001 + k];
            int res = INT_MIN;
            
            if (k == 1) {
                for (int i = start; i < n; i++) { // 枚举第一段开头位置i
                    for (int len = m; i + len <= n - m * (k - 1); len++) { // 枚举第一段长度
                        int sg1 = pre[i + len - 1 + 1] - pre[i - 1 + 1];
                        res = max(res, sg1);
                        // cout << i << " " << len << " " << res << endl;
                    }   
                }
                return res;
            }
            
            for (int i = start; i < n; i++) { // 枚举第一段开头位置i
                for (int len = m; i + len <= n - m * (k - 1); len++) { // 枚举第一段长度
                    int sg1 = pre[i + len - 1 + 1] - pre[i - 1 + 1];
                    res = max(res, sg1 + dfs(dfs, i + len, k - 1));
                    // cout << i << " " << len << " " << res << endl;
                }   
            }
            memo[start * 10001 + k] = res;
            return res;
        };

        ans = dfs(dfs, 0, k);
        return ans;
    }

    /* 参考灵茶题解，
    原问题：从[0, n)选k个子数组，这时如果去考虑第一段/最后一段的位置，就会写成maxSum_tle()那样，
    dfs()里要枚举最后一段的位置i, j，也就是说dfs里有个n^2，加上dfs本身的参数，会是个4次方的时间复杂度。
    这样不行的原因应该是在于，没有充分转化为同类型的子问题。
    关键在于优化dfs里的n^2，考虑最后一个位置选与不选，
    若最后一个子数组右边界不在nums[n - 1]，则问题直接转化为dfs(n - 1, k)；
    若最后一个子数组右边界在nums[n - 1]，则最后一个子数组就固定了一侧了，这样只需枚举左边界，这样dfs里就是线性的；
    f[i][j]表示从nums[0, j)选i个子数组，则
    f[i][j] = max(f[i][j - 1], max{l=(i-1)*m, j-m}f[i - 1][l] + sum(l, j - 1))，但这dfs里仍然有一重循环，再用前缀最大值优化，
    这个前缀最值优化，与LeetCode3148. 矩阵中的最大得分类似。
    */
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        vector<int> s(n + 1); // 前缀和，向右偏移1
        partial_sum(nums.begin(), nums.end(), s.begin() + 1);

        vector<vector<int>> f(k + 1, vector<int>(n + 1, -0x3f3f3f3f));

        for (int i = 0; i <= n; i++) f[0][i] = 0; // nums可能为负，f[0]要全为0，其它位置要为负无穷

        for (int i = 1; i <= k; i++) {
            int mx = INT_MIN;
            for (int j = i * m; j <= n - (k - i) * m; j++) {
                // 找i个子数组，右边界j的范围在[i * m, n - (k - i) * m]
                // 而i - 1个子数组，右边界j的范围在[(i - 1) * m, n - (k - (i + 1)) * m]
                // j - m枚举了l=(i-1)*m, j-m这个范围
                mx = max(mx, f[i - 1][j - m] - s[j - m]);
                // 这题涉及到前缀最大和，记忆化搜索不好处理，只能用dp(记忆化搜索应该也能处理，不过不如直接dp)
                f[i][j] = max(f[i][j - 1], mx + s[j]);
            }
        }
        return f[k][n];
    }
};

int main(int argc, char const *argv[]) {
    Solution3473 solu;
    cout << solu.maxSum(*new vector<int>{1,2,-1,3,3,4}, 2, 2) << endl;
    cout << solu.maxSum(*new vector<int>{-10,3,-1,-2}, 4, 1) << endl;
    return 0;
}