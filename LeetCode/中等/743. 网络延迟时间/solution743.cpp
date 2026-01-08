/*
url: https://leetcode.cn/problems/network-delay-time/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution743 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> g(n);
        k--; // 节点从 1 开始编号的，这里直接减一下
        for (auto& edge : times) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u - 1].push_back({v - 1, w});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (距离，节点)
        vector<int> dis(n, INT_MAX);
        pq.push({0, k});
        dis[k] = 0;
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

        int ans = *max_element(dis.begin(), dis.end());
        return ans == INT_MAX ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution743 solu;
    // cout << solu.networkDelayTime(*new vector<vector<int>>{{2,1,1},{2,3,1},{3,4,1}}, 4, 2) << endl;
    // cout << solu.networkDelayTime(*new vector<vector<int>>{{1,2,1}}, 2, 2) << endl;
    cout << solu.networkDelayTime(*new vector<vector<int>>{{1,2,1},{2,3,2},{1,3,4}}, 3, 1) << endl;
    return 0;
}