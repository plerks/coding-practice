/*
url: https://leetcode.cn/problems/the-time-when-the-network-becomes-idle/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2039 {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n = patience.size();
        vector<vector<int>> g(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> dis(n);
        queue<int> q;
        vector<int> vis(n);
        q.push(0);
        vis[0] = true;

        for (int level = 0; !q.empty(); level++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                int x = q.front(); q.pop();
                dis[x] = level;
                for (int y : g[x]) {
                    if (!vis[y]) {
                        q.push(y);
                        vis[y] = true;
                    }
                }
            }
        }

        int ans = 0;
        // patience[0] == 0，对于 1 <= i < n，1 <= patience[i] <= 10^5
        for (int i = 1; i < n; i++) {
            int d = dis[i];
            int p = patience[i];
            // 在2d时刻开始时接收到回复，如果此时到patience时刻，不会发
            // 找[0, 2d)的最后一个重发时刻 (2 * d - 1) / p * p ， 在这个时刻开始时最后一次重发
            // (2 * d - 1) / p * p 怎么找？
            // 重发时刻为 p 2p 3p ... kp (时刻开始时)
            // kp <= 2d - 1，kp为整数 => kp 为 (2 * d - 1) / p * p
            int last_send = (2 * d - 1) / p * p;
            int t = last_send + 2 * d;
            ans = max(ans, t);
        }

        return ans + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2039 solu;
    cout << solu.networkBecomesIdle(*new vector<vector<int>>{{0,1},{1,2}}, *new vector<int>{0,2,1}) << endl;
    cout << solu.networkBecomesIdle(*new vector<vector<int>>{{0,1},{0,2},{1,2}}, *new vector<int>{0,10,10}) << endl;
    return 0;
}