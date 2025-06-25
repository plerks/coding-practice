/*
url: https://leetcode.cn/problems/maximum-number-of-fish-in-a-grid/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2658 {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<vector<int>> vis(m, vector<int>(n, false));
        auto bfs = [&](int i, int j) -> int {
            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = true;
            int ans = 0;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                ans += grid[x][y];
                for (auto [dx, dy] : directions) {
                    int xx = x + dx;
                    int yy = y + dy;
                    if (legal(xx, yy) && grid[xx][yy] > 0 && !vis[xx][yy]) {
                        vis[xx][yy] = true;
                        q.push({xx, yy});
                    }
                }
            }
            return ans;
        };

        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0 && !vis[i][j]) {
                    ans = max(ans, bfs(i, j));
                }
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2658 solu;
    cout << solu.findMaxFish(*new vector<vector<int>>{{0,2,1,0},{4,0,0,3},{1,0,0,4},{0,3,2,0}}) << endl;
    return 0;
}