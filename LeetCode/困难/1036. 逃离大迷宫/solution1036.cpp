/*
url: https://leetcode.cn/problems/escape-a-large-maze/
参考: https://leetcode.cn/problems/escape-a-large-maze/solutions/1203946/gong-shui-san-xie-bfs-gei-ding-zhang-ai-8w63o/
      https://leetcode.cn/problems/escape-a-large-maze/solutions/1203052/tao-chi-da-mi-gong-by-leetcode-solution-qxhz/
标签: 【算法题单】网格图, 离散化, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

struct Pair_hash {
    long long operator()(const pair<int, int>& p) const {
        return p.first * 1e6 + p.second;
    }
};

class Solution1036 {
public:
    // 看起来像A*算法，但是blocked = [], source = [0,0], target = [999999,999999]这个用例就能看出来，A*会遍历1e6 * 1e6的范围，并不是走一条线过去，超时
    bool isEscapePossible_tle(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        int m = 1e6, n = 1e6;
        unordered_set<pair<int, int>, Pair_hash> st;
        for (auto &v : blocked) st.insert({v[0], v[1]});
        int sx = source[0], sy = source[1];
        int tx = target[0], ty = target[1];
        
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n && !st.count({i, j});
        };
        auto manh_dis = [](int x1, int y1, int x2, int y2) { // 启发函数，曼哈顿距离
            return abs(x1 - x2) + abs(y1 - y2);
        };

        unordered_map<pair<int, int>, int, Pair_hash> dis;

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        pq.push({manh_dis(sx, sy, tx, ty), sx, sy}); // 题目保证source, target非障碍点
        dis[{sx, sy}] = 0;

        while (!pq.empty()) {
            // cout << pq.size() << endl;
            auto [f, x, y] = pq.top(); pq.pop();
            if (x == tx && y == ty) return true;
            int g = f - manh_dis(x, y, tx, ty);
            if (!dis.count({x, y}) || g > dis[{x, y}]) continue;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                int gg = g + 1;
                if (legal(xx, yy) && (!dis.count({xx, yy}) || gg < dis[{xx, yy}])) {
                    pq.push({gg + manh_dis(xx, yy, tx, ty), xx, yy});
                    dis[{xx, yy}] = gg;
                }
            }
        }
        return false;
    }

    /* (sx, sy) 和 (tx, ty) 不连通，说明二者之一被围起来了。0 <= blocked.length <= 200
    所以围点的圈不会很大。但是：1. 可以借助边界围 2. 两点可能在包围圈内连通。不知道具体怎么写。
    参考宫水三叶题解，
    用 <= 200 个block，能围住的空格最多多少个？
    把点放在边角，然后block以斜边的形式围，最多围 1 + 2 + ... + (n - 1) = n(n - 1) / 2 个空格。
    反过来，只要从一个点bfs，发现了超过这个数的空格，就说明这个点没有被围住。
    分别检查source和target是否被围住，若都没被围住，或者二者在一个圈里，则二者互通。

    时间复杂度 O(MX)
    */
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        int m = 1e6, n = 1e6;
        unordered_set<pair<int, int>, Pair_hash> st;
        for (auto &v : blocked) st.insert({v[0], v[1]});
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n && !st.count({i, j}); // 检查越界与是否是障碍
        };

        int MX = blocked.size() * (blocked.size() - 1) / 2;

        // bfs(s)是否能找到足够多的空格，或者直接找到t
        auto bfs = [&](vector<int>& a, vector<int>& b) {
            queue<pair<int, int>> q;
            unordered_set<pair<int, int>, Pair_hash> vis;
            q.push({a[0], a[1]});
            vis.insert({a[0], a[1]});
            while (!q.empty() && vis.size() <= MX) {
                auto [x, y] = q.front(); q.pop();
                if (x == b[0] && y == b[1]) return true; // 直接找到了另一个点
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && !vis.count({xx, yy})) {
                        q.push({xx, yy});
                        vis.insert({xx, yy});
                    }
                }
            }
            return vis.size() > MX;
        };

        return bfs(source, target) && bfs(target, source);
    }

    // 宫水三叶题解解法二，图很稀疏，对大棋盘进行离散化，然后直接bfs
    /* 注意离散化的缝隙保留问题，
    首先，如果原本图是：
            s 1 t
            0 0 0
            1 1 1
        不保留缝隙，直接按+1离散化的话图会变成：
            s 1 t
            1 1 1
        变成无法相连了
    所以，原本的缝隙，离散化之后idx要+2，保留缝隙特征

    此外，第一个有值的行号，如果其 == 0，则其不能往上走，但如果其 >= 1，那么上面还有一行，是可以往上走的，
    所以，第一个有值的行号，不能单纯映射为0。

    官方题解的总结：“如果两个行坐标本身相邻，那么在离散化之后它们也必须相邻。如果它们不相邻，可以把它们之间间隔的若干行直接「压缩」成一行，即行坐标相差 2”
    离散化时，要有-1和1e6这两个障碍行的坐标，它们是边界，这样离散化之后第一个有值的行号往上的缝隙也能判断。

    最后得到的grid，四周代表障碍，[1, mr) × [1, mc) 的区域才是原映射区域，0行、mr行、0列，mc列是原边界。
    */
    bool isEscapePossible_implementation2(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        int M = 2 * (blocked.size() + 4); // 假设blocked横坐标各不相同，加上source和target，网格上下边界，最多blocked.size() + 4个值。乘2是为了可能需要留出缝隙
        int N = 2 * (blocked.size() + 4);
        vector<vector<int>> grid(M, vector<int>(N));
        vector<pair<int, int>> nodes;
        int EDGE = 1e6;
        nodes.push_back({-1, -1});
        nodes.push_back({EDGE, EDGE}); // 边界
        for (auto& v : blocked) nodes.push_back({v[0], v[1]});
        nodes.push_back({source[0], source[1]});
        nodes.push_back({target[0], target[1]});
        
        sort(nodes.begin(), nodes.end()); // 把横坐标排序
        // 坐标值域大，个数小，离散化，把坐标全替换成编号
        int sx, sy, tx, ty;
        int mr, mc;
        for (int i = 0, idx = 0; i < nodes.size();) { // 分组循环，编号横坐标
            int start = i;
            int cur = nodes[start].first; // 这一轮要映射的横坐标值
            for (i++; i < nodes.size() && nodes[i].first == nodes[i - 1].first; i++);
            // [start, i)
            if (nodes[start].first == source[0]) sx = idx;
            if (nodes[start].first == target[0]) tx = idx;
            for (int k = start; k < i; k++) {
                nodes[k].first = idx;
                mr = idx;
            }
            // nodes[i].first - cur 为下一个横坐标与当前横坐标的距离，注意cur不能用node[i - 1].first替代，上面已经改了node[i - 1].first
            if (i < nodes.size() && nodes[i].first - cur == 1) idx += 1;
            else idx += 2;
            // 注意这里离散化 +1 +2 的处理，原本的缝隙，离散化之后idx要+2，保留缝隙特征
        }

        sort(nodes.begin(), nodes.end(), [&](pair<int, int> x, pair<int, int> y) { // 把纵坐标排序
            return x.second < y.second;
        });
        for (int i = 0, idx = 0; i < nodes.size();) { // 纵坐标
            int start = i;
            int cur = nodes[start].second; // 这一轮要映射的纵坐标值
            for (i++; i < nodes.size() && nodes[i].second == nodes[i - 1].second; i++);
            // [start, i)
            if (nodes[start].second == source[1]) sy = idx;
            if (nodes[start].second == target[1]) ty = idx;
            for (int k = start; k < i; k++) {
                nodes[k].second = idx;
                mc = idx;
            }
            if (i < nodes.size() && nodes[i].second - cur == 1) idx += 1;
            else idx += 2;
        }
        for (auto [x, y] : nodes) {
            if (!(x == sx && y == sy || x == tx && y == ty)) { // 障碍
                grid[x][y] = 1;
            }
        }

        // grid的 (0, mr) × (0, mc) 区域是原映射区域，0行、mr行、0列，mc列是原边界

        // bfs，看(sx, sy)能否到达(tx, ty)
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 < i && i < mr && 0 < j && j < mc && grid[i][j] != 1; // 检查越界与是否是障碍
        };
        queue<pair<int, int>> q;
        vector<vector<int>> vis(grid.size(), vector<int>(grid[0].size()));
        q.push({sx, sy});
        vis[sx][sy] = true;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (x == tx && y == ty) return true;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (legal(xx, yy) && !vis[xx][yy]) {
                    q.push({xx, yy});
                    vis[xx][yy] = true;
                }
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution1036 solu;
    
    // cout << solu.isEscapePossible_tle(*new vector<vector<int>>{}, *new vector<int>{0, 0}, *new vector<int>{999,99}) << endl;
    
    cout << solu.isEscapePossible(*new vector<vector<int>>{{0,1},{1,0}}, *new vector<int>{0, 0}, *new vector<int>{0, 2}) << endl;

    cout << solu.isEscapePossible_implementation2(*new vector<vector<int>>{{0,1},{1,0}}, *new vector<int>{0, 0}, *new vector<int>{0, 2}) << endl;
    return 0;
}