/*
url: https://leetcode.cn/problems/map-of-highest-peak/
相关: LeetCode542. 01 矩阵
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1765 {
public:
    // 此题与 LeetCode542. 01 矩阵 相同
    vector<vector<int>> highestPeak(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n));
        queue<pair<int, int>> q;
        vector<vector<int>> vis(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    q.push({i, j}); // 多源bfs
                    vis[i][j] = true;
                }
            }
        }

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        int level = 0;
        
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto [x, y] = q.front(); q.pop();
                ans[x][y] = level;
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && !vis[xx][yy]) {
                        q.push({xx, yy});
                        vis[xx][yy] = true;
                    }
                }
            }
            level++;
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1765 solu;
    auto a = solu.highestPeak(*new vector<vector<int>>{{0,0,1},{1,0,0},{0,0,0}});
    return 0;
}