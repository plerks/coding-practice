/*
参考: https://leetcode.cn/problems/cut-off-trees-for-golf-event/solutions/1512294/by-ac_oier-ksth/
      https://leetcode.cn/problems/cut-off-trees-for-golf-event/solutions/1510776/wei-gao-er-fu-bi-sai-kan-shu-by-leetcode-rlrc/
相关: 典型问题/最短路径问题/A-star算法, LeetCode2290. 到达角落需要移除障碍物的最小数目
标签: A*算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution675 {
public:
    // 官方题解里用A*来求最短距离的写法，关于时间复杂度，按官方题解的说法：“启发式搜索不讨论时空复杂度。”
    // 运行时间 950ms
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size(), n = forest[0].size();
        vector<pair<int, int>> tree;
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            if (forest[i][j] > 1) { // 是树
                tree.push_back({i, j});
            }
        }
        sort(tree.begin(), tree.end(), [&](pair<int, int> node1, pair<int, int> node2) {
            return forest[node1.first][node1.second] < forest[node2.first][node2.second];
        });

        int ans = 0;
        int cx = 0, cy = 0; // 当前的位置
        for (int i = 0; i < tree.size(); i++) {
            int t = A_star(forest, cx, cy, tree[i].first, tree[i].second);
            if (t == -1) { // 无法到达
                return -1;
            }
            ans += t;
            cx = tree[i].first;
            cy = tree[i].second;
        }
        return ans;
    }

    // 返回 (sx, sy) 到 (tx, ty) 的最短距离，若无法到达返回-1
    int A_star(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        int m = forest.size(), n = forest[0].size();
        if (forest[sx][sy] == 0 || forest[tx][ty] == 0) return -1; // 起终点是障碍
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
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || forest[nx][ny] == 0) continue;
                if (nd < dis[nx][ny]) { // 松弛邻居
                    // cout << "enqueue: " << "(" << nx << ", " << ny << ") " << nd << endl;
                    pq.push({nd + manh_dis(nx, ny, tx, ty), nx, ny});
                    dis[nx][ny] = nd;
                }
            }
        }
        return -1;
    }

    // dis数组改成存一个节点当前遇到的最短估计距离f是等效的，运行时间也基本一致
    int A_star_implementation2(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        int m = forest.size(), n = forest[0].size();
        if (forest[sx][sy] == 0 || forest[tx][ty] == 0) return -1; // 起终点是障碍
        if (sx == tx && sy == ty) return 0; // 起点终点相同要特判
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto manh_dis = [](int x1, int y1, int x2, int y2) { // 曼哈顿距离
            return abs(x1 - x2) + abs(y1 - y2);
        };
        
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX)); // 存一个节点当前遇到的最短估计距离f

        // (估计距离f, 坐标x, 坐标y)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({manh_dis(sx, sy, tx, ty), sx, sy});
        dis[sx][sy] = manh_dis(sx, sy, tx, ty);
        while (!pq.empty()) {
            auto [f, x, y] = pq.top(); pq.pop();
            int d = f - manh_dis(x, y, tx, ty);
            if (f > dis[x][y]) continue; // 过时信息，不需计算
            if (x == tx && y == ty) return d; // 终点第一次出队，就是答案
            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy, nd = d + 1;
                int nf = nd + manh_dis(nx, ny, tx, ty);
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || forest[nx][ny] == 0) continue;
                if (nf < dis[nx][ny]) { // 松弛邻居
                    // cout << "enqueue: " << "(" << nx << ", " << ny << ") " << nd << endl;
                    pq.push({nd + manh_dis(nx, ny, tx, ty), nx, ny});
                    dis[nx][ny] = nf;
                }
            }
        }
        return -1;
    }
};

// 宫水三叶题解中还有个剪枝办法，用并查集预处理求出连通性，计算ans之前检查，tree中的所有点都要与(0, 0)连通，否则cutOffTree()直接返回-1

int main(int argc, char const *argv[]) {
    Solution675 solu;
    cout << solu.cutOffTree(*new vector<vector<int>>{{1,2,3},{0,0,4},{7,6,5}}) << endl;

    cout << "======" << endl;

    cout << solu.cutOffTree(*new vector<vector<int>>{{2,3,4},{0,0,5},{8,7,6}}) << endl;

    cout << "======" << endl;

    // 这个用例全是高树，把高度整成编号
    vector<vector<int>> forest = {{54581641,64080174,24346381,69107959},
                                  {86374198,61363882,68783324,79706116},
                                  {668150,92178815,89819108,94701471},
                                  {83920491,22724204,46281641,47531096},
                                  {89078499,18904913,25462145,60813308}};
    vector<int> nums;
    for (int i = 0; i < forest.size(); i++) {
        for (int j = 0; j < forest[0].size(); j++) {
            nums.push_back(forest[i][j]);
        }
    }
    sort(nums.begin(), nums.end());
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); i++) mp[nums[i]] = i + 2;
    for (int i = 0; i < forest.size(); i++) {
        for (int j = 0; j < forest[0].size(); j++) {
            forest[i][j] = mp[forest[i][j]];
        }
    }
    cout << solu.cutOffTree(forest) << endl;
    return 0;
}