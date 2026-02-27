/*
url: https://leetcode.cn/problems/min-cost-to-connect-all-points/
标签: 最小生成树
*/
#include <bits/stdc++.h>

using namespace std;

// 计算最小生成树的权值，若图不连通则返回 INT64_MAX
// 此题为稠密图，用朴素实现的 Prim ，时间复杂度 O(n^2)
long long prim(int n, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> g(n);
    for (auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<int> dis(n, INT_MAX);
    vector<bool> vis(n, false);
    dis[0] = 0;
    long long sum_w = 0;
    int cand;
    for (int _ = 0; _ < n; _++) {
        cand = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (cand == -1 || dis[j] < dis[cand])) {
                cand = j;
            }
        }
        for (auto [nbr, w] : g[cand]) {
            dis[nbr] = min(dis[nbr], w);
        }
        vis[cand] = true;
        sum_w += dis[cand];
    }
    return sum_w;
}

class Solution1584 {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges.push_back({i, j, abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])});
            }
        }
        return prim(n, edges);
    }
};

int main(int argc, char const *argv[]) {
    Solution1584 solu;
    cout << solu.minCostConnectPoints(*new vector<vector<int>>{{0,0},{2,2},{3,10},{5,2},{7,0}}) << endl;
    return 0;
}