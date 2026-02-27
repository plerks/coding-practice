/*
url: https://leetcode.cn/problems/min-cost-to-connect-all-points/
标签: 最小生成树
*/
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int cc; // 连通分量个数

    UnionFind(int n) : parent(n), size(n, 1), cc(n) {
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
        cc--;
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

    // x, y 是否在同一分量
    int is_connected(int x, int y) {
        return find(x) == find(y);
    }
};

// 计算最小生成树的权值，若图不连通则返回 INT64_MAX
long long kruskal(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end(), [&](const auto& a, const auto& b) {
        return a[2] < b[2];
    });

    UnionFind uf(n);
    long long sum_w = 0;
    for (auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (!uf.is_connected(u, v)) {
            uf.unite(u, v);
            sum_w += w;
        }
    }
    if (uf.cc > 1) return INT64_MAX;
    return sum_w;
}

class Solution1584 {
public:
    // 用 kruskal ，此题为稠密图，时间复杂度 O(n^2 * logn)
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges.push_back({i, j, abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])});
            }
        }
        return kruskal(n, edges);
    }
};

// [TODO] 官方题解有个建图优化的 Kruskal 解法，能减少边数，时间复杂度能优化到 O(nlogn)

int main(int argc, char const *argv[]) {
    Solution1584 solu;
    cout << solu.minCostConnectPoints(*new vector<vector<int>>{{0,0},{2,2},{3,10},{5,2},{7,0}}) << endl;
    return 0;
}