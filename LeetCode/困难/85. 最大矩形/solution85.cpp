/*
url: https://leetcode.cn/problems/maximal-rectangle/
参考: https://leetcode.cn/problems/maximal-rectangle/solutions/535672/zui-da-ju-xing-by-leetcode-solution-bjlu/
相关: LeetCode84. 柱状图中最大的矩形, LeetCode1504. 统计全 1 子矩形, LeetCode221. 最大正方形
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution85 {
public:
    // 官方题解解法一，枚举右边界(竖线)位置，然后就变成了LeetCode84. 柱状图中最大的矩形。于是需要预先求出每个点左侧的连续1数量
    // 时间复杂度O(mn)
    int maximalRectangle(vector<vector<char>>& matrix) {
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
            // 固定右边界后，变成LeetCode84，具体见LeetCode84的官方题解
            // 枚举f[i][j]为高，求能以这个为高的最大宽度
            // 求f[i][j]上侧第一个 < f[i][j]的位置
            // 顺便同时求f[i][j]下侧第一个 <= f[i][j]的位置
            vector<int> up(m);
            vector<int> down(m, m);

            stack<int> st; // 单调栈
            for (int i = 0; i < m; i++) {
                while (!st.empty() && f[st.top()][j] >= f[i][j]) {
                    down[st.top()] = i;
                    st.pop();
                }
                up[i] = st.empty() ? -1 : st.top();
                st.push(i);
            }

            for (int i = 0; i < m; i++) {
                // 矩形w为f[i][j]，高取为(up, down)，可能f[down[i]][j]与f[i][j]相等，但是那种情况会在遍历i == down[i][j]时被涵盖，不会有问题
                ans = max(ans, f[i][j] * (down[i] - up[i] - 1));
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution85 solu;
    cout << solu.maximalRectangle(*new vector<vector<char>>{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}}) << endl;
    cout << solu.maximalRectangle(*new vector<vector<char>>{{'0','0','1'},{'1','1','1'}}) << endl;
    return 0;
}