/*
url: https://leetcode.cn/problems/minimum-moves-to-reach-target-with-rotations/
相关: LeetCode909. 蛇梯棋, LeetCode1293. 网格中的最短路径, LeetCode675. 为高尔夫比赛砍树
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

struct Snake {
    pair<int, int> tail;
    pair<int, int> head;
};

/* bool operator<(Snake s1, Snake s2) {
    if (s1.head != s2.head) return s1.head < s2.head;
    return s1.tail < s2.tail;
} */

class Solution1210 {
public:
    // 和 LeetCode909. 蛇梯棋 类似，有优先队列Dijkstra的感觉，不过Dijkstra算法算是bfs在带权图上的推广，所以也不奇怪
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size(); // grid为方阵

        auto legal = [&](int i, int j) {
            return 0 <= i && i < n && 0 <= j && j < n && grid[i][j] != 1; // 这里检测了非障碍物
        };
        auto clock_wise = [&](Snake& s) -> Snake { // 顺时针转
            return {s.tail, pair{s.head.first + 1, s.head.second - 1}};
        };
        auto c_clock_wise = [&](Snake& s) -> Snake { // 逆时针转
            return {s.tail, pair{s.head.first - 1, s.head.second + 1}};
        };
        auto is_horizontal = [&](Snake& s) -> bool { // 蛇是否水平
            return s.tail.first == s.head.first;
        };
        auto is_vertical = [&](Snake& s) -> bool { // 蛇是否垂直
            return s.tail.second == s.head.second;
        };
        auto hash = [&](const Snake& s) -> int {
            int N = 101; // 2 <= n <= 100
            return s.tail.first * N * N * N + s.tail.second * N * N + s.head.first * N + s.head.second;
        };

        unordered_set<int> vis;
        queue<Snake> q;
        q.push({{0, 0}, {0, 1}});
        vis.insert(hash({{0, 0}, {0, 1}}));
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            level++; // 这一轮要 **入队** 的节点的深度
            for (int _ = 0; _ < size; _++) {
                Snake s = q.front(); q.pop();
                if (s.tail == pair{n - 1, n - 2} && s.head == pair{n - 1, n - 1}) return level - 1; // 注意这里是level - 1，s是上一轮入栈的
                // 向右
                {
                    Snake t = s; t.tail.second++; t.head.second++;
                    if (legal(t.head.first, t.head.second) && legal(t.tail.first, t.tail.second) && !vis.count(hash(t))) {
                        q.push(t);
                        vis.insert(hash(t));
                    }
                }
                // 向下
                {
                    Snake t = s; t.tail.first++; t.head.first++;
                    if (legal(t.head.first, t.head.second) && legal(t.tail.first, t.tail.second) && !vis.count(hash(t))) {
                        q.push(t);
                        vis.insert(hash(t));
                    }
                }
                // 顺时针转
                if (is_horizontal(s)) {
                    Snake t = clock_wise(s);
                    // grid[s.head.first + 1][s.head.second - 1] != 1 是转的时候不能被右下那个点卡住
                    if (legal(t.head.first, t.head.second) && grid[s.head.first + 1][s.head.second] != 1 && !vis.count(hash(t))) {
                        q.push(t);
                        vis.insert(hash(t));
                    }
                }
                // 逆时针转
                if (is_vertical(s)) {
                    Snake t = c_clock_wise(s);
                    if (legal(t.head.first, t.head.second) && grid[s.head.first][s.head.second + 1] != 1 && !vis.count(hash(t))) {
                        q.push(t);
                        vis.insert(hash(t));
                    }
                }
            }
            int debug = 1; // 在这里断下来时，q中的所有节点的层数为level
        }
        return -1;
    }

    /* 简化代码，具体见灵茶题解，把蛇的状态用三元组 (x, y, s) 表示，(x, y)代表 **蛇尾** 坐标，s代表水平(0)还是竖直方向(1)。
    于是，3种变化就是：constexpr int DIRS[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    每次，对于一个DIRS[i]，如何计算新蛇尾？：xx = x + d[0], yy = y + d[1], s ^= d[2]
    对于蛇尾状态 (x, y, s)，如何计算蛇头坐标？蛇尾(x, y)对应的蛇头坐标为(x + s, y + (s ^ 1))。
    这样就能避免一堆判断，写出简洁的代码了。
    */
    int minimumMoves_implementation2(vector<vector<int>>& grid) {
        int n = grid.size();

        const vector<tuple<int, int, int>> DIRS = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // 3种移动方式，向下，向右，旋转

        vector<vector<vector<int>>> vis(n, vector<vector<int>>(n, vector<int>(2)));
        queue<tuple<int, int, int>> qu;
        qu.push({0, 0, 0});
        for (int level = 1; !qu.empty(); level++) {
            int size = qu.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, s] = qu.front(); qu.pop(); // (x, y)为当前蛇尾坐标，s为蛇姿态（水平/竖直）
                int x2 = x + s, y2 = y + (s ^ 1); // (x2, y2)为当前蛇头坐标
                for (auto [d0, d1, d2] : DIRS) { // 此次行动动作
                    int p = x + d0, q = y + d1, t = s ^ d2; // (p, q, r)为新蛇尾状态
                    int p2 = p + t, q2 = q + (t ^ 1); // (p2, q2)为新蛇头
                    // 蛇可以以水平姿态往下移动，所以(p, q),(p2, q2)都要检查不走到障碍上
                    if (p2 < n && q2 < n && !vis[p][q][t] && grid[p][q] == 0 && grid[p2][q2] == 0
                            && (d2 == 0 || grid[p + 1][q + 1] == 0)) { // d2 == 0 || grid[p + 1][q + 1] == 0 是保证，若此次动作是旋转(d2为1)，则右下角非障碍
                        if (p == n - 1 && q == n - 2) return level; // 蛇尾在这里，蛇头一定在(n - 1, n - 1)
                        qu.push({p, q, t});
                        vis[p][q][t] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1210 solu;
    cout << solu.minimumMoves(*new vector<vector<int>>{{0,0,0,0,0,1},
                                                        {1,1,0,0,1,0},
                                                        {0,0,0,0,1,1},
                                                        {0,0,1,0,1,0},
                                                        {0,1,1,0,0,0},
                                                        {0,1,1,0,0,0}}) << endl;

    cout << solu.minimumMoves(*new vector<vector<int>>{{0,0,1,1,1,1},
                                                        {0,0,0,0,1,1},
                                                        {1,1,0,0,0,1},
                                                        {1,1,1,0,0,1},
                                                        {1,1,1,0,0,1},
                                                        {1,1,1,0,0,0}}) << endl;
    
    cout << solu.minimumMoves_implementation2(*new vector<vector<int>>{{0,0,0,0,0,1},
                                                        {1,1,0,0,1,0},
                                                        {0,0,0,0,1,1},
                                                        {0,0,1,0,1,0},
                                                        {0,1,1,0,0,0},
                                                        {0,1,1,0,0,0}}) << endl;

    cout << solu.minimumMoves_implementation2(*new vector<vector<int>>{{0,0,1,1,1,1},
                                                        {0,0,0,0,1,1},
                                                        {1,1,0,0,0,1},
                                                        {1,1,1,0,0,1},
                                                        {1,1,1,0,0,1},
                                                        {1,1,1,0,0,0}}) << endl;
    return 0;
}