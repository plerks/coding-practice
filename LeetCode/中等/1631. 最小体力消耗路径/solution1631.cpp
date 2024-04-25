/*
url: https://leetcode.cn/problems/path-with-minimum-effort/description/
LeetCode参考: https://leetcode.cn/problems/path-with-minimum-effort/solutions/581109/zui-xiao-ti-li-xiao-hao-lu-jing-by-leetc-3q2j/
其它参考: https://oi-wiki.org/search/heuristic/
相关: LeetCode2258. 逃离火灾, LeetCode1976. 到达目的地的方案数, LeetCode797. 所有可能的路径, 典型问题/有序范围内的二分查找, 典型问题/最短路径问题/最短路径-Dijkstra-使用优先队列, 典型问题/并查集
标签: 二分查找, 并查集, Dijkstra算法, A*算法
*/

#include <bits/stdc++.h>

using namespace std;

// C++，这里UnionFind必须定义在Solution1631前
class UnionFind {
public:
    vector<int> parent;
    vector<int> size;

    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // C++ union是关键字！这里不能像Java里直接叫union()，改叫unite()
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return; // x, y已经相连，不要做下面的操作
        if (size[rx] < size[ry]) {
            parent[rx] = ry;
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int getSize(int x) {
        return size[x];
    }
};

// 这题很特别，有典型例题的价值
class Solution1631 {
public:
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int ans = INT_MAX;

    /* 暴力枚举所有路径，5 / 75 个通过的测试用例。最后执行的用例是
    [[4,3,4,10,5,5,9,2],[10,8,2,10,9,7,5,6],[5,8,10,10,10,7,4,2],[5,1,3,1,1,3,1,9],[6,4,10,6,10,9,4,6]]
    这里的代码和`LeetCode1976. 到达目的地的方案数`countPaths_exceed_time_limit()相同。
    这个用例在本地测试要几秒才能出结果，说明对这个输入规模暴力枚举就已经很慢了。
    */
    // 这里的暴力dfs代码与`LeetCode1976. 到达目的地的方案数`，`LeetCode797. 所有可能的路径`中的相同
    int minimumEffortPath_exceed_time_limit(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> visited(m, vector<int>(n));
        dfs(0, 0, heights, visited, 0);
        return ans;
    }

    void dfs(int i, int j, vector<vector<int>>& heights, vector<vector<int>>& visited, int maxDiff) {
        int m = heights.size(), n = heights[0].size();
        if (i == m - 1 && j == n - 1) {
            ans = min(ans, maxDiff);
            return;
        }
        visited[i][j] = true;
        for (auto& direction : directions) {
            int x = i + direction[0];
            int y = j + direction[1];
            if (x >= 0 && x < m && y >= 0 && y < n && !visited[x][y]) {
                int t = max(maxDiff, abs(heights[i][j] - heights[x][y]));
                dfs(x, y, heights, visited, t);
            }
        }
        // 为了后续还可以通过其它路径到这个点
        visited[i][j] = false;
    }

