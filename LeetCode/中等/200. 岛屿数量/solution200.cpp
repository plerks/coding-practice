/*
url: https://leetcode.cn/problems/number-of-islands/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution200 {
public:
    // 用dfs
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        int ans = 0;
        vector<vector<int>> vis(m, vector<int>(n, false));
        auto dfs = [&](auto& dfs, int i, int j) {
            if (!legal(i, j)) return;

            if (grid[i][j] == '1' && !vis[i][j]) {
                vis[i][j] = true;
                for (auto [dx, dy] : directions) {
                    dfs(dfs, i + dx, j + dy);
                }
            }
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !vis[i][j]) {
                    ans++;
                    dfs(dfs, i, j);
                }
            }
        }

        return ans;
    }

    // 用bfs
    int numIslands_implementation2(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<vector<int>> vis(m, vector<int>(n, false));
        auto bfs = [&](int i, int j) {
            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = true;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx;
                    int yy = y + dy;
                    if (legal(xx, yy) && grid[xx][yy] == '1' && !vis[xx][yy]) {
                        vis[xx][yy] = true;
                        q.push({xx, yy});
                    }
                }
            }
        };

        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !vis[i][j]) {
                    ans++;
                    bfs(i, j);
                }
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution200 solu;
    cout << solu.numIslands(*new vector<vector<char>>{
                {'1','1','1','1','0'},
                {'1','1','0','1','0'},
                {'1','1','0','0','0'},
                {'0','0','0','0','0'}}) << endl;

    cout << solu.numIslands_implementation2(*new vector<vector<char>>{
                {'1','1','1','1','0'},
                {'1','1','0','1','0'},
                {'1','1','0','0','0'},
                {'0','0','0','0','0'}}) << endl;
    return 0;
}