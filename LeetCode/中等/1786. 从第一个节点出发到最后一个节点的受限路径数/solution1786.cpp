/*
url: https://leetcode.cn/problems/number-of-restricted-paths-from-first-to-last-node/
参考: https://leetcode.cn/problems/number-of-restricted-paths-from-first-to-last-node/solutions/646430/xiang-jie-dui-you-hua-dijkstra-dong-tai-i6j0d/
标签: 【题单】图论算法, 拓扑序dp
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1786 {
public:
    // 我的解法，错误的原因在于，一个节点的 cnt[node] 可能在“被弹出之后”还会继续增加，导致漏算，不能这样 bfs ，不用 vis 也不行，会重复计算
    int countRestrictedPaths_wa(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> g(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u - 1].push_back({v - 1, w}); // 节点编号从 1 开始
            g[v - 1].push_back({u - 1, w});
        }

        // 先把最短距离算出来
        const int MOD = 1e9 + 7;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq; // (距离，节点)
        vector<long long> dis(n, LLONG_MAX); // 各个节点到 n - 1 节点的距离
        pq.push({0, n - 1});
        dis[n - 1] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dis[node]) continue;
            for (auto [next, w] : g[node]) {
                if (d + w < dis[next]) {
                    dis[next] = d + w;
                    pq.push({d + w, next});
                }
            }
        }

        // 再跑一遍，直接去搜索
        queue<int> q;
        vector<long long> cnt(n, 0); // cnt[i] 表示从 0 到 i 节点的受限路径数
        vector<int> vis(n);
        cnt[0] = 1;
        q.push(0); // 节点
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (auto [next, w] : g[node]) {
                if (dis[next] < dis[node]) {
                    cnt[next] = (cnt[next] + cnt[node]) % MOD;
                    q.push(next);
                    vis[next] = true;
                }
            }
        }

        return cnt[n - 1];
    }

    // 参考宫水三叶题解，正确思路为按照距离从大到小的顺序来dp计算，也即按拓扑序来dp
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> g(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u - 1].push_back({v - 1, w}); // 节点编号从 1 开始
            g[v - 1].push_back({u - 1, w});
        }

        // 先把最短距离算出来
        const int MOD = 1e9 + 7;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq; // (距离，节点)
        vector<long long> dis(n, LLONG_MAX); // 各个节点到 n - 1 节点的距离
        pq.push({0, n - 1});
        dis[n - 1] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dis[node]) continue;
            for (auto [next, w] : g[node]) {
                if (d + w < dis[next]) {
                    dis[next] = d + w;
                    pq.push({d + w, next});
                }
            }
        }

        // 按拓扑序 dp
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int x, int y) { // 从大到小
            return dis[x] > dis[y];
        });
        vector<int> cnt(n);
        cnt[0] = 1; // 路径要从节点 0 出发
        for (int i = 0; i < n; i++) {
            int node = idx[i];
            for (auto [next, _] : g[node]) {
                if (dis[node] > dis[next]) {
                    cnt[next] = (cnt[next] + cnt[node]) % MOD;
                }
            }
        }

        return cnt[n - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution1786 solu;
    cout << solu.countRestrictedPaths(5, *new vector<vector<int>>{{1,2,3},{1,3,3},{2,3,1},{1,4,2},{5,2,2},{3,5,1},{5,4,10}}) << endl;
    return 0;
}