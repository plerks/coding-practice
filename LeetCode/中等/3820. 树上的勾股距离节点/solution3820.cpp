/*
url: https://leetcode.cn/problems/rotate-non-negative-elements/
标签: LeetCode第486场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
        vector<vector<int>> g(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        auto ax = calc(g, x);
        auto ay = calc(g, y);
        auto az = calc(g, z);
        int ans = 0;
        for (int u = 0; u < n; u++) {
            vector<long long> e{ax[u], ay[u], az[u]};
            sort(e.begin(), e.end());
            if (e[0] * e[0] + e[1] * e[1] == e[2] * e[2]) ans++;
        }
        return ans;
    }

    // 枚举 u 的话需要每次计算 u 到 x / y / z 的距离，转换成在反图中求 x / y / z 到其它节点的单源最短路径，就只需要求三次
    // 求 x / y / z 到其它节点的距离
    vector<int> calc(vector<vector<int>>& g, int r) {
        int n = g.size();
        vector<int> dis(n);
        dis[r] = 0;

        auto dfs = [&](auto& dfs, int root, int fa) -> void {
            for (int nbr : g[root]) {
                if (nbr == fa) continue;
                dis[nbr] = dis[root] + 1;
                dfs(dfs, nbr, root);
            }
        };

        dfs(dfs, r, -1);
        return dis;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}