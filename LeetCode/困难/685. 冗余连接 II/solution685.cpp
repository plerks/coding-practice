/*
url: https://leetcode.cn/problems/redundant-connection-ii/
相关: LeetCode684. 冗余连接
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

class Solution685 {
public:
    /* 参考题解，
    给定的图是有向图，为一棵 有根树 + 附加的一条边
    考虑这条附加边的情况，
    1. 如果其从某个节点指向根，则图中没有入度为2的节点(必须看入度，出度没用，有根树中一个节点可能有多个出度 0，1，2，3... 但入度除根都为1，因为有parent关系)。
        将这个图视为无向图，图中有且仅有一个环，删除环上任意一条边，剩余部分都是有根树。用并查集找环，删除使环出现的边，
        就能满足题目：若有多个答案，返回最后出现在给定二维数组的答案。 的要求
    2. 如果其从某个节点指向非根节点，则途中一定没有度为2的节点。但是要分类讨论：
        以下称导致入度为2的两条边为冲突边，我们必须删除两条冲突边之一
        2.1. 如果附加边从u指向u的某个祖先v，则我们必须找到这条附加边，其导致了环
        2.2. 如果附加边从u指向u的非祖先节点v，则删除两条冲突边任一即可
       当我们发现了会使一个点入度为2的边(u, v)时（这是两条冲突边的较后者），不将其加入并查集，
       如果最后通过并查集发现无环，说明是2.2，删除(u, v)即可，(u, v)也是较后者。
       如果有环，则是2.1，必须删除 (parent[v], v)
    */
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n + 1); // 节点编号从1开始
        vector<int> parent(n + 1, -1);
        int cycle_edge = -1; // 是否有环，以及导致发现环时的那条边
        int conflict_edge = -1; // 是否有入度为2的节点，以及较后的冲突边
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            if (parent[v] != -1) { // 后一条冲突边，不加入图中
                conflict_edge = i;
            }
            else {
                if (uf.is_connected(u, v)) {
                    cycle_edge = i;
                }
                uf.unite(u, v); // 将边视为无向边，加入并查集
                parent[v] = u;
            }
        }
        if (conflict_edge == -1) { // 没有冲突边，附加边指向根
            return edges[cycle_edge];
        }
        // 选冲突边之一
        int u = edges[conflict_edge][0], v = edges[conflict_edge][1];
        if (cycle_edge >= 0) { // 有环，要删前面遇到的那条冲突边
            return {parent[v], v};
        }
        return {u, v};
    }
};

int main(int argc, char const *argv[]) {
    Solution685 solu;
    auto a = solu.findRedundantDirectedConnection(*new vector<vector<int>>{{1,2},{1,3},{2,3}});
    auto b = solu.findRedundantDirectedConnection(*new vector<vector<int>>{{1,2},{2,3},{3,4},{4,1},{1,5}});
    auto c = solu.findRedundantDirectedConnection(*new vector<vector<int>>{{2,1},{3,1},{4,2},{1,4}});
    return 0;
}