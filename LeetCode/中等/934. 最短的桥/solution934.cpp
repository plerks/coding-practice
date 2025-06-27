/*
url: https://leetcode.cn/problems/shortest-bridge/
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution934 {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < n && 0 <= j && j < n;
        };
        vector<vector<int>> vis(n, vector<int>(n, false));
        queue<pair<int, int>> island1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    queue<pair<int, int>> q;
                    vector<vector<int>> t_vis(n, vector<int>(n, false));
                    q.push({i, j});
                    island1.push({i, j});
                    t_vis[i][j] = true;
                    vis[i][j] = true;
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        for (auto [dx, dy] : directions) {
                            int xx = x + dx, yy = y + dy;
                            if (legal(xx, yy) && !t_vis[xx][yy] && grid[xx][yy] == 1) {
                                q.push({xx, yy});
                                island1.push({xx, yy});
                                vis[xx][yy] = true;
                                t_vis[xx][yy] = true;
                            }
                        }
                    }
                    goto out;
                }
            }
        }
        out:

        int level = 0;
        while (!island1.empty()) {
            int sz = island1.size();
            level++;
            for (int i = 0; i < sz; i++) {
                auto [x, y] = island1.front(); island1.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && !vis[xx][yy]) {
                        if (grid[xx][yy] == 1) return level - 1; // 节点总数level + 1，中间节点数level - 1
                        island1.push({xx, yy});
                        vis[xx][yy] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution934 solu;
    cout << solu.shortestBridge(*new vector<vector<int>>{{0,1},{1,0}}) << endl;
    cout << solu.shortestBridge(*new vector<vector<int>>{{0,1,0},{0,0,0},{0,0,1}}) << endl;
    return 0;
}