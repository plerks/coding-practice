/*
url: https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution882 {
public:
    int reachableNodes_wa(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> g(n);
        auto hash = [&](int x, int y) {
            return x * (n + 1) + y;
        };
        unordered_map<int, int> mid_cnt; // (记录 u, v 中间的节点数)
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            g[u].push_back({v, cnt});
            g[v].push_back({u, cnt});
            mid_cnt[hash(u, v)] = cnt;
            mid_cnt[hash(v, u)] = cnt;
        }
        unordered_map<int, int> mp; // mp 记录 (u -> v) 中间能走几个节点
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (距离，节点)
        vector<int> dis(n, INT_MAX);
        pq.push({0, 0});
        dis[0] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dis[node]) continue;
            for (auto [next, c] : g[node]) { // 中间有 c 个节点，边长为 c + 1
                int w = c + 1;
                mp[hash(node, next)] = max(mp[hash(node, next)], min(c, maxMoves - dis[node]));
                if (d + w <= maxMoves && d + w < dis[next]) {
                    pq.push({d + w, next});
                    dis[next] = d + w;
                    pq.push({d + w, next});
                }
            }
        }
        int ans = 0;
        for (auto& [h, cnt] : mp) {
            int u = h / (n + 1), v = h % (n + 1);
            if (u > v) continue;
            int cnt2 = mp[hash(v, u)];
            ans += min(cnt + cnt2, mid_cnt[hash(u, v)]);
        }
        for (int d : dis) if (d != INT_MAX) ans++;
        return ans;
    }

    // 要先算出最短距离，然后再算边中间能访问的节点，不然枚举边会有缺失
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> g(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            g[u].push_back({v, cnt});
            g[v].push_back({u, cnt});
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (距离，节点)
        vector<int> dis(n, INT_MAX);
        pq.push({0, 0});
        dis[0] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dis[node]) continue;
            for (auto [next, c] : g[node]) { // 中间有 c 个节点，边长为 c + 1
                int w = c + 1;
                if (d + w <= maxMoves && d + w < dis[next]) {
                    pq.push({d + w, next});
                    dis[next] = d + w;
                    pq.push({d + w, next});
                }
            }
        }
        int ans = 0;
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            if (u >= v) continue; // 防止重复计数
            int move1 = max(0, maxMoves - dis[u]);
            int move2 = max(0, maxMoves - dis[v]);
            ans += min(cnt, move1 + move2);
        }
        for (int d : dis) if (d != INT_MAX) ans++;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution882 solu;
    // cout << solu.reachableNodes_wa(*new vector<vector<int>>{{0,1,10},{0,2,1},{1,2,2}}, 6, 3) << endl;
    cout << solu.reachableNodes_wa(*new vector<vector<int>>{{1,2,5},{0,3,3},{1,3,2},{2,3,4},{0,4,1}}, 7, 5) << endl;
    // cout << solu.reachableNodes(*new vector<vector<int>>{{0,1,10},{0,2,1},{1,2,2}}, 6, 3) << endl;
    cout << solu.reachableNodes(*new vector<vector<int>>{{1,2,5},{0,3,3},{1,3,2},{2,3,4},{0,4,1}}, 7, 5) << endl;
    return 0;
}