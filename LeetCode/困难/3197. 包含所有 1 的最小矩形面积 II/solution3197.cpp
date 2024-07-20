/*
url: https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-ii/
参考: https://www.bilibili.com/video/BV1MZ421M74P/
      https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-ii/description/
相关: LeetCode3195. 包含所有 1 的最小矩形面积 I
标签: LeetCode第403场周赛
*/

// 这次周赛3题

#include <bits/stdc++.h>

using namespace std;

class Solution3197 {
public:
    /* 参考灵茶山艾府题解。
    3个矩形，是可以用2条分割线分隔成3个区域的，暴力枚举分隔线的位置。
    先考虑第一条分割线是水平的情况，第二条分割线的情况为：
    1. 第二条分割线也是水平
    2. 第二条分割线是竖直且在第一条线下方
    3. 第二条分割线是竖直且在第一条线上方
    用LeetCode3195的代码求出3个区域包含所有1的最小矩阵面积相加

    如果切出来的区域没有1，则最终结果也是对的，这种切出0面积的方式不会比最优解优。后续会枚举到所有切割方式

    若第一条分割线是竖直，则将矩阵旋转90度进行处理，可以用上面3种情况的代码处理。

    如果是要切4个矩形，则性质会不一样，见灵茶山艾府视频讲解示例图.jpg，第一刀就可能不能切透，会复杂很多
    */
    int calc(vector<vector<int>>& grid) {
        int ans = INT_MAX;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i <= m - 2; i++) {
            // 第二条线也是水平，枚举位置
            for (int j = i + 1; j <= m - 2; j++) {
                ans = min(ans, minimumArea(grid, 0, i, 0, n - 1) + minimumArea(grid, i + 1, j, 0, n - 1) + minimumArea(grid, j + 1, m - 1, 0, n - 1));
            }
            // 第二条线竖直且在第一条线下方
            for (int j = 0; j <= n - 2; j++) {
                ans = min(ans, minimumArea(grid, 0, i, 0, n - 1) + minimumArea(grid, i + 1, m - 1, 0, j) + minimumArea(grid, i + 1, m - 1, j + 1, n - 1));
            }
            // 第二条线竖直且在第一条线上方
            for (int j = 0; j <= n - 2; j++) {
                ans = min(ans, minimumArea(grid, i + 1, m - 1, 0, n - 1) + minimumArea(grid, 0, i, 0, j) + minimumArea(grid, 0, i, j + 1, n - 1));
            }
        }
        return ans;
    }

    int minimumSum(vector<vector<int>>& grid) {
        int ans = INT_MAX;
        int m = grid.size();
        int n = grid[0].size();

        ans = min(ans, calc(grid));

        vector<vector<int>> r_grid(n, vector<int>(m)); // 旋转90度的矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                r_grid[i][j] = grid[j][i];
            }
        }
        ans = min(ans, calc(r_grid));
        return ans;
    }

    // 用LeetCode3195. 包含所有 1 的最小矩形面积 I的代码求出区域内包含所有1的矩形最小面积
    int minimumArea(vector<vector<int>>& grid, int r1, int r2, int c1, int c2) {
        int m = grid.size();
        int n = grid[0].size();
        int x1, y1, x2, y2;
        x1 = m - 1;
        x2 = 0;
        y1 = n - 1;
        y2 = 0;
        for (int i = r1; i <= r2; i++) {
            for (int j = c1; j <= c2; j++) {
                if (grid[i][j] == 1) {
                    x1 = min(x1, i);
                    x2 = max(x2, i);
                    y1 = min(y1, j);
                    y2 = max(y2, j);
                }
            }
        }
        return (y2 - y1 + 1) * (x2 - x1 + 1);
    }
};

int main(int argc, char const *argv[]) {
    Solution3197 solu;
    vector<vector<int>> grid = {{1,0,1},{1,1,1}};
    vector<vector<int>> grid2 = {{1,0,1,0},{0,1,0,1}};
    cout << solu.minimumSum(grid) << endl;
    cout << solu.minimumSum(grid2) << endl;
    return 0;
}
