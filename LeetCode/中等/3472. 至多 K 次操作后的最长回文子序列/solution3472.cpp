/*
url: https://leetcode.cn/problems/longest-palindromic-subsequence-after-at-most-k-operations/
参考: https://www.bilibili.com/video/BV1QP9bY3EL6/
相关: LeetCode516. 最长回文子序列
标签: LeetCode第439场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3472 {
public:
    /* 参考灵茶题解，相比LeetCode516. 最长回文子序列，多了个k的约束，"多个约束，就多个参数"。
    若s[i] == s[j]，f[i][j][k] = 2 + f[i + 1][j - 1][k]
    若s[i] != s[j]，f[i][j][k] = max(f[i][j - 1][k], 2 + f[i + 1][j - 1][k - dis(s[i], s[j])],
                                    f[i + 1][j][k], 2 + f[i + 1][j - 1][k - dis(s[i], s[j])])
    */
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        vector<vector<vector<int>>> f(n, vector<vector<int>>(n, vector<int>(k + 1)));
        for (int i = 0; i < n; i++) {
            for (int z = 0; z <= k; z++) {
                f[i][i][z] = 1;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                for (int z = 0; z <= k; z++) {
                    if (s[i] == s[j]) f[i][j][z] = 2 + f[i + 1][j - 1][z];
                    else {
                        int d = abs(s[i] - s[j]);
                        int op = min(d, 26 - d);
                        if (z - op >= 0) {
                            f[i][j][z] = max({f[i][j - 1][z], 2 + f[i + 1][j - 1][z - op],
                                              f[i + 1][j][z]});
                        }
                        else f[i][j][z] = max({f[i][j - 1][z], f[i + 1][j][z]});
                    }
                }
            }
        }
        return f[0][n - 1][k];
    }
};

int main(int argc, char const *argv[]) {
    Solution3472 solu;
    cout << solu.longestPalindromicSubsequence(*new string("abced"), 2) << endl; 
    return 0;
}