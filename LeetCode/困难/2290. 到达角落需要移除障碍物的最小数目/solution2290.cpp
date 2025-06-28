/*
url: https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
参考: https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/solutions/1524710/0-1-bfs-by-endlesscheng-4pjt/
相关: LeetCode1368. 使网格图至少有一条有效路径的最小代价, LeetCode1824. 最少侧跳次数
标签: 【算法题单】网格图, 0-1 Dijkstra, A*算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2290 {
public:
    // 用Dijkstra，时间复杂度O(mn * log(mn))，301ms
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX)); // 到达(x, y)的最小移除障碍次数
        vector<vector<int>> vis(m, vector<int>(n));
        auto comparator = [&](tuple<int, int, int> x, tuple<int, int, int> y) {
            if (get<0>(x) != get<0>(y)) return get<0>(x) > get<0>(y);
            return false; // 只关心c的排序，其它都返回false，这样 x !< y，y !< x，就会认为相等
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(comparator)> pq(comparator); // (cnt, x, y)，cnt为移除次数
        // grid[0][0] == grid[m - 1][n - 1] == 0，不用判断起点终点为障碍
        pq.push({0, 0, 0});
        while (!pq.empty()) {
            auto [c, x, y] = pq.top(); pq.pop();
            if (vis[x][y]) continue;
            vis[x][y] = true;
            if (x == m - 1 && y == n - 1) return c; // 终点第一次出队时即为到终点的最短距离
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (legal(xx, yy)) {
                    // 这里再判断一个 && !vis[xx][yy] 没用，可以删掉。没访问过自然要落到 c < dis[xx][yy] 来检查决定是否入队。而若访问过，不靠 !vis，c < dis[xx][yy] 也一定能拦住。靠 c < dis[xx][yy] 来判断就够了
                    if (grid[xx][yy] == 0 && !vis[xx][yy] && c < dis[xx][yy]) {
                        pq.push({c, xx, yy});
                        dis[xx][yy] = c;
                    }
                    else if (grid[xx][yy] == 1 && !vis[xx][yy] && c + 1 < dis[xx][yy]) {
                        pq.push({c + 1, xx, yy});
                        dis[xx][yy] = c + 1;
                    }
                }
            }
        }
        return -1;
    }

    /* 参考灵茶题解，这题确实是需要用Dijkstra，但是由于边权只会出现0和1，不需要用堆，用个双端队列即可维护住堆序(甚至是个全序)。
    由于边权只有0和1，所以队列中优先级的差值最多为1，于是，遇到0边权就插入队首，遇到1边权就插入队尾，这样堆序性仍然是满足的。
    举例来说，x x ... x + 1 x + 1，x出队，若与邻居的边权为0，插入队首即可；若与邻居的边权为1，插入队尾(优先级为x + 1)，前方亦
    不会有比 x + 1 大的元素。
    于是，通过双端队列就维护住了堆序。这种情况下的优先队列Dijkstra算法时间复杂度降到了O(e)，而非O(eloge)。
    灵茶题解中称为 0-1 BFS，但是我感觉更习惯叫 0-1 Dijkstra，因为本质是Dijkstra，只是边权为 0-1，可以优化优先队列的使用，
    用 双端队列 + 判断插入位置 来代替 优先队列。

    时间复杂度O(mn)，用时115ms
    */
    int minimumObstacles_implementation2(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX)); // 到达(x, y)的最小移除障碍次数
        deque<tuple<int, int, int>> dq; // (cnt, x, y)，cnt为移除次数
        // grid[0][0] == grid[m - 1][n - 1] == 0，不用判断起点终点为障碍
        dq.push_front({0, 0, 0});
        dis[0][0] = 0;
        while (!dq.empty()) {
            auto [c, x, y] = dq.front(); dq.pop_front();
            if (x == m - 1 && y == n - 1) return dis[x][y];
            if (c > dis[x][y]) continue;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (legal(xx, yy)) {
                    int w = grid[xx][yy]; // 若grid[xx][yy]为障碍1，则边权为1，否则为0
                    if (c + w < dis[xx][yy]) {
                        dis[xx][yy] = c + w;
                        if (w == 0) dq.push_front({c + w, xx, yy});
                        else dq.push_back({c + w, xx, yy});
                    }
                }
            }
        }
        return -1;
    }

    // 用A*算法来写下，不过有了估值函数，虽然边权为0-1，不能像minimumObstacles_implementation2()一样用双端队列来代替优先队列了
    // 启发式搜索，原本以为效率不怎么样，因为这题启发函数h单纯是0，没什么启发性，但是还是比优先队列Dijkstra用时少，用时252ms。看来是A*算法的dfs成分起了作用
    int minimumObstacles_implementation3(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX)); // 到达(x, y)的最小实际移除障碍次数(实际距离g)
        auto heuristic = [](int x1, int y1, int x2, int y2) { // 曼哈顿距离
            return 0;
            // “我们往往会直接使用「理论最小步数」来作为启发式函数。”，这里不是曼哈顿距离了，不满足可接受性，得不到正解。得是返回0，假设一路无障碍
        };

        auto comparator = [&](tuple<int, int, int> x, tuple<int, int, int> y) {
            if (get<0>(x) != get<0>(y)) return get<0>(x) > get<0>(y);
            return false; // 只关心c的排序，其它都返回false，这样 x !< y，y !< x，就会认为相等
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(comparator)> pq(comparator); // (f, x, y)，f为估计移除次数(估计距离f)
        // grid[0][0] == grid[m - 1][n - 1] == 0，不用判断起点终点为障碍
        pq.push({heuristic(0, 0, m - 1, n - 1), 0, 0});
        while (!pq.empty()) {
            auto [f, x, y] = pq.top(); pq.pop();
            int g = f - heuristic(x, y, m - 1, n - 1);
            if (x == m - 1 && y == n - 1) return g;
            if (g > dis[x][y]) continue;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (legal(xx, yy)) {
                    int w = grid[xx][yy]; // 若grid[xx][yy]为障碍1，则边权为1，否则为0
                    int gg = g + w;
                    if (gg < dis[xx][yy]) {
                        pq.push({gg + heuristic(xx, yy, m - 1, n - 1), xx, yy});
                        dis[xx][yy] = gg;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2290 solu;
    cout << solu.minimumObstacles(*new vector<vector<int>>{{0,1,1},{1,1,0},{1,1,0}}) << endl;

    cout << solu.minimumObstacles_implementation2(*new vector<vector<int>>{{0,1,1},{1,1,0},{1,1,0}}) << endl;

    cout << solu.minimumObstacles_implementation3(*new vector<vector<int>>{{0,1,1},{1,1,0},{1,1,0}}) << endl;
    cout << solu.minimumObstacles_implementation3(*new vector<vector<int>>{{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}}) << endl;
    return 0;
}