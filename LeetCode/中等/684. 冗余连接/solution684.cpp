/*
url: https://leetcode.cn/problems/redundant-connection/
相关: LeetCode685. 冗余连接 II
标签: 【算法题单】图论算法, [mark]
*/
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;

    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (size[rx] < size[ry]) {
            parent[rx] = ry;
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int getSize(int x) {
        return size[find(x)];
    }

    int is_connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution684 {
public:
    // 我的解法，此题为无向图，用dfs找到跨边，记录parent + 求lca把环找到
    // 找环还不那么好写，这题的图特殊，是树 + 一条边，不是这样还不好写
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<vector<int>> g(n + 1); // 节点编号从1开始
        for (auto& edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        vector<int> vis(n + 1);
        vector<int> parent(n + 1, -1);
        int s, t; // (s, t)为冗余边
        // dfs找环
        auto dfs = [&](auto &dfs, int x) -> void {
            vis[x] = true;
            for (int y : g[x]) {
                if (vis[y]) {
                    if (y != parent[x]) { // 由于是无向图，要避免 1 -> 5，然后dfs(5)，5 把 5 -> 1 当成环
                        s = x;
                        t = y;
                    }
                }
                else {
                    parent[y] = x;
                    dfs(dfs, y);
                }
            }
        };
        dfs(dfs, 1); // 节点编号从1开始
        
        // 现在 (s, t) 为冗余边，找 lca 即可找到环的所有边

        int lca = get_lca(s, t, parent);
        set<pair<int, int>> cycle_edges;
        cycle_edges.insert({s, t});
        while (s != lca) {
            cycle_edges.insert({s, parent[s]});
            s = parent[s];
        }
        while (t != lca) {
            cycle_edges.insert({t, parent[t]});
            t = parent[t];
        }
        for (int i = edges.size() - 1; i >= 0; i--) {
            int u = edges[i][0], v = edges[i][1];
            if (cycle_edges.count({u, v}) || cycle_edges.count({v, u})) {
                return {u, v};
            }
        }
        return {};
    }

    int get_lca(int s, int t, vector<int>& parent) {
        unordered_set<int> st;
        while (s != -1) {
            st.insert(s);
            s = parent[s];
        }
        while (!st.count(t)) {
            t = parent[t];
        }
        return t;
    }

    // 参考官方题解，不需要完整找出环，只需要找出edges中最后出现的环上的边即可。用并查集遍历边，如果一个条边的两个节点已经相连，则其为冗余边
    vector<int> findRedundantConnection_implementation2(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n + 1); // 节点编号从1开始
        for (int i = 0; i < edges.size(); i++) {
            auto &edge = edges[i];
            int u = edge[0], v = edge[1];
            if (uf.is_connected(u, v)) {
                return {u, v};
            }
            uf.unite(u, v);
        }
        return {};
    }
};

int main(int argc, char const *argv[]) {
    Solution684 solu;
    auto a = solu.findRedundantConnection(*new vector<vector<int>>{{1,2}, {1,3}, {2,3}});
    auto b = solu.findRedundantConnection(*new vector<vector<int>>{{1,2}, {2,3}, {3,4}, {1,4}, {1,5}});

    auto c = solu.findRedundantConnection_implementation2(*new vector<vector<int>>{{1,2}, {1,3}, {2,3}});
    auto d = solu.findRedundantConnection_implementation2(*new vector<vector<int>>{{1,2}, {2,3}, {3,4}, {1,4}, {1,5}});
    return 0;
}