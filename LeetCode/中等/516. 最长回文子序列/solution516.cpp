/*
url: https://leetcode.cn/problems/longest-palindromic-subsequence/
参考: https://www.bilibili.com/video/BV1Gs4y1E7EU/
相关: LeetCode3472. 至多 K 次操作后的最长回文子序列
标签: 子序列, 最长公共子序列LCS
*/
#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

class Solution516 {
public:
    /* 一种做法是，把s反转，求s和reverse(s)的最长公共子序列(LCS)。
    但是可以直接做，类似LCS的思考方式，
    若首尾相等，则dfs(0, n - 1) = 2 + dfs(1, n - 2)，
    若首尾不等，则要么s[0]要用，要么s[n-1]要用，要么二者都不用，
    dfs(0, n - 1) == max({dfs(0, n - 2), dfs(1, n - 1), dfs(1, n - 2)})
    */
    int longestPalindromeSubseq(string s) {
        int n = s.size();

        vector<int> memo((n - 1) * n + n - 1 + 1, -1);

        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i == j) return 1;
            if (i > j) return 0;
            if (memo[i * n + j] != -1) return memo[i * n + j];
            int res = -1;
            if (s[i] == s[j]) {
                res = 2 + dfs(dfs, i + 1, j - 1);
            }
            else res = max({dfs(dfs, i, j - 1), dfs(dfs, i + 1, j), dfs(dfs, i + 1, j - 1)});
            memo[i * n + j] = res;
            return res;
        };
        
        return dfs(dfs, 0, n - 1);
    }

    /* dp，f[i][j] = 2 + f[i + 1][j - 1] 或者 f[i][j] = max({f[i][j - 1], f[i + 1][j], f[i + 1][j - 1]})。
    从右边到f[i][j]，i减小，j增大，所以枚举时i减小，j增大。
    */
    int longestPalindromeSubseq_implementation2(string s) {
        int n = s.size();
        vector<vector<int>> f(n, vector<int>(n));
        for (int i = 0; i < n; i++) f[i][i] = 1; // 这题不用f[n + 1][n + 1]，因为j要>i，第n - 1行不会算元素
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    f[i][j] = 2 + f[i + 1][j - 1];
                }
                else {
                    f[i][j] = max({f[i][j - 1], f[i + 1][j]}); // 不选s[i]，不选s[j]，s[i]和s[j]都不选，只用前两种情况就可以涵盖
                }
            }
        }
        return f[0][n - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution516 solu;
    cout << solu.longestPalindromeSubseq(*new string("bbbab")) << endl;
    cout << solu.longestPalindromeSubseq_implementation2(*new string("bbbab")) << endl;
    return 0;
}