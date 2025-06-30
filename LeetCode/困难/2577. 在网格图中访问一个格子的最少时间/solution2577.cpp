/*
url: https://leetcode.cn/problems/minimum-time-to-visit-a-cell-in-a-grid/
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2577 {
public:
    // 直接用 0-1 BFS
    int minimumTime_tle(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        using Info = tuple<int, int, int>; // (x, y, t)

        deque<Info> pq;
        set<Info> vis;
        pq.push_front({0, 0, 0});
        vis.insert({0, 0, 0});
        while (!pq.empty()) { // 每次找t最小的出来走，第一次走到(m - 1, n - 1)就是最短时间
            auto [x, y, t] = pq.front(); pq.pop_front();
            if (x == m - 1 && y == n - 1) return t;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                /* 这题格子有最早访问时间的限制，所以即使能以更短的时间到达(x, y)，t更大的状态也要入队进行搜索，
                时间复杂度会超，不是Dijkstra，而是 x * y * t 种状态的BFS
                */
                if (legal(xx, yy) && t + 1 >= grid[xx][yy] && !vis.count({xx, yy, t + 1})) {
                    pq.push_back({xx, yy, t + 1});
                    vis.insert({xx, yy, t + 1});
                }
            }
        }
        return -1;
    }

    /* 修改上面的解法，关键问题在于这题可以在格子间反复走以等待时机。当发现一个相邻格子暂时上不去，只要当前点不是0时刻的起点，
    就可以与上一个点反复横跳增加时间。如果后续到了起点(0, 0)，那么现在它有上一个节点，有反复横跳的能力了
    这样每次时间会+2，然后才走上那个相邻格子，有没有可能优化成刚好上去？否，去更多的节点在走回来，
    花费的时间一定是更大的偶数(去和回来)。
    有没有可能走别的路径可以刚好上去？(更晚到达(x, y)，可以刚好踏上(xx, yy))
    可能，但是上面的最短路最多浪费1时间，走别的路径，开销只要不同就要多 >=1 的时间，所以选最短路反复横跳能得到最优解

    时间复杂度O(mnlogmn)，运行用时176ms

    这题虽然磕磕绊绊，但是居然分析出来了
    */
    int minimumTime(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        using Info = tuple<int, int, int>; // (t, x, y)

        priority_queue<Info, vector<Info>, greater<Info>> pq;
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX));
        pq.push({0, 0, 0});
        dis[0][0] = 0;
        while (!pq.empty()) {
            auto [t, x, y] = pq.top(); pq.pop();
            if (x == m - 1 && y == n - 1) return t; // 一个点第一次出队时，一定为最小距离
            if (t > dis[x][y]) continue;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (!legal(xx, yy)) continue;
                // (0, 0)开始时没有反复横跳到其它点的机会，后续要给它补上，否则[[0,1,99],[3,99,99],[4,5,6]]这个用例就到不了3
                if (t + 1 >= grid[xx][yy] && (t + 1 < dis[xx][yy] || pair{xx, yy} == pair{0, 0})) {
                    pq.push({t + 1, xx, yy});
                    dis[xx][yy] = t + 1;
                }
                else if (t + 1 < grid[xx][yy] && t != 0) { // (x, y)非0时刻的起点就可以反复横跳
                    int tt = t + 1 + ((grid[xx][yy] - (t + 1)) + 1) / 2 * 2; // t要反复横跳的次数为 ⌈差的时间⌉ / 2
                    if (tt < dis[xx][yy]) {
                        pq.push({tt, xx, yy});
                        dis[xx][yy] = tt;
                    }
                }
            }
        }
        return -1;
    }

    /* 二分的解法，参考灵茶题解，能想到这题还可以用二分，也能想到check可能需要倒着检查，但是还是不知道check具体怎么写。
    反向传播，不需要考虑反复横跳，只需要考虑哪些点可以在t <= end_time时被访问，一步步倒着找点，这样不需要处理反复横跳。
    但是这样check有不严谨性，比方说我在t=1000时反向到达了(0, 0)，那正向来跳是否真的可以在t=1000时在(0, 0)位置呢？
    要先处理不能反复横跳的情况，只要一开始能反复横跳，那么后续一定能到任一个点（开场拖时间）。然后check的不严谨性就只会有1的差别，
    只需要最后将ans的奇偶性变成和m + n相同就行了（m + n是有效步，反复横跳一定为偶数，所以 ans 和 m + n 的奇偶性一定相同）。
    这个check有点怪，有点相当于只检查了连通性。

    时间复杂度O(mnlogU)，U为二分范围，运行用时508ms
    */
    int minimumTime_implementation2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        // 必须先检查开场能否反复横跳，2 <= m, n <= 1000。开场能反复横跳的话就可以到达任何地点
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;

        vector<vector<int>> vis(m, vector<int>(n)); // 用end_time来做标记，避免每次重新申请一个vis
        auto check = [&](int end_time) {
            if (grid[m - 1][n - 1] > end_time) return false; // 别忘了这个，不然没检查(m - 1, n - 1)，check的结果会有误
            queue<pair<int, int>> q;
            q.push({m - 1, n - 1});
            vis[m - 1][n - 1] = end_time;
            for (int t = end_time - 1; !q.empty(); t--) {
                int size = q.size();
                for (int _ = 0; _ < size; _++) {
                    auto [x, y] = q.front(); q.pop();
                    if (x == 0 && y == 0) return true;
                    for (auto [dx, dy] : directions) {
                        int xx = x + dx, yy = y + dy;
                        if (legal(xx, yy) && grid[xx][yy] <= t && vis[xx][yy] != end_time) {
                            q.push({xx, yy});
                            vis[xx][yy] = end_time;
                        }
                    }
                }
            }
            return false;
        };

        int mx = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mx = max(mx, grid[i][j]);
            }
        }

        // 找第一个可以的
        int left = 0, right = mx + m + n; // 这题可以在格子间反复走以等待时机，上界不止是 m * n，得 grid最大值 + m + n
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        int ans = left;
        return ans + (ans + m + n) % 2; // 把 ans 和 m + n 的奇偶性变成相同，而且是要变大
    }
};

int main(int argc, char const *argv[]) {
    Solution2577 solu;
    // cout << solu.minimumTime(*new vector<vector<int>>{{0,1,3,2},{5,1,2,5},{4,3,8,6}}) << endl;
    cout << solu.minimumTime(*new vector<vector<int>>{{0,1,99},{3,99,99},{4,5,6}}) << endl;

    cout << solu.minimumTime_implementation2(*new vector<vector<int>>{{0,1,99},{3,99,99},{4,5,6}}) << endl;
    return 0;
}