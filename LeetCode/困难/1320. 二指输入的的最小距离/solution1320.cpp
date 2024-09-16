/*
url: https://leetcode.cn/problems/minimum-distance-to-type-a-word-using-two-fingers/description/
标签: 动态规划
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1320 {
public:
    int minimumDistance(string word) {
        int n = word.size();
        // dp[i][j]表示点完前max(i, j)个字符，且手指1在i位置，手指2在j位置的最小开销，用0代表手指初始位置
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0x3f3f3f3f));
        dp[1][0] = 0;
        dp[0][1] = 0;
        for (int x = 0; x < n; x++) {
            // 情况1，由i转移来。要么i在x - 1位置，j任意(< x - 1)，要么i在< x - 1的位置，j在x - 1位置
            for (int j = -1; j < x - 1; j++) {
                dp[x + 1][j + 1] = min(dp[x + 1][j + 1], dp[x][j + 1] + dis(word, x - 1, x));
            }
            for (int i = -1; i < x - 1; i++) {
                dp[x + 1][x] = min(dp[x + 1][x], dp[i + 1][x] + dis(word, i, x));
            }

            // 情况2，由j转移来。要么j在x - 1位置，i任意(< x - 1)，要么j在< x - 1的位置，i在x - 1位置
            for (int i = -1; i < x - 1; i++) {
                dp[i + 1][x + 1] = min(dp[i + 1][x + 1], dp[i + 1][x] + dis(word, x - 1, x));
            }
            for (int j = -1; j < x - 1; j++) {
                dp[x][x + 1] = min(dp[x][x + 1], dp[x][j + 1] + dis(word, j, x));
            }
        }
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) ans = min(ans, dp[i + 1][n]);
        for (int j = 0; j < n; j++) ans = min(ans, dp[n][j + 1]);
        return ans;
    }

    int dis(string &word, int x, int y) {
        if (x == -1) return 0;
        int x1 = (word[x] - 'A') / 6;
        int y1 = (word[x] - 'A') % 6;
        int x2 = (word[y] - 'A') / 6;
        int y2 = (word[y] - 'A') % 6;
        return abs(x1 - x2) + abs(y1 - y2);
    }
};

int main(int argc, char const *argv[]) {
    Solution1320 solu;
    cout << solu.minimumDistance("HAPPY") << endl;
    return 0;
}
