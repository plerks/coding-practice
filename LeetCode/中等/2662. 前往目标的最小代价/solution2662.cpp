/*
url: https://leetcode.cn/problems/minimum-cost-of-a-path-with-special-roads/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2662 {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        int sx = start[0], sy = start[1];
        int tx = target[0], ty = target[1];

        auto hash = [&](int x, int y) -> long long {
            return x * (long long)(1e5 + 1) + y;
        };

        auto dehash = [&](long long node) -> pair<int, int> {
            int N = 1e5 + 1;
            return {node / N, node % N};
        };

        unordered_set<long long> nodes;
        nodes.insert(hash(sx, sy));
        nodes.insert(hash(tx, ty));
        for (auto& road : specialRoads) {
            int x1 = road[0], y1 = road[1];
            int x2 = road[2], y2 = road[3];
            long long u = hash(x1, y1), v = hash(x2, y2);
            nodes.insert(u);
            nodes.insert(v);
        }

        unordered_map<long long, vector<pair<long long, int>>> g; // g[u] = {v, w}
        for (long long u : nodes) {
            for (long long v : nodes) {
                auto [x1, y1] = dehash(u);
                auto [x2, y2] = dehash(v);
                g[u].push_back({v, abs(x1 - x2) + abs(y1 - y2)});
            }
        }
        for (auto& road : specialRoads) {
            int x1 = road[0], y1 = road[1];
            int x2 = road[2], y2 = road[3];
            int w = road[4];
            long long u = hash(x1, y1), v = hash(x2, y2);
            g[u].push_back({v, w});
        }

        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq; // (距离，节点)
        unordered_map<long long, long long> dis;
        pq.push({0, hash(sx, sy)});
        dis[hash(sx, sy)] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            auto [x, y] = dehash(node);
            if (d > dis[node]) continue;
            for (auto [next, w] : g[node]) {
                auto [nx, ny] = dehash(next);
                if (d + w < (dis.count(next) ? dis[next] : LLONG_MAX)) {
                    dis[next] = d + w;
                    pq.push({d + w, next});
                }
            }
        }
        return dis[hash(tx, ty)];
    }

    // 灵茶题解的简洁写法，specialRoads[i].length == 5，节点很少，边多(稠密图)，用朴素Dijkstra实现就行，用 for 循环去遍历 specialRoads
    int minimumCost_implementation2(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        unordered_map<long long, long long> dis; // (节点，距离)

        auto hash = [](int x, int y) {
            return (long long)x << 32 | y;
        };

        dis[hash(start[0], start[1])] = 0;
        dis[hash(target[0], target[1])] = abs(start[0] - target[0]) + abs(start[1] - target[1]);
        unordered_set<long long> vis;
        while (true) {
            long long u = -1;
            long long d = -1; // 这次最优先的那个节点
            for (auto [node, distance] : dis) {
                if (!vis.count(node) && (d < 0 || distance < d)) {
                    u = node;
                    d = distance;
                }
            }
            long long t = hash(target[0], target[1]);
            if (u == t) return d;
            vis.insert(u);
            int ux = u >> 32, uy = u & UINT32_MAX;
            // 松弛邻居，枚举所有邻居，其余所有节点都是u的邻居，包括终点和specialRoads中的点
            dis[t] = min(dis[t], d + abs(ux - target[0]) + abs(uy - target[1]));
            for (auto& r : specialRoads) {
                // 不用判断 (r[0], r[1]) 是否为 (ux, uy) 也行，松弛涉及了两段路也没问题
                int next_d = d + abs(r[0] - ux) + abs(r[1] - uy) + r[4];
                long long next = hash(r[2], r[3]);
                if (!dis.count(next) || next_d < dis[next]) dis[next] = next_d;
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2662 solu;
    // cout << solu.minimumCost(*new vector<int>{1,1}, *new vector<int>{4,5}, *new vector<vector<int>>{{1,2,3,3,2},{3,4,4,5,1}}) << endl;
    // cout << solu.minimumCost(*new vector<int>{3,2}, *new vector<int>{5,7}, *new vector<vector<int>>{{5,7,3,2,1},{3,2,3,4,4},{3,3,5,5,5},{3,4,5,6,6}}) << endl;
    cout << solu.minimumCost_implementation2(*new vector<int>{1,1}, *new vector<int>{4,5}, *new vector<vector<int>>{{1,2,3,3,2},{3,4,4,5,1}}) << endl;
    return 0;
}