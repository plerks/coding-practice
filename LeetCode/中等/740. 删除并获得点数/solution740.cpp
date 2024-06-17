/*
url: https://leetcode.cn/problems/delete-and-earn/description/
LeetCode参考: https://leetcode.cn/problems/maximum-total-damage-with-spell-casting/solutions/2812389/tao-lu-da-jia-jie-she-pythonjavacgo-by-e-p9b5/
相关: LeetCode3186. 施咒的最大总伤害, LeetCode198. 打家劫舍
标签: 考虑值域
*/

#include <bits/stdc++.h>

using namespace std;

// LeetCode3186. 施咒的最大总伤害与此题基本相同，具体看那题我的注释
class Solution740 {
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> map;
        for (int num : nums) map[num]++;
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end());
        int n = vec.size();
        vector<int> dp(n, 0); // dp[i]表示使用vec[0...i]所能得到的最大值
        dp[0] = vec[0].first * vec[0].second;
        for (int i = 1, j = 0; i < n; i++) {
            // 选vec[i]
            while (vec[j].first < vec[i].first - 1) {
                j++;
            }
            // j为第一个 >= vec[i].first - 1的，j - 1为选vec[i]的情况下上一个能考虑的右边界
            int res1 = j - 1 >= 0 ? dp[j - 1] + vec[i].first * vec[i].second : vec[i].first * vec[i].second;

            // 不选vec[i]
            int res2 = dp[i - 1];
            dp[i] = max(res1, res2);
        }
        return dp[n - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution740 solu;
    vector<int> nums = {2,2,3,3,3,4};
    cout << solu.deleteAndEarn(nums) << endl;
    return 0;
}
