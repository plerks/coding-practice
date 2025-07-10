/*
url: https://leetcode.cn/problems/number-of-operations-to-make-network-connected/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1319 {
public:
    // 时间复杂度 O(n + m)
    int makeConnected(int n, vector<vector<int>>& connections) {
        // n个点连通需要n-1条边，这题可以任意移线，最小操作次数为连通分量数 - 1
        if (connections.size() < n - 1) return -1;
        vector<vector<int>> g(n);
        for (auto v : connections) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        vector<int> vis(n);

        auto dfs = [&](auto& dfs, int r) -> void {
            vis[r] = true;
            for (auto next : g[r]) {
                if (!vis[next]) dfs(dfs, next);
            }
        };

        int cnt = 0; // 连通分量数

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                cnt++;
                dfs(dfs, i);
            }
        }

        return cnt - 1;
    }

    // 也可用并查集求连通分量数，官方题解有写用并查集的代码。这题用并查集的话只需遍历一遍connections，时间复杂度O(m⋅α(n))
    // m是connections的长度，α 是阿克曼函数的反函数
};

int main(int argc, char const *argv[]) {
    Solution1319 solu;
    cout << solu.makeConnected(4, *new vector<vector<int>>{{0,1},{0,2},{1,2}}) << endl;
    cout << solu.makeConnected(4, *new vector<vector<int>>{{0,1},{0,2},{0,3},{1,2}}) << endl;
    return 0;
}