/*
url: https://leetcode.cn/problems/rotting-oranges/
标签: 【算法题单】网格图, 多源bfs
*/

#include <bits/stdc++.h>

using namespace std;

class Solution994 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int cnt = 0;
        queue<pair<int, int>> q;
        vector<vector<int>> vis(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    cnt++;
                }
                if (grid[i][j] == 2) {
                    q.push({i, j});
                    vis[i][j] = true;
                }
            }
        }

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        
        int t = 0;
        if (cnt == 0) return t;
        while (!q.empty()) {
            if (cnt == 0) return t;
            t++;
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && !vis[xx][yy] && grid[xx][yy] == 1) {
                        cnt--;
                        q.push({xx, yy});
                        vis[xx][yy] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution994 solu;
    cout << solu.orangesRotting(*new vector<vector<int>>{{2,1,1},{1,1,0},{0,1,1}}) << endl;
    cout << solu.orangesRotting(*new vector<vector<int>>{{0}}) << endl;
    return 0;
}