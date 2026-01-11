/*
url: https://leetcode.cn/problems/second-minimum-time-to-reach-destination/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2045 {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> g(n + 1); // 节点编号从 1 开始
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (距离，节点)
        const int inf = INT_MAX / 2;
        vector<int> dis(n + 1, inf);
        vector<int> second_dis(n + 1, inf);
        pq.push({0, 1});
        dis[1] = 0;
        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dis[node] && d > second_dis[node]) continue;
            for (int neighbor : g[node]) {
                int w = time;
                if ((d / change) % 2 == 1) d = (d / change + 1) * change;
                int a = d + w;
                if (a < dis[neighbor]) {
                    dis[neighbor] = a;
                    pq.push({a, neighbor});
                }
                else if (a > dis[neighbor] && a < second_dis[neighbor]) {
                    second_dis[neighbor] = a;
                    pq.push({a, neighbor});
                }
                // 不能直接把 pq.push({a, neighbor}); 放这里
            }
        }
        return second_dis[n];
    }

    /* 官方题解的解法是用bfs，除开在每个节点的等待时间，这里相当于每条边权都相等的无向图，bfs 就可以达成 Dijkstra 的效果，
    且时间复杂度低了，然后最后去根据路径段数算总时间（段数越高，时间一定越高（同一时间要么都在走，要么都在等），所以之前忽略等待时间的
    bfs没问题，最后加上等待时间即可）。
    */

};

int main(int argc, char const *argv[]) {
    Solution2045 solu;
    // cout << solu.secondMinimum(5, *new vector<vector<int>>{{1,2},{1,3},{1,4},{3,4},{4,5}}, 3, 5) << endl;
    cout << solu.secondMinimum(2, *new vector<vector<int>>{{1,2}}, 3, 2) << endl;
    return 0;
}