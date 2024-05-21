/*
url: https://leetcode.cn/problems/taking-maximum-energy-from-the-mystic-dungeon/description/
LeetCode参考: https://leetcode.cn/problems/taking-maximum-energy-from-the-mystic-dungeon/solutions/2774844/o1-kong-jian-zuo-fa-pythonjavacgo-by-end-8rad/
标签: LeetCode第397场周赛, 动态规划, 后缀和
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3147 {
public:
    // 我的做法，用动态规划
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();
        vector<int> dp(n, 0); // dp[i]表示到达i位置可获得的最大能量
        dp[0] = energy[0];
        for (int i = 1; i < n; i++) {
            dp[i] = energy[i];
            if (i - k >= 0) {
                dp[i] = max(dp[i], energy[i] + dp[i - k]);
            }
        }
        int ans = INT_MIN;
        for (int i =  n - 1; i + k >= n; i--) {
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    // 灵茶山艾府题解解法，这题要走到不能再走为止，也就是说起点任意，终点极右，实际上是逆向遍历求最大的后缀和
    int maximumEnergy_implementation2(vector<int>& energy, int k) {
        int n = energy.size();
        int ans = INT_MIN;
        for (int i = n - 1; i + k >= n; i--) {
            int sum = 0;
            for (int j = i; j >= 0; j -= k) {
                sum += energy[j];
                ans = max(ans, sum);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3147 solu;
    vector<int> energy = {5,2,-10,-5,1};
    cout << solu.maximumEnergy(energy, 3) << endl;
    cout << solu.maximumEnergy_implementation2(energy, 3) << endl;
    return 0;
}