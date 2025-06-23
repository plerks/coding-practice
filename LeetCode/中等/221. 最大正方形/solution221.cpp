/*
url: https://leetcode.cn/problems/maximal-square/
参考: https://leetcode.cn/problems/maximal-square/solutions/234964/zui-da-zheng-fang-xing-by-leetcode-solution/
相关: LeetCode85. 最大矩形
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution221 {
public:
    // LeetCode85 的单调栈解法，时间复杂度O(mn)
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<vector<int>> f(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '0') {
                    cnt = 0;
                    f[i][j] = 0;
                }
                else {
                    cnt++;
                    f[i][j] = cnt;
                }
            }
        }

        int ans = 0;

        for (int j = 0; j < n; j++) {
            stack<int> st;
            vector<int> left(m); // 上侧第一个 <
            vector<int> right(m, m); // 下侧第一个 <=
            for (int i = 0; i < m; i++) {
                while (!st.empty() && f[st.top()][j] >= f[i][j]) {
                    right[st.top()] = i;
                    st.pop();
                }
                left[i] = st.empty() ? -1 : st.top();
                st.push(i);
            }
            for (int i = 0; i < m; i++) {
                int w = f[i][j];
                int h = right[i] - left[i] - 1;
                int e = min(w, h);
                ans = max(ans, e * e);
            }
        }
        return ans;
    }

    // 参考官方题解，动态规划的解法，时间复杂度也是O(mn)，常数低
    // dp[i][j]表示以(i, j)为右下角的正方形的边长，则若matrix[i][j]为1，则dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
    int maximalSquare_implementation2(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> f(m + 1, vector<int>(n + 1));

        int mx = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    f[i + 1][j + 1] = 1 + min({f[i - 1 + 1][j + 1], f[i + 1][j - 1 + 1], f[i - 1 + 1][j - 1 + 1]});
                    mx = max(mx, f[i + 1][j + 1]);
                }
            }
        }
        return mx * mx;
    }
};

int main(int argc, char const *argv[]) {
    Solution221 solu;
    cout << solu.maximalSquare(*new vector<vector<char>>{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}}) << endl;

    cout << solu.maximalSquare_implementation2(*new vector<vector<char>>{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}}) << endl;
    return 0;
}