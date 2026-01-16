/*
url: https://leetcode.cn/problems/minimum-weighted-subgraph-with-the-required-paths/
参考: https://leetcode.cn/problems/minimum-weighted-subgraph-with-the-required-paths/solutions/1332967/by-endlesscheng-2mxm/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2203 {
public:
    /* 参考灵茶题解，看这个最小带权子图的性质，从两个点出发到dest，只要二者合到了一起，后面就一定不会再分开，
    所以，答案形状应该是个三岔口（Y形，也可能是一条线或者V形）。枚举交点即可。
    */
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int, int>>> g(n), rg(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u].push_back({v, w});
            rg[v].push_back({u, w}); // 反图，所有点到dest的最短路径通过对rg计算以dest为源的最短路径得到
        }

        auto d1 = dijkstra(g, src1);
        auto d2 = dijkstra(g, src2);
        auto rd3 = dijkstra(rg, dest);
        long long ans = INT64_MAX;
        for (int i = 0; i < n; i++) {
            if (d1[i] != INT64_MAX && d2[i] != INT64_MAX && rd3[i] != INT64_MAX) {
                ans = min(ans, d1[i] + d2[i] + rd3[i]);
            }
        }
        return ans == INT64_MAX ? -1 : ans;
    }

    vector<long long> dijkstra(vector<vector<pair<int, int>>>& g, int src) {
        int n = g.size();
        // (距离，节点)
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        vector<long long> dis(n, LLONG_MAX);
        pq.push({0, src});
        dis[src] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dis[node]) continue;
            for (auto [next, w] : g[node]) {
                if (d + w < dis[next]) {
                    dis[next] = d + w;
                    pq.push({dis[next], next});
                }
            }
        }
        return dis;
    }
};

int main(int argc, char const *argv[]) {
    Solution2203 solu;
    // cout << solu.minimumWeight(6, *new vector<vector<int>>{{0,2,2},{0,5,6},{1,0,3},{1,4,5},{2,1,1},{2,3,3},{2,3,4},{3,4,2},{4,5,1}}, 0, 1, 5) << endl;
    cout << solu.minimumWeight(3, *new vector<vector<int>>{{0,1,1},{2,1,1}}, 0, 1, 2) << endl;
    return 0;
}