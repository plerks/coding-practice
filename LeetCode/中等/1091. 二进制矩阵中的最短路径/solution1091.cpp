/*
url: https://leetcode.cn/problems/shortest-path-in-binary-matrix/
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1091 {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        const vector<pair<int, int>> directions = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < n && 0 <= j && j < n;
        };

        vector<vector<bool>> vis(n, vector<bool>(n));
        queue<pair<int, int>> q;
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) return -1;

        q.push({0, 0});
        vis[0][0] = true;
        int level = 0;
        while (!q.empty()) {
            int sz = q.size(); // level为这批节点的层号
            for (int i = 0; i < sz; i++) {
                auto [x, y] = q.front();
                q.pop();
                if (x == n - 1 && y == n - 1) {
                    return level + 1;
                }
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && !vis[xx][yy] && grid[xx][yy] == 0) {
                        q.push({xx, yy});
                        vis[xx][yy] = true;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1091 solu;
    // cout << solu.shortestPathBinaryMatrix(*new vector<vector<int>>{{0,0,0},{1,1,0},{1,1,0}}) << endl;
    // cout << solu.shortestPathBinaryMatrix(*new vector<vector<int>>{{0,0,0},{1,1,0},{1,1,1}}) << endl;
    cout << solu.shortestPathBinaryMatrix(*new vector<vector<int>>{{0}}) << endl;
    return 0;
}