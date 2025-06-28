/*
url: https://leetcode.cn/problems/contain-virus/
相关: LeetCode463. 岛屿的周长, LeetCode1034. 边界着色
标签: 【算法题单】网格图, 连通分量边界
*/

#include <bits/stdc++.h>

using namespace std;

struct pair_hash {
    int operator()(const pair<int, int>& p) const {
        // 1 <= m, n <= 50
        return p.first * 50 + p.second;
    }
};

class Solution749 {
public:
    int containVirus(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int ans = 0;
        while (true) { // 最多 m + n 天要模拟
            // node为此轮威胁最大的连通分量中的一个点，t为此轮威胁最大的连通分量的隔离所需防火墙数
            // 注意威胁最大是指会感染最多的点，而非需要装的栅栏最多
            auto [virus, virus_edge, cnt] = get_max(grid);
            if (cnt == 0) return ans;
            ans += cnt;

            // 装防火墙（把围起来的区域变成2）
            defend(grid, virus);

            // 扩散一天
            spread(grid);
        }
        return -1;
    }

    // 找此轮威胁最大的连通分量中的一个点，和所需防火墙数
    tuple<unordered_set<pair<int, int>, pair_hash>, unordered_set<pair<int, int>, pair_hash>, int> get_max(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<int>> vis(m, vector<int>(n));

        unordered_set<pair<int, int>, pair_hash> virus; // 威胁最大的连通分量的病毒点
        unordered_set<pair<int, int>, pair_hash> virus_edge; // 相应会感染的正常点
        int cnt = 0; // virus的区域的边界长度

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    // bfs
                    unordered_set<pair<int, int>, pair_hash> area1; // 连通分量的病毒点
                    unordered_set<pair<int, int>, pair_hash> area2; // 相应会感染的正常点
                    int t = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vis[i][j] = true;
                    area1.insert({i, j});
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        for (auto [dx, dy] : directions) {
                            int nx = x + dx, ny = y + dy;
                            if (legal(nx, ny) && grid[nx][ny] == 0) {
                                t++; // 所需防火墙数，相当于求分量边界
                                area2.insert({nx, ny});
                            }
                            if (legal(nx, ny) && grid[nx][ny] == 1 && !vis[nx][ny]) {
                                q.push({nx, ny});
                                vis[nx][ny] = true;
                                area1.insert({nx, ny});
                            }
                        }
                    }
                    if (area2.size() > virus_edge.size()) {
                        cnt = t;
                        virus = std::move(area1);
                        virus_edge = std::move(area2);
                    }
                }
            }
        }

        return tuple{virus, virus_edge, cnt};
    }

    // 把node所在的连通分量全变成2
    void defend(vector<vector<int>>& grid, unordered_set<pair<int, int>, pair_hash>& area) {
        for (auto [x, y] : area) grid[x][y] = 2;
    }

    // 扩散一天
    void spread(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        queue<pair<int, int>> q;
        vector<vector<int>> vis(m, vector<int>(n));
        // 多源bfs，只扩散一天
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    vis[i][j] = true;
                }
            }
        }
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (legal(nx, ny) && grid[nx][ny] == 0) {
                    grid[nx][ny] = 1;
                }
            }
        }
    }
};

int main(int argc, char const *argv[]) {
    Solution749 solu;
    cout << solu.containVirus(*new vector<vector<int>>{{0,1,0,0,0,0,0,1},{0,1,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0}}) << endl;
    return 0;
}