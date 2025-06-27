/*
url: https://leetcode.cn/problems/shortest-path-in-a-grid-with-obstacles-elimination/
参考: https://leetcode.cn/problems/shortest-path-in-a-grid-with-obstacles-elimination/solutions/101739/wang-ge-zhong-de-zui-duan-lu-jing-by-leetcode-solu/
相关: LeetCode909. 蛇梯棋, LeetCode1210. 穿过迷宫的最少移动次数, LeetCode675. 为高尔夫比赛砍树
标签: 【算法题单】网格图, [mark], [special]
*/
#include <bits/stdc++.h>

using namespace std;

struct Info {
    int x;
    int y;
    int r; // 剩余消除次数
};

class Solution1293 {
public:
    /* 参考官方题解，这题解法很特别，有点优先队列Dijkstra的感觉。
    遍历时加上一个维度，用 (x, y, r) 表示一个搜索状态，r为剩余的消除障碍次数。

    时间复杂度 O(m * n * min(k, m + n))
    */
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        k = min(k, m + n - 3); // grid[0][0] == grid[m-1][n-1] == 0，最短路径最多m + n - 3次消除障碍
        if (m == 1 && n == 1) return 0; // 1 <= m, n <= 40

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<vector<int>>> vis(m, vector<vector<int>>(n, vector<int>(k + 1)));
        queue<Info> q;
        q.push({0, 0, k});
        vis[0][0][k] = true;
        
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            level++;
            for (int i = 0; i < size; i++) {
                auto [x, y, r] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (xx == m - 1 && yy == n - 1) return level;
                    if (!legal(xx, yy)) continue;
                    
                    // 要把邻居入队的两种情况
                    if (grid[xx][yy] == 1 && r >= 1 && !vis[xx][yy][r - 1]) { // 是障碍物
                        q.push({xx, yy, r - 1});
                        vis[xx][yy][r - 1] = true;
                    }
                    else if (grid[xx][yy] == 0 && !vis[xx][yy][r]) {
                        q.push({xx, yy, r});
                        vis[xx][yy][r] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1293 solu;
    cout << solu.shortestPath(*new vector<vector<int>>{{0,0,0},{1,1,0},{0,0,0},{0,1,1},{0,0,0}}, 1) << endl;
    cout << solu.shortestPath(*new vector<vector<int>>{{0}}, 1) << endl;
    return 0;
}