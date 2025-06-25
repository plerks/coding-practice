/*
url: https://leetcode.cn/problems/surrounded-regions/
相关: LeetCode1254. 统计封闭岛屿的数目
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution130 {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        vector<vector<int>> vis(m, vector<int>(n, false));
        auto dfs = [&](auto& dfs, int i, int j) {
            if (i < 0 || i >= m || j < 0 || j >= n || vis[i][j] || board[i][j] == 'X') return;
            vis[i][j] = true;
            board[i][j] = 't';
            dfs(dfs, i - 1, j);
            dfs(dfs, i + 1, j);
            dfs(dfs, i, j - 1);
            dfs(dfs, i, j + 1);
        };

        // 遍历四周边界上的'O'的连通分量
        for (int i = 0; i < m; i++) {
            int step = i == 0 || i == m - 1 ? 1 : n - 1;
            for (int j = 0; j < n; j += step) {
                dfs(dfs, i, j);
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == 't') board[i][j] = 'O';
            }
        }
    }
};

int main(int argc, char const *argv[]) {
    Solution130 solu;
    solu.solve(*new vector<vector<char>>{{'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}});
    return 0;
}