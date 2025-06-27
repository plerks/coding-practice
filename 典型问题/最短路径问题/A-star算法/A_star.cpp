/*
描述: A*算法通过启发式搜索，求单源单目标最短距离。具体笔记见 LeetCode/困难/675. 为高尔夫比赛砍树/A-star算法.md
相关: LeetCode675. 为高尔夫比赛砍树
*/
#include <bits/stdc++.h>

using namespace std;

class Astar {
public:
    // 网格路径问题，grid中0代表空格，1代表障碍物不能走，用A*算法求(rx, ry)到(sx, sy)的最短距离，若不能到达则返回-1
    // LeetCode/困难/675. 为高尔夫比赛砍树/solution675_implementation3.cpp 中的代码搬过来的
    int dis(vector<vector<int>> grid, int sx, int sy, int tx, int ty) {
        int m = grid.size(), n = grid[0].size();
        if (grid[sx][sy] == 1 || grid[tx][ty] == 1) return -1; // 起终点是障碍
        if (sx == tx && sy == ty) return 0; // 起点终点相同要特判
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto manh_dis = [](int x1, int y1, int x2, int y2) { // 启发函数，曼哈顿距离
            return abs(x1 - x2) + abs(y1 - y2);
        };
        
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX)); // 存一个节点当前遇到的最短实际距离d

        // (估计距离f, 坐标x, 坐标y)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({manh_dis(sx, sy, tx, ty), sx, sy});
        dis[sx][sy] = 0;
        while (!pq.empty()) {
            auto [f, x, y] = pq.top(); pq.pop();
            int d = f - manh_dis(x, y, tx, ty);
            if (d > dis[x][y]) continue; // 过时信息，不需计算
            if (x == tx && y == ty) return d; // 终点第一次出队，就是答案
            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy, nd = d + 1;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 1) continue;
                if (nd < dis[nx][ny]) { // 松弛邻居
                    // cout << "enqueue: " << "(" << nx << ", " << ny << ") " << nd << endl;
                    pq.push({nd + manh_dis(nx, ny, tx, ty), nx, ny});
                    dis[nx][ny] = nd;
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Astar a_star;
    vector<vector<int>> grid = {
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {1, 0, 1, 1}
    };
    cout << a_star.dis(grid, 0, 0, 2, 1) << endl;
    cout << a_star.dis(grid, 0, 0, 0, 3) << endl;
    return 0;
}