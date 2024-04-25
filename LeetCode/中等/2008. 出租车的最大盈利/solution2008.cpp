/*
url: https://leetcode.cn/problems/maximum-earnings-from-taxi/description/
标签: 动态规划
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2008 {
public:
    // LeetCode上执行用时388ms
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        vector<long long> dp(n + 1, 0); // dp[i]表示在i位置的最大收益
        vector<vector<vector<int>>> map(n + 1); // map[i]记录终点为i的ride
        for (auto& ride : rides) {
            /* 这里ride是vector<int>&，放进去会发生复制，所以maxTaxiEarnings_implementation2()改了下，
            里面装vector<int>*，效果类似Java
            */
            map[ride[1]].push_back(ride);
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            // 在i位置有两种情况，刚放下一个人，或者没有放下人，也就是典型的选与不选的分类情况
            dp[i] = dp[i - 1]; // 没放下人
            // 在i位置放下一个人的情况
            for (auto& ride : map[i]) {
                dp[i] = max(dp[i], dp[ride[0]] + ride[1] - ride[0] + ride[2]);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    // 改成装vector<int>*，效果类似Java，LeetCode上执行用时366ms
    long long maxTaxiEarnings_implementation2(int n, vector<vector<int>>& rides) {
        vector<long long> dp(n + 1, 0); // dp[i]表示在i位置的最大收益
        vector<vector<vector<int>*>> map(n + 1); // map[i]记录终点为i的ride
        for (auto& ride : rides) {
            map[ride[1]].push_back(&ride);
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            // 在i位置有两种情况，刚放下一个人，或者没有放下人，也就是典型的选与不选的分类情况
            dp[i] = dp[i - 1]; // 没放下人
            // 在i位置放下一个人的情况
            for (auto& ride : map[i]) {
                dp[i] = max(dp[i], dp[(*ride)[0]] + (*ride)[1] - (*ride)[0] + (*ride)[2]);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2008 solu;
    int n = 5;
    vector<vector<int>> rides = {{2,5,4},{1,5,1}};
    cout << solu.maxTaxiEarnings(n, rides) << endl;
    cout << solu.maxTaxiEarnings_implementation2(n, rides) << endl;
    return 0;
}
