/*
url: https://leetcode.cn/problems/minimum-number-of-refueling-stops/?envType=daily-question&envId=2024-10-07
参考: https://leetcode.cn/problems/minimum-number-of-refueling-stops/solutions/1636921/zui-di-jia-you-ci-shu-by-leetcode-soluti-nmga/
      https://leetcode.cn/problems/minimum-number-of-refueling-stops/solutions/553778/bang-ni-kan-dong-guan-jie-de-dong-tai-gu-8oyf/
相关: LeetCode1928. 规定时间内到达终点的最小花费
标签: 动态规划, 动态规划例题, dp定义技巧, 贪心
*/

#include <bits/stdc++.h>

using namespace std;

class Solution871 {
public:
    // 我的解法，记忆化搜索，109 / 198 个通过的测试用例，超时，1 <= target, startFuel <= 10^9, 0 <= stations.length <= 500，能产生很多情况
    int minRefuelStops_exceed_time_limit(int target, int startFuel, vector<vector<int>>& stations) {
        map<pair<int, int>, int> memo;

        auto dfs = [&](auto &dfs, int pos, int startFuel) {
            if (pos + startFuel >= target) return 0;
            if (memo.count({pos, startFuel})) return memo[{pos, startFuel}];
            // 找到stations里第一个>pos的
            int left = 0;
            int right = stations.size() - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (stations[mid][0] <= pos) {
                    left = mid + 1;
                }
                else right = mid - 1;
            }
            int min = INT_MAX;
            if (left == stations.size()) memo[{pos, startFuel}] = INT_MAX;
            for (int i = left; i < stations.size(); i++) {
                if (pos + startFuel < stations[i][0]) break;
                int cnt = dfs(dfs, stations[i][0], startFuel - (stations[i][0] - pos) + stations[i][1]);
                if (cnt != INT_MAX) min = std::min(min, 1 + cnt);
            }
            memo[{pos, startFuel}] = min;
            return min;
        };

        int ans = dfs(dfs, 0, startFuel);

        return ans == INT_MAX ? -1 : ans;
    }

    // 看了官方题解后写的dp，从加油次数来考虑，枚举次数。时间复杂度O(n^3)，180 / 198 个通过的测试用例，超时
    int minRefuelStops_exceed_time_limit2(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        // dp[i][j]表示加油i次，且最后一次是在stations[j]时，能走的最大距离
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));
        for (int j = 0; j < n; j++) {
            if (stations[j][0] <= startFuel) dp[1][j] = startFuel + stations[j][1];
        }
        for (int i = 2; i <= n; i++) {
            for (int j = i - 1; j < n; j++) { // 在j位置加第i次油，则前面至少有i - 1个station，j从i - 1开始枚举
                // 第 i - 1 次加油的位置
                for (int k = j - 1; k >= 0; k--) {
                    if (dp[i - 1][k] >= stations[j][0]) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][k] + stations[j][1]);
                    }
                }
            }
        }
        if (startFuel >= target) return 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] >= target) return i;
            }
        }
        return -1;
    }

    /* 官方题解解法一，从加油次数来考虑，枚举次数。

    考虑minRefuelStops_exceed_time_limit2()的不足，实际上我们要求加油i次能走的最大距离，不需要知道上一步在哪里，
    只需要知道用i - 1次加油能不能到stations[j]。

    这提示我们改变dp的设法，

    对加油次数i，考虑最后一次加油的位置j(j >= i)，那么其最远到达距离就是使用j左侧的station加油i - 1次能到达的最大距离 + stations[j][1]，
    同时，还需要考虑 i - 1 次加油能不能到达 j 位置。
    这样就能看出来dp需要设2个参数，加油次数和加油范围。
    */
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        // dp[i][j]表示使用stations[0...j)加油i次能到达的最大距离，这里dp使用左闭右开区间最好，因为这样一个station不用j就是0，不会出现-1
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));
        for (int j = 0; j <= n; j++) dp[0][j] = startFuel;
        for (int i = 1; i <= n; i++) { // i是加油次数
            for (int j = i; j <= n; j++) {
                // 为了转化为子问题，考虑j-1位置选与不选
                // 选第j-1位置(在j-1位置加油)
                if (dp[i - 1][j - 1] >= stations[j - 1][0]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + stations[j - 1][1]);
                }
                // 不选第j-1位置
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }
        for (int i = 0; i <= n; i++) {
            if (dp[i][n] >= target) return i;
        }
        return -1;
    }

    /* 这里的dp定义有技巧性，和LeetCode1928. 规定时间内到达终点的最小花费有点相似，不知道加油次数但知道范围就枚举次数，然后判定
    能否到达
    */

    // 官方题解解法二，先把油量按大根堆组织暂存，当油量不够时再依次补充之前的，并优先拿大的，这样就能判定能不能到i位置
    int minRefuelStops_implementation2(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> q;
        int n = stations.size();
        stations.push_back({target, 0});
        int fuel = startFuel;
        int prev = 0; // 上一次的位置
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            int cur = stations[i][0];
            fuel -= cur - prev; // 耗油
            while (fuel < 0 && !q.empty()) {
                fuel += q.top();
                q.pop();
                ans++;
            }
            if (fuel < 0) return -1;
            q.emplace(stations[i][1]);
            prev = cur;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution871 solu;
    vector<vector<int>> stations = {{10,60},{20,30},{30,30},{60,40}};
    cout << solu.minRefuelStops(100, 10, stations) << endl;

    vector<vector<int>> stations2 = {{25,27},{36,187},{140,186},{378,6},{492,202},{517,89},{579,234},{673,86},{808,53},{954,49}};
    // cout << solu.minRefuelStops(1000, 83, stations) << endl;
    return 0;
}
