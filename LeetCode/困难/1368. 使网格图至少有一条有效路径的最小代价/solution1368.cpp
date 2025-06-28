/*
url: https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
相关: LeetCode2290. 到达角落需要移除障碍物的最小数目, LeetCode1824. 最少侧跳次数
标签: 【算法题单】网格图, 0-1 Dijkstra
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1368 {
public:
    // 时间复杂度O(mn * log(mn))
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 右左下上，对应grid的1234
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX));
        deque<tuple<int, int, int>> dq; // (cost, x, y)
        dq.push_back({0, 0, 0});
        dis[0][0] = 0;
        while (!dq.empty()) {
            auto [c, x, y] = dq.front(); dq.pop_front();
            if (c > dis[x][y]) continue;
            if (x == m - 1 && y == n - 1) return dis[m - 1][n - 1];
            for (int i = 0; i < directions.size(); i++) {
                auto [dx, dy] = directions[i];
                int xx = x + dx, yy = y + dy;
                int w = i == grid[x][y] - 1 ? 0 : 1; // 边权
                if (legal(xx, yy)) {
                    if (c + w < dis[xx][yy]) {
                        if (w == 0) dq.push_front({c + w, xx, yy});
                        else dq.push_back({c + w, xx, yy});
                        dis[xx][yy] = c + w;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1368 solu;
    cout << solu.minCost(*new vector<vector<int>>{{1,1,1,1},{2,2,2,2},{1,1,1,1},{2,2,2,2}}) << endl;
    return 0;
}