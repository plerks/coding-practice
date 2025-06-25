/*
url: https://leetcode.cn/problems/check-if-there-is-a-valid-path-in-a-grid/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1391 {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // 每种街道的两个点
        enum {UP, DOWN, LEFT, RIGHT};
        // grid的街道类型编号从1开始，这里{-1, -1}是哨兵
        vector<pair<int, int>> street = {{-1, -1}, {LEFT, RIGHT}, {UP, DOWN}, {LEFT, DOWN}, {DOWN, RIGHT}, {LEFT, UP}, {UP, RIGHT}};

        auto contains = [&](int type, int dir) { // type类型的街道有没有dir类型的点
            return street[type].first == dir || street[type].second == dir;
        };

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        vector<vector<int>> vis(m, vector<int>(n, false));
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto [dx, dy] : directions) {
                int xx = x + dx;
                int yy = y + dy;
                if (0 <= xx && xx < m && 0 <= yy && yy < n && !vis[xx][yy]) {
                    int type1 = grid[x][y];
                    int type2 = grid[xx][yy];
                    if (pair{xx, yy} == pair{x - 1, y}) { // (x, y)往上走
                        if (contains(type1, UP) && contains(type2, DOWN)) {
                            vis[xx][yy] = true;
                            q.push({xx, yy});
                        }
                    }
                    else if (pair{xx, yy} == pair{x + 1, y}) { // 下
                        if (contains(type1, DOWN) && contains(type2, UP)) {
                            vis[xx][yy] = true;
                            q.push({xx, yy});
                        }
                    }
                    else if (pair{xx, yy} == pair{x, y - 1}) { // 左
                        if (contains(type1, LEFT) && contains(type2, RIGHT)) {
                            vis[xx][yy] = true;
                            q.push({xx, yy});
                        }
                    }
                    else if (pair{xx, yy} == pair{x, y + 1}) { // 右
                        if (contains(type1, RIGHT) && contains(type2, LEFT)) {
                            vis[xx][yy] = true;
                            q.push({xx, yy});
                        }
                    }
                }
            }
        }
        
        return vis[m - 1][n - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution1391 solu;
    cout << solu.hasValidPath(*new vector<vector<int>>{{2,4,3},{6,5,2}}) << endl;
    cout << solu.hasValidPath(*new vector<vector<int>>{{2,6}}) << endl;
    cout << solu.hasValidPath(*new vector<vector<int>>{{1,2},{2,1}}) << endl;
    return 0;
}