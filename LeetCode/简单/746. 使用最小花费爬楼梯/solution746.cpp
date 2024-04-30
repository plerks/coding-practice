/*
url: https://leetcode.cn/problems/min-cost-climbing-stairs/description/
相关: LeetCode70. 爬楼梯
标签: 动态规划
*/

#include <bits/stdc++.h>

using namespace std;

class Solution746 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1); // 后面dp求min()不需要用到dp[i]，不用把所有元素都初始化为INT_MAX
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i < n + 1; i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[n];
    }
};

int main(int argc, char const *argv[]) {
    Solution746 solu;
    vector<int> v = {10,15,20};
    cout << solu.minCostClimbingStairs(v) << endl;
    return 0;
}
