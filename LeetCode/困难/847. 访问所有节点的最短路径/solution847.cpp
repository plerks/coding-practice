/*
url: https://leetcode.cn/problems/shortest-path-visiting-all-nodes/
参考: https://leetcode.cn/problems/shortest-path-visiting-all-nodes/solutions/918311/fang-wen-suo-you-jie-dian-de-zui-duan-lu-mqc2/
相关: LeetCode231. 2 的幂
标签: 【题单】图论算法, 旅行商问题, 多源bfs
*/

#include <bits/stdc++.h>

using namespace std;

class Solution847 {
public:
    // 我想的是二分 + check的方式

    // 官方题解解法一，bfs，为了搜索经过所有点的最短路径，当前搜索状态要设计为 (当前节点，已经过节点，已走距离)
    // 此外，不用枚举从每个点为起点 bfs 一遍，多源 bfs 就行

    /* 时间复杂度：
        遍历所有状态的时间为 O(n * 2^n)
        对于边的遍历，对于一个固定的 mask ，(0, mask), (1, mask), ... , (n - 1, mask) 对邻居的遍历刚好是图的所有边，
        所以对边的遍历的总时间为 2^n * e
       总时间复杂度 O(2^n * (n + e))
    */
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        // 1 <= n <= 12，已经过节点可以用一个 mask 压缩
        queue<pair<int, int>> q; // 距离可以用 level 记，不用记在搜索状态中
        vector<vector<int>> vis(n, vector<int>(1 << n));
        for (int i = 0; i < n; i++) {
            q.push({i, 1 << i});
            vis[i][1 << i] = true;
        }

        // bfs
        int level = 1;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto [cur, state] = q.front(); q.pop();
                for (int next : graph[cur]) {
                    int next_state = state | (1 << next);
                    if (next_state == (1 << n) - 1) return level;
                    if (!vis[next][next_state]) {
                        q.push({next, next_state});
                        vis[next][next_state] = true;
                    }
                }
            }
            level++;
        }

        return 0; // 空图返回 0
    }

    // 官方题解解法二，dp，经过所有节点的路径，每次下一步的"目标"节点最终一定是 n 个节点的一个排列(中间可能重复经过同一节点，但其不是下一个"目标")，每步之间走最短路径
    /* 用 f[u][mask] 表示现在到达 u ，且已经过节点状态为 mask 的最短路径，
    那么 f[u][mask] = min{f[v][mask \ u] + d(v, u)}
    base case 为 mask 里面只有一个 1
    */
    // 时间复杂度 O(n^2 * 2^n)
    int shortestPathLength_implementation2(vector<vector<int>>& graph) {
        int n = graph.size();
        // 先用 floyd 求最短路
        vector<vector<int>> d(n, vector<int>(n, INT_MAX / 2));
        for (int i = 0; i < n; i++) for (int j : graph[i]) d[i][j] = 1;
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }

        // dp
        vector<vector<int>> f(n, vector<int>(1 << n, INT_MAX / 2));
        for (int mask = 1; mask < (1 << n); mask++) {
            if ((mask & (mask - 1)) == 0) { // LeetCode231. 2 的幂
                int u = __builtin_ctz(mask);
                f[u][mask] = 0;
            }
            else {
                for (int u = 0; u < n; u++) {
                    if ((mask >> u) & 1) {
                        for (int v = 0; v < n; v++) {
                            if ((mask >> v) & 1) {
                                f[u][mask] = min(f[u][mask], f[v][mask ^ (1 << u)] + d[v][u]);
                            }
                        }
                    }
                }
            }
        }

        int ans = INT_MAX;
        for (int u = 0; u < n; u++) {
            ans = min(ans, f[u][(1 << n) - 1]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution847 solu;
    cout << solu.shortestPathLength(*new vector<vector<int>>{{1,2,3},{0},{0},{0}}) << endl;
    cout << solu.shortestPathLength_implementation2(*new vector<vector<int>>{{1,2,3},{0},{0},{0}}) << endl;
    return 0;
}