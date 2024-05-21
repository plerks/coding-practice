/*
url: https://leetcode.cn/problems/maximum-difference-score-in-a-grid/description/
LeetCode参考: https://leetcode.cn/problems/maximum-difference-score-in-a-grid/solutions/2774823/nao-jin-ji-zhuan-wan-dppythonjavacgo-by-swux7/
相关: LeetCode304. 二维区域和检索 - 矩阵不可变
标签: LeetCode第397场周赛, 二维前缀和, 二维前缀最值, 二维前缀最小值
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3148 {
public:
    // 周赛时直接写的O(n^3)的暴力解法，能通过，不过接近超时
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -0x3f3f3f3f)); // dp[i][j]到(i, j)且有过跳跃的最优解
        int ans = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // dp[i][j]由上方和左侧转移来
                dp[i][j] = -0x3f3f3f3f;
                for (int k = i - 1; k >= 0; k--) {
                    dp[i][j] = max(dp[i][j], (dp[k][j] > 0 ? dp[k][j] : 0) + grid[i][j] - grid[k][j]);
                }
                for (int k = j - 1; k >= 0; k--) {
                    dp[i][j] = max(dp[i][j], (dp[i][k] > 0 ? dp[i][k] : 0) + grid[i][j] - grid[i][k]);
                }
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法，(c2 - c1) + (c3 - c2) = c3 - c1，因此得分只与路径起点终点有关，与路径无关，
    对特定的终点(i, j)，取最大得分的起点是左上区域(不包含(i, j))取最小值的位置，这是类似二维前缀和的问题，只是换成了求最小值，比求和要简单点。
    这里二维前缀最小值记录包含(i, j)的左上角区域的最小值，对终点为(i, j)，用(i - 1, j)和(i, j - 1)即可找出不包含(i, j)位置的最小值 */
    int maxScore_implementation2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> prefix(m, vector<int>(n, INT_MAX)); // 二维前缀最小值
        int ans = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int preMin = INT_MAX;
                if (i - 1 >= 0) preMin = min(preMin, prefix[i - 1][j]);
                if (j - 1 >= 0) preMin = min(preMin, prefix[i][j - 1]);
                prefix[i][j] = min(grid[i][j], preMin);
                ans = max(ans, grid[i][j] - preMin);
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法二，优化空间使用，遍历过程中只维护每列的最小值即可
    int maxScore_implementation3(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int ans = INT_MIN;
        vector<int> colMin(n, INT_MAX);
        for (int i = 0; i < m; i++) {
            int preMin = INT_MAX;
            for (int j = 0; j < n; j++) {
                // preMin这时为[0, j - 1]列的最小值，colMin[j]为grid[i][0 ... j - 1]的最小值
                ans = max(ans, grid[i][j] - min(preMin, colMin[j]));
                // 更新两个变量
                colMin[j] = min(colMin[j], grid[i][j]);
                preMin = min(preMin, colMin[j]);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3148 solu;
    vector<vector<int>> grid = {{9,5,7,3},{8,9,6,1},{6,7,14,3},{2,5,3,1}};
    cout << solu.maxScore(grid) << endl;
    cout << solu.maxScore_implementation2(grid) << endl;
    cout << solu.maxScore_implementation3(grid) << endl;
    return 0;
}
