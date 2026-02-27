#include <bits/stdc++.h>

using namespace std;

// 计算最小生成树的权值，若图不连通则返回 INT64_MAX
long long prim(int n, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> g(n);
    for (auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (优先级，节点编号)
    vector<int> dis(n, INT_MAX);
    vector<bool> vis(n, false);
    pq.emplace(0, 0);
    dis[0] = 0;
    long long sum_w = 0;
    while (!pq.empty()) {
        auto [d, node] = pq.top(); pq.pop();
        if (vis[node]) continue;
        vis[node] = true;
        sum_w += d;
        for (auto [nbr, w] : g[node]) {
            if (w < dis[nbr]) {
                pq.emplace(w, nbr);
                dis[nbr] = w;
            }
        }
    }
    return sum_w;
}

// 朴素实现
long long prim_trival(int n, vector<vector<int>>& edges) {
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

int main(int argc, char const *argv[]) {
    cout << prim(4, *new vector<vector<int>>{{0,1,1},{1,2,6},{0,3,2},{2,3,3}}) << endl;
    cout << prim_trival(4, *new vector<vector<int>>{{0,1,1},{1,2,6},{0,3,2},{2,3,3}}) << endl;
    return 0;
}