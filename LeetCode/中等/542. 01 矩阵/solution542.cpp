/*
url: https://leetcode.cn/problems/01-matrix/
相关: LeetCode417. 太平洋大西洋水流问题, LeetCode1765. 地图中的最高点
标签: 【算法题单】网格图, 多源bfs
*/

#include <bits/stdc++.h>

using namespace std;

class Solution542 {
public:
    /* 超时的解法，从每个节点bfs一遍，虽然用了ans数组记忆化，当bfs到之前算出了距离的节点时就直接用之前的结果，
    但是时间复杂度仍然是O((mn)^2)。
    例如，遍历mat每个点的过程中，每个点的bfs都需要去完整遍历右下方的点，这样会是O((mn)^2)
    */
    vector<vector<int>> updateMatrix_tle(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0x3f3f3f3f));

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        
        auto bfs = [&](int i, int j) {
            vector<vector<int>> vis(m, vector<int>(n));
            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = true;
            int level = 0;
            while (!q.empty()) {
                int sz = q.size();
                level++;
                for (int k = 0; k < sz; k++) {
                    auto [x, y] = q.front(); q.pop();
                    for (auto& [dx, dy] : directions) {
                        int xx = x + dx, yy = y + dy;
                        if (legal(xx, yy)) {
                            if (mat[xx][yy] == 0) {
                                ans[i][j] = min(ans[i][j], level);
                            }
                            else { // mat[xx][yy] == 1
                                if (!vis[xx][yy] && ans[xx][yy] == 0x3f3f3f3f) {
                                    q.push({xx, yy});
                                    vis[xx][yy] = true;
                                }
                                else {
                                    ans[i][j] = min(ans[i][j], level + ans[xx][yy]); 
                                }
                            }
                        }
                    }
                }
            }
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) ans[i][j] = 0;
                else bfs(i, j);
            }
        }
        return ans;
    }

    // 看着好像要从每个点都bfs一遍，和 LeetCode417. 太平洋大西洋水流问题 是一样的，把终点作为bfs的种子，这里要多源bfs
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n));
        queue<pair<int, int>> q;
        vector<vector<int>> vis(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
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
    Solution542 solu;
    auto a = solu.updateMatrix_tle(*new vector<vector<int>>{{0,0,0},{0,1,0},{0,0,0}});
    auto b = solu.updateMatrix_tle(*new vector<vector<int>>{{0,0,0},{0,1,0},{1,1,1}});
    auto c = solu.updateMatrix_tle(*new vector<vector<int>>{{2,1,0,0,1,0,0,1,1,0},
                                                            {1,0,0,1,0,1,1,2,2,1},
                                                            {1,1,1,0,0,1,2,3,1,0},
                                                            {0,1,2,1,0,1,2,3,2,1},
                                                            {0,0,1,2,1,2,1,2,1,0},
                                                            {1,1,2,3,2,1,0,1,1,1},
                                                            {0,1,2,3,3,1,1,0,0,1},
                                                            {1,2,1,2,1,0,0,1,1,2},
                                                            {0,1,0,1,1,0,1,2,2,3},
                                                            {1,2,1,0,1,0,1,2,3,4}});
    
    auto d = solu.updateMatrix(*new vector<vector<int>>{{0,0,0},{0,1,0},{0,0,0}});
    auto e = solu.updateMatrix(*new vector<vector<int>>{{0,0,0},{0,1,0},{1,1,1}});
    auto f = solu.updateMatrix(*new vector<vector<int>>{{2,1,0,0,1,0,0,1,1,0},
                                                            {1,0,0,1,0,1,1,2,2,1},
                                                            {1,1,1,0,0,1,2,3,1,0},
                                                            {0,1,2,1,0,1,2,3,2,1},
                                                            {0,0,1,2,1,2,1,2,1,0},
                                                            {1,1,2,3,2,1,0,1,1,1},
                                                            {0,1,2,3,3,1,1,0,0,1},
                                                            {1,2,1,2,1,0,0,1,1,2},
                                                            {0,1,0,1,1,0,1,2,2,3},
                                                            {1,2,1,0,1,0,1,2,3,4}});
    return 0;
}