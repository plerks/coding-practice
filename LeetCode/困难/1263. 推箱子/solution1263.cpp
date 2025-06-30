/*
url: https://leetcode.cn/problems/minimum-moves-to-move-a-box-to-their-target-location/
标签: 【算法题单】网格图, 状态压缩, 状压bfs
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1263 {
public:
    // 状压bfs
    // 要的是最小推箱子次数，但是是按bfs枚举人的移动步数来搜索的，所以运行用时较高，1926ms，能通过
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int sx, sy; // 人的开始位置
        int bx, by; // 箱子开始位置，此题箱子只有一个
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (grid[i][j] == 'B') {
                    bx = i;
                    by = j;
                }
            }
        }

        auto hash = [&](int sx, int sy, int bx, int by, int cnt) {
            // 1 <= m, n <= 20，一个int就能记录状态
            constexpr int N = 21;
            return sx * N * N * N * N + sy * N * N * N + bx * N * N + by * N + cnt;
        };

        constexpr int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n && grid[i][j] != '#';
        };

        queue<tuple<int, int, int, int, int>> q; // 人坐标 箱子坐标 推箱子次数
        unordered_set<int> vis;
        q.push({sx, sy, bx, by, 0});
        vis.insert(hash(sx, sy, bx, by, 0));
        int ans = INT_MAX;
        for (int level = 0; !q.empty(); level++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, a, b, cnt] = q.front(); q.pop();
                if (legal(a, b) && grid[a][b] == 'T') ans = min(ans, cnt); // 人在走，但是要的是最小的推箱子次数，要枚举完
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    // 如果人的移动走到了箱子的位置上，则是一次推箱子
                    if (xx == a && yy == b) {
                        int aa = a + dx, bb = b + dy;
                        if (legal(aa, bb) && !vis.count(hash(xx, yy, aa, bb, cnt))) {
                            q.push({xx, yy, aa, bb, cnt + 1});
                            vis.insert(hash(xx, yy, aa, bb, cnt + 1));
                        }
                    }
                    else {
                        if (legal(xx, yy) && !vis.count(hash(xx, yy, a, b, cnt))) {
                            q.push({xx, yy, a, b, cnt});
                            vis.insert(hash(xx, yy, a, b, cnt));
                        }
                    }
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }

    // 改成优先队列，优先拿cnt小的状态出来，作为种子继续搜索
    // 846ms，通过
    // 这里Dijkstra的vis修改位置写错了，应该是出队修改为visited，而不是入队，写成了bfs的了。
    // 而且vis只该考虑状态信息，不该把开销cnt也记录进去了，
    // 这样写，没发挥出优先队列的剪枝作用，相同的(sx, sy, bx, by, cnt)没重复算，但是更大的cnt也在拿来算
    int minPushBox_wrong_implementation(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int sx, sy; // 人的开始位置
        int bx, by; // 箱子开始位置，此题箱子只有一个
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (grid[i][j] == 'B') {
                    bx = i;
                    by = j;
                }
            }
        }

        auto hash = [&](int sx, int sy, int bx, int by, int cnt) {
            // 1 <= m, n <= 20，一个int就能记录状态
            constexpr int N = 21;
            return sx * N * N * N * N + sy * N * N * N + bx * N * N + by * N + cnt;
        };

        constexpr int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n && grid[i][j] != '#';
        };

        using Info = tuple<int, int, int, int, int>;
        auto comparator = [&](Info &x, Info &y) {
            return get<4>(x) > get<4>(y);
        };
        priority_queue<Info, vector<Info>, decltype(comparator)> pq(comparator); // 人坐标 箱子坐标 推箱子次数

        unordered_set<int> vis;
        pq.push({sx, sy, bx, by, 0});
        vis.insert(hash(sx, sy, bx, by, 0));
        for (int level = 0; !pq.empty(); level++) {
            int size = pq.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, a, b, cnt] = pq.top(); pq.pop();
                if (legal(a, b) && grid[a][b] == 'T') return cnt; // 第一次找到就可以直接返回最小推箱子次数
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    // 如果人的移动走到了箱子的位置上，则是一次推箱子
                    if (xx == a && yy == b) {
                        int aa = a + dx, bb = b + dy;
                        if (legal(aa, bb) && !vis.count(hash(xx, yy, aa, bb, cnt))) {
                            pq.push({xx, yy, aa, bb, cnt + 1});
                            vis.insert(hash(xx, yy, aa, bb, cnt + 1));
                        }
                    }
                    else {
                        if (legal(xx, yy) && !vis.count(hash(xx, yy, a, b, cnt))) {
                            pq.push({xx, yy, a, b, cnt});
                            vis.insert(hash(xx, yy, a, b, cnt));
                        }
                    }
                }
            }
        }
        return -1;
    }

    // 正确的Dijkstra写法，158ms
    int minPushBox_implementation2(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int sx, sy; // 人的开始位置
        int bx, by; // 箱子开始位置，此题箱子只有一个
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (grid[i][j] == 'B') {
                    bx = i;
                    by = j;
                }
            }
        }

        auto hash = [&](int sx, int sy, int bx, int by) {
            // 1 <= m, n <= 20，一个int就能记录状态
            constexpr int N = 21;
            return sx * N * N * N + sy * N * N + bx * N + by;
        };

        constexpr int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n && grid[i][j] != '#';
        };

        using Info = tuple<int, int, int, int, int>;
        auto comparator = [&](Info &x, Info &y) {
            return get<4>(x) > get<4>(y);
        };
        priority_queue<Info, vector<Info>, decltype(comparator)> pq(comparator); // 人坐标 箱子坐标 推箱子次数

        unordered_set<int> vis;
        unordered_map<int, int> dis; // 到达(x, y, a, b)状态的最小开销（推箱子次数）
        pq.push({sx, sy, bx, by, 0});
        // 注意别在这里写 vis.insert(hash(sx, sy, bx, by)); Dijkstra是出队时标记为visited，不是入队
        dis[hash(sx, sy, bx, by)] = 0;
        for (int level = 0; !pq.empty(); level++) { // 这里是Dijkstra，这里这样分层没有含义，不过能运行而已
            int size = pq.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, a, b, cnt] = pq.top(); pq.pop();
                if (vis.count(hash(x, y, a, b))) continue;
                vis.insert(hash(x, y, a, b));
                if (legal(a, b) && grid[a][b] == 'T') return cnt; // 第一次找到就可以直接返回最小推箱子次数
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    // 如果人的移动走到了箱子的位置上，则是一次推箱子
                    if (xx == a && yy == b) {
                        int aa = a + dx, bb = b + dy;
                        int new_state = hash(xx, yy, aa, bb);
                        if (legal(aa, bb) && (!dis.count(new_state) || cnt + 1 < dis[new_state])) {
                            pq.push({xx, yy, aa, bb, cnt + 1});
                            dis[new_state] = cnt + 1;
                        }
                    }
                    else {
                        int new_state = hash(xx, yy, a, b);
                        if (legal(xx, yy) && (!dis.count(new_state) || cnt < dis[new_state])) {
                            pq.push({xx, yy, a, b, cnt});
                            dis[new_state] = cnt;
                        }
                    }
                }
            }
        }
        return -1;
    }

    // 参考官方题解，还可以用 0-1 Dijkstra，没想起来这个。115ms
    int minPushBox_implementation3(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int sx, sy; // 人的开始位置
        int bx, by; // 箱子开始位置，此题箱子只有一个
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (grid[i][j] == 'B') {
                    bx = i;
                    by = j;
                }
            }
        }

        auto hash = [&](int sx, int sy, int bx, int by) {
            // 1 <= m, n <= 20，一个int就能记录状态
            constexpr int N = 21;
            return sx * N * N * N + sy * N * N + bx * N + by;
        };

        constexpr int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n && grid[i][j] != '#';
        };

        using Info = tuple<int, int, int, int, int>; // 人坐标 箱子坐标 推箱子次数
        deque<Info> pq;

        unordered_set<int> vis;
        unordered_map<int, int> dis; // 到达(x, y, a, b)状态的最小开销（推箱子次数）
        pq.push_front({sx, sy, bx, by, 0});
        // 注意别在这里写 vis.insert(hash(sx, sy, bx, by)); Dijkstra是出队时标记为visited，不是入队
        dis[hash(sx, sy, bx, by)] = 0;
        while (!pq.empty()) {
            auto [x, y, a, b, cnt] = pq.front(); pq.pop_front();
            if (vis.count(hash(x, y, a, b))) continue;
            vis.insert(hash(x, y, a, b));
            if (legal(a, b) && grid[a][b] == 'T') return cnt; // 第一次找到就可以直接返回最小推箱子次数
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                // 如果人的移动走到了箱子的位置上，则是一次推箱子
                if (xx == a && yy == b) {
                    int aa = a + dx, bb = b + dy;
                    int new_state = hash(xx, yy, aa, bb);
                    if (legal(aa, bb) && (!dis.count(new_state) || cnt + 1 < dis[new_state])) {
                        pq.push_back({xx, yy, aa, bb, cnt + 1});
                        dis[new_state] = cnt + 1;
                    }
                }
                else {
                    int new_state = hash(xx, yy, a, b);
                    if (legal(xx, yy) && (!dis.count(new_state) || cnt < dis[new_state])) {
                        pq.push_front({xx, yy, a, b, cnt});
                        dis[new_state] = cnt;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1263 solu;
    cout << solu.minPushBox(*new vector<vector<char>>{{'#','#','#','#','#','#'},
                                                        {'#','T','#','#','#','#'},
                                                        {'#','.','.','B','.','#'},
                                                        {'#','.','#','#','.','#'},
                                                        {'#','.','.','.','S','#'},
                                                        {'#','#','#','#','#','#'}}) << endl;

    cout << solu.minPushBox_implementation2(*new vector<vector<char>>{{'#','#','#','#','#','#'},
                                                        {'#','T','#','#','#','#'},
                                                        {'#','.','.','B','.','#'},
                                                        {'#','.','#','#','.','#'},
                                                        {'#','.','.','.','S','#'},
                                                        {'#','#','#','#','#','#'}}) << endl;

    cout << solu.minPushBox_implementation3(*new vector<vector<char>>{{'#','#','#','#','#','#'},
                                                        {'#','T','#','#','#','#'},
                                                        {'#','.','.','B','.','#'},
                                                        {'#','.','#','#','.','#'},
                                                        {'#','.','.','.','S','#'},
                                                        {'#','#','#','#','#','#'}}) << endl;
    return 0;
}