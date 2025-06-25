/*
url: https://leetcode.cn/problems/number-of-closed-islands/
相关: LeetCode130. 被围绕的区域
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1254 {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        // 联通分量的边界没遇到超出grid就是被水包围

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        
        vector<vector<int>> vis(m, vector<int>(n, false));

        auto bfs = [&](int i, int j) {
            if (vis[i][j]) return;
            queue<pair<int, int>> q;
            vis[i][j] = true;
            q.push({i, j});
            bool out = false; // 连通分量是否在边界上
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (!legal(xx, yy)) out = true;
                    else if (grid[xx][yy] == 0 && !vis[xx][yy]) { // 此题0代表陆地
                        vis[xx][yy] = true;
                        q.push({xx, yy});
                    }
                }
            }
            if (!out) {
                ans++;
            }
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) bfs(i, j);
            }
        }

        return ans;
    }

    /* 灵茶题解中有个处理方法是预先从第一行、最后一行、第一列和最后一列的所有0出发，dfs一遍，把这些的连通分量都变成1: 

        for (int i = 0; i < m; i++) {
            // 如果是第一行和最后一行，访问所有格子
            // 如果不是，只访问第一列和最后一列的格子
            int step = i == 0 || i == m - 1 ? 1 : n - 1;
            for (int j = 0; j < n; j += step)
                dfs(grid, i, j);
        }

       然后再找连通分量数就直接是答案了。
       这个遍历矩阵边界的写法比较简洁
    */ 
};

int main(int argc, char const *argv[]) {
    Solution1254 solu;
    cout << solu.closedIsland(*new vector<vector<int>>{{1,1,1,1,1,1,1,0},{1,0,0,0,0,1,1,0},{1,0,1,0,1,1,1,0},{1,0,0,0,0,1,0,1},{1,1,1,1,1,1,1,0}}) << endl;
    return 0;
}