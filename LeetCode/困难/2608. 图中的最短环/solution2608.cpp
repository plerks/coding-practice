/*
url: https://leetcode.cn/problems/shortest-cycle-in-a-graph/
参考: https://leetcode.cn/problems/shortest-cycle-in-a-graph/solutions/2203585/yi-tu-miao-dong-mei-ju-qi-dian-pao-bfspy-ntck/
      https://leetcode.cn/problems/shortest-cycle-in-a-graph/solutions/2203459/bfs-by-tsreaper-7pab/
      https://oi-wiki.org/graph/min-cycle/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

// 此题为无向图
class Solution2608 {
public:
    /* 错误的做法，先把树边求出来，发现跨边就意味着有环，然后求lca，通过depth求环长度。
    这种做法的错误之处在于，可能最小环是由多条跨边组成的，以下代码考虑不到这种情况。
    */
    int findShortestCycle_wa(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto& edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        vector<int> vis(n, -1);
        vector<int> parent(n, -1);
        vector<int> depth(n);

        int ans = INT_MAX;

        // 无向图的bfs找出树边，然后发现跨边的话，说明就是一个环
        auto bfs = [&](int i) {
            queue<int> q;
            q.push(i);
            vis[i] = i; // 用特异值 x 来表示 visited 状态
            depth[i] = 0;
            while (!q.empty()) {
                int x = q.front(); q.pop();
                for (int y : g[x]) {
                    if (vis[y] != i) { // !vis[y]
                        q.push(y);
                        vis[y] = i; // vis[y] = true
                        depth[y] = depth[x] + 1;
                        parent[y] = x;
                        if (depth[y] == -1) depth[y] = depth[x] + 1;
                    }
                    else {
                        // 无向图，x -> y -> x 的环要排除掉
                        if (parent[x] == y) continue;

                        auto get_lca = [&](int x, int y) {
                            while (depth[x] > depth[y]) x = parent[x];
                            while (depth[y] > depth[x]) y = parent[y];
                            while (x != y) {
                                x = parent[x];
                                y = parent[y];
                            }
                            return x;
                        };
                        int lca = get_lca(x, y);
                        ans = min(ans, depth[x] - depth[lca] + depth[y] - depth[lca] + 1);
                    }
                }
            }
            int debug = 1;
        };

        for (int i = 0; i < n; i++) {
            if (vis[i] == -1) { // 没访问过
                bfs(i);
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }

    /* 参考灵茶题解，
    从每个点出发做一次独立的bfs，找最小环。（枚举每个点作为环上一个点，做独立的多次bfs）

    时间复杂度 O(nm) ， m为edges长度，每次bfs花费O(m)时间

    参考灵茶题解：
    如果改成求最大环要怎么做？
    极端情况下，这会算出一个哈密顿回路，而它是 NP 完全问题，只能通过暴搜得到。
    */
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto& edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        
        int ans = INT_MAX;

        vector<int> depth(n);
        
        auto bfs = [&](int start) {
            fill(depth.begin(), depth.end(), -1);
            depth[start] = 0;
            queue<pair<int, int>> q; // (节点，节点父亲)
            q.push({start, -1});
            while (!q.empty()) {
                auto [x, fa] = q.front(); q.pop();
                for (int y : g[x]) {
                    if (depth[y] < 0) { // !vis[y]
                        q.push({y, x});
                        depth[y] = depth[x] + 1;
                    }
                    else if (y != fa) { // 跨边，且排除 x -> y -> x 的情况
                        ans = min(ans, depth[x] + depth[y] + 1);
                    }
                }
            }
        };

        for (int i = 0; i < n; i++) {
            bfs(i);
        }

        return ans == INT_MAX ? -1 : ans;
    }

    /* 也有枚举边的解法，枚举并删除一条边(u, v)，删除这条边之后用 bfs/Dijkstra 算法求(u, v)距离，
    二者相加就是环的长度。
    见[TsReaper题解](https://leetcode.cn/problems/shortest-cycle-in-a-graph/solutions/2203459/bfs-by-tsreaper-7pab/)
    与[oiwiki](https://oi-wiki.org/graph/min-cycle/)
    */
};

int main(int argc, char const *argv[]) {
    Solution2608 solu;
    
    // cout << solu.findShortestCycle_wa(6, *new vector<vector<int>>{{4,2},{5,1},{5,0},{0,3},{5,2},{1,4},{1,3},{3,4}}) << endl;
    
    cout << solu.findShortestCycle(7, *new vector<vector<int>>{{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}}) << endl;
    cout << solu.findShortestCycle(3, *new vector<vector<int>>{{1,0},{2,1}}) << endl;
    cout << solu.findShortestCycle(4, *new vector<vector<int>>{{1,2},{0,1},{3,2},{1,3}}) << endl;
    cout << solu.findShortestCycle(6, *new vector<vector<int>>{{4,2},{5,1},{5,0},{0,3},{5,2},{1,4},{1,3},{3,4}}) << endl;
    return 0;
}