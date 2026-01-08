/*
url: https://leetcode.cn/problems/path-with-maximum-probability/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1514 {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> g(n);
        for (int i = 0; i < edges.size(); i++) {
            auto &edge = edges[i];
            int u = edge[0], v = edge[1];
            double w = succProb[i];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>> pq; // (距离，节点)
        vector<double> dis(n, 0);
        pq.push({1, start_node});
        dis[start_node] = 1;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (node == end_node) return dis[end_node];
            if (d > dis[node]) continue;
            for (auto [next, w] : g[node]) {
                if (d * w > dis[next]) {
                    dis[next] = d * w;
                    pq.push({d * w, next});
                }
            }
        }

        return dis[end_node];
    }
};

int main(int argc, char const *argv[]) {
    Solution1514 solu;
    cout << solu.maxProbability(3, *new vector<vector<int>>{{0,1},{1,2},{0,2}}, *new vector<double>{0.5,0.5,0.2}, 0, 2) << endl;
    return 0;
}