    // 错误解法，这里不是子问题，不能dp，到达一个点的最佳路径不只由左上部分决定，可能从下面来
    int minimumEffortPath_wrong(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        dp[0][0] = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (auto& direction : directions) {
                    int x = i + direction[0];
                    int y = j + direction[1];
                    if (x >= 0 && x < m && y >= 0 && y < n) {
                        dp[i][j] = min(dp[i][j], max(dp[x][y], abs(heights[i][j] - heights[x][y])));
                    }
                }
            }
        }
        return dp[m - 1][n - 1];
    }

    /* 官方题解解法一，二分查找。将矩阵看成图，图的边为相邻格子的高度之差绝对值。于是问题变为，找(0,0)到(m-1,n-1)的
    路径，其中其经过的边的边权的最大值最小。
    再将问题转化为判定性问题，即是否有(0,0)到(m-1,n-1)的路径，其经过的边的边权的最大值不超过x？
    然后就变成对x的二分查找，而判定可达由dfs或bfs都可完成，这里用bfs，search时只走<=x的边即可剪枝。
    */
    // 这个二分解法和`LeetCode2258. 逃离火灾`很像
    int minimumEffortPath(vector<vector<int>>& heights) {
        // 1 <= heights[i][j] <= 10^6，每条边不会超过10^6 - 1
        int left = 0, right = 1000000 - 1; // C++不能像Java一样用_分隔(不能写1_000_000)，C++14可以用'分隔(1'000'000)，不过C++写int right = 1e6 - 1会自动转换，不用像Java写int right = (int)1e6 - 1
        // 区间呈[否...是]变化，搜索第一个是，转化为搜索最后一个否+1
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(heights, mid)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left;
    }

    bool check(vector<vector<int>>& heights, int mid) {
        int m = heights.size(), n = heights[0].size();
        int N = max(m, n); // 用进制表示法
        queue<int> q;
        vector<vector<int>> visited(m, vector<int>(n));
        q.push(0 * N + 0);
        visited[0][0] = true;
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            int j = p % N;
            int i = (p / N) % N;
            for (auto &direction : directions) {
                int x = i + direction[0];
                int y = j + direction[1];
                if (x >= 0 && x < m && y >= 0 && y < n && !visited[x][y] && abs(heights[i][j] - heights[x][y]) <= mid) {
                    visited[x][y] = true;
                    q.push(x * N + y);
                }
            }
        }
        return visited[m - 1][n - 1];
    }

    // 官方题解解法二，用并查集，把边按权值排序，逐步加入边直到(0, 0)和(m - 1, n - 1)连通。过程有点像Kruskal算法。
    int minimumEffortPath_implementation2(vector<vector<int>>& heights) {
        vector<tuple<int, int, int>> edges;
        int m = heights.size(), n = heights[0].size();
        // 节点编号从左往右，从上往下编，id = i * n + j，类似进制表示法又有点不一样
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 每个点负责把自己上方和左边的边加入vector，也可以每个点负责右方和下方
                long long id = i * n + j;
                if (i > 0) {
                    edges.emplace_back(id, id - n, abs(heights[i][j] - heights[i - 1][j]));
                }
                if (j > 0) {
                    edges.emplace_back(id, id - 1, abs(heights[i][j] - heights[i][j - 1]));
                }
            }
        }
        sort(edges.begin(), edges.end(), [](tuple<int, int, int> x, tuple<int, int, int> y) {
            return get<2>(x) < get<2>(y);
        });
        UnionFind uf(m * n);
        for (auto &edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);
            uf.unite(u, v);
            if (uf.find(0) == uf.find(m * n - 1)) {
                return w;
            }
        }
        return 0;
    }

    /* 官方题解解法三，可以当作最短路径问题，使用Dijkstra算法，这题的最短路径的定义不是经过的边权的和，而是经过的边权的最大值。
    但按官方题解所说，这仍可以使用Dijkstra算法："Dijkstra算法本质上是一种启发式搜索算法，它是A*算法在启发函数h≡0时的特殊情况"
    官方题解有证明这里可以用Dijkstra算法求。
    */
    // 待做: 弄懂A*算法和官方题解中关于这里可以用Dijkstra算法求的证明
    int minimumEffortPath_implementation3(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        auto comparator = [](tuple<int, int, int> x, tuple<int, int, int> y) {
            if (get<2>(x) < get<2>(y)) return false;
            return true;
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(comparator)> q(comparator);
        vector<int> distance(m * n, INT_MAX);
        distance[0] = 0;
        vector<int> visited(m * n);
        q.emplace(0, 0, 0); // 三个值分别代表横纵坐标和最短距离
        while (!q.empty()) {
            auto t = q.top();
            int i = get<0>(t), j = get<1>(t), d = get<2>(t);
            q.pop();
            if (visited[i * n + j]) continue;
            if (i * n + j == m * n - 1) break; // 此时(m - 1, n - 1)的最短距离已经算出
            for (auto &direction : directions) {
                int x = i + direction[0];
                int y = j + direction[1];
                if (x >= 0 && x < m && y >= 0 && y < n) {
                    if (max(d, abs(heights[i][j] - heights[x][y])) < distance[x * n + y]) {
                        distance[x * n + y] = max(d, abs(heights[i][j] - heights[x][y]));
                        q.emplace(x, y, distance[x * n + y]);
                    }
                }
            }
            visited[i * n + j] = true;
        }
        return distance[m * n - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution1631 solu;
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    vector<vector<int>> heights2 = {{4,3,4,10,5,5,9,2},{10,8,2,10,9,7,5,6},{5,8,10,10,10,7,4,2},{5,1,3,1,1,3,1,9},{6,4,10,6,10,9,4,6}};
    // cout << solu.minimumEffortPath_exceed_time_limit(heights2) << endl;
    Solution1631 solu2;
    vector<vector<int>> heights3 = {{1,2,1,1,1},{1,2,1,2,1},{1,2,1,2,1},{1,2,1,2,1},{1,1,1,2,1}};
    // cout << solu.minimumEffortPath_wrong(heights3) << endl;
    cout << solu.minimumEffortPath(heights) << endl;
    cout << solu.minimumEffortPath_implementation2(heights) << endl;
    cout << solu.minimumEffortPath_implementation3(heights) << endl;
    return 0;
}
