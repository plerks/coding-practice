// https://leetcode.cn/problems/minimum-ascii-delete-sum-for-two-strings/description/

#include <bits/stdc++.h>

using namespace std;

class Solution712 {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0x3f3f3f3f)); // dp[i][j]表示s1[0 ... i)和s2[0 ... j)的最小开销

        // 考虑s1的i和s2的j位置，如果二者相同，则这位置不需删，若不同，则要么删s1[i]，要么删s2[j]，要么删2个

        dp[0][0] = 0;
        for (int i = 1; i <= m; i++) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }

        for (int j = 1; j <= n; j++) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }

        // 依赖左方，左上方，上方3个位置，和最长公共子序列很像
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
                else {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + s1[i - 1]);
                    dp[i][j] = min(dp[i][j], dp[i][j - 1] + s2[j - 1]);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + s1[i - 1] + s2[j - 1]);
                }
            }
        }
        return dp[m][n];
    }

    // 此题用dp求ascii值最大的公共子序列，然后剩下的字符就是最小删除开销，应该也行
};

int main(int argc, char const *argv[]) {
    Solution712 solu;
    cout << solu.minimumDeleteSum("delete", "leet") << endl;
    return 0;
}
