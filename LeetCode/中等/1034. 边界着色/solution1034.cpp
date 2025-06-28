/*
url: https://leetcode.cn/problems/coloring-a-border/
相关: LeetCode463. 岛屿的周长
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1034 {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size();
        int n = grid[0].size();
        int c = grid[row][col];
        auto ans = grid;

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<int>> vis(m, vector<int>(n, false));

        auto dfs = [&](auto& dfs, int i, int j) -> void {
            vis[i][j] = true;
            bool is_edge = false;
            for (auto [dx, dy] : directions) {
                int ii = i + dx, jj = j + dy;
                if (!legal(ii, jj) || grid[ii][jj] != c) {
                    is_edge = true;
                }
                else if (!vis[ii][jj]) dfs(dfs, ii, jj);
            }
            if (is_edge) ans[i][j] = color;
        };

        dfs(dfs, row, col);
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1034 solu;
    // auto a = solu.colorBorder(*new vector<vector<int>>{{1,1},{1,2}}, 0, 0, 3);
    auto b = solu.colorBorder(*new vector<vector<int>>{{1,1,1},{1,1,1},{1,1,1}}, 1, 1, 2);
    return 0;
}