/*
url: https://leetcode.cn/problems/island-perimeter/
相关: LeetCode749. 隔离病毒, LeetCode1034. 边界着色
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution463 {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
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
            int ans = 0;
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx; int yy = y + dy;
                    if (!legal(xx, yy) || grid[xx][yy] == 0) ans++;
                    else {
                        if (vis[xx][yy]) continue;
                        vis[xx][yy] = true;
                        q.push({xx, yy});
                    }
                }
            }
            return ans;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return bfs(i, j);
                }
            }
        }

        return -1;
    }

    // 参考官方题解，上面写麻烦了，直接遍历每个点看四周即可
    int islandPerimeter_implementation2(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    for (auto [dx, dy] : directions) {
                        int ii = i + dx;
                        int jj = j + dy;
                        if (!legal(ii, jj) || grid[ii][jj] == 0) ans++;
                    }
                }
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution463 solu;
    cout << solu.islandPerimeter(*new vector<vector<int>>{{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}}) << endl;

    cout << solu.islandPerimeter_implementation2(*new vector<vector<int>>{{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}}) << endl;
    return 0;
}