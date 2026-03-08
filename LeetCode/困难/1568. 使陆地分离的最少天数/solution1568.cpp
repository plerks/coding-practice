// https://leetcode.cn/problems/minimum-number-of-days-to-disconnect-island/

#include <bits/stdc++.h>

using namespace std;

class VertexBCC {
public:
    int n = -1, m = -1; // 节点数和边数
    vector<int> dfn; int dfncnt = 0; // 遇到节点的顺序编号。dfn[i] = 0 顺便代表未访问
    vector<int> low; // 节点通过后向边能到达的最高节点
    stack<int> st; // 暂存节点的栈
    vector<bool> cut; // 是否是割点
    vector<vector<int>> bcc; // 点双分量
    int root = 0; // 当前dfs的树根
    vector<vector<int>> g;
    int cc = 0; // 连通分量数

    VertexBCC(int n, const vector<pair<int, int>>& edges) {
        this->n = n;
        this->m = edges.size();
        dfn.resize(n);
        low.resize(n);
        cut.resize(n, false);
        g.resize(n);
        for (auto [u, v] : edges) {
            g[u].push_back(v);
            g[v].push_back(u);
        }

        for (int i = 0; i < n; i++) {
            if (!dfn[i]) {
                cc++; // 可以在这里顺便统计连通分量数
                root = i;
                tarjan(i);
            }
        }
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++dfncnt;
        st.push(u);
        int child = 0; // u 的 dfs 子树数量
        for (int v : g[u]) {
            if (!dfn[v]) { // 树边
                child++;
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= dfn[u]) { // v 到不了 u 的真祖先，这里有个点双分量，往上最多扩展到 u
                    if (u != root || child >= 2) cut[u] = true; // 归类是否是割点。子树 v 到不了 u 的真祖先，若 u 非根，则为割点；若 u 为根，要看根的树边分支数，得 >= 2 才是割点
                    vector<int> component;
                    int node;
                    do { // 出栈直到 v 出去
                        node = st.top(); st.pop();
                        component.push_back(node);
                    } while (node != v);
                    component.push_back(u); // 补上 u
                    bcc.push_back(component);
                }
            }
            else {
                low[u] = std::min(low[u], dfn[v]);
                // 求点双分量的Tarjan，这里不能改成 low[u] = std::min(low[u], low[v]);，原因见 ./README.md
            }
        }

        // 整树只有一个根的情况
        if (u == root && child == 0) {
            st.pop();
            bcc.push_back({u});
        }
    }
};

class Solution1568 {
public:
    /* 参考官方题解，最终答案不会超过 2，因为总是可以将某个角落相邻的两个陆地单元变成水单元，从而使这个角落的陆地单元与原岛屿分离。
    分类讨论，先看连通分量的数量，
    1. 如果连通分量数 > 1，不用删除
    2. 如果连通分量数 == 1，看 n 是否为 1 和 割点数，如果有割点，答案为 1，否则为 2
    */
    int minDays(vector<vector<int>>& grid) {
        int mx = std::max(grid.size(), grid[0].size());
        vector<pair<int, int>> DIRECTIONS = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int x, int y) {
            return 0 <= x && x < grid.size() && 0 <= y && y < grid[0].size();
        };

        auto h = [&](int x, int y) {
            return x * mx + y;
        };

        int n = 0;
        vector<int> idx(mx * mx); // 节点顺序编号
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    idx[h(i, j)] = n++;
                }
            }
        }
        
        vector<pair<int, int>> edges;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    for (auto [dx, dy] : DIRECTIONS) {
                        int ii = i + dx, jj = j + dy;
                        if (legal(ii, jj) && grid[ii][jj] == 1) {
                            edges.emplace_back(idx[h(i, j)], idx[h(ii, jj)]);
                        }
                    }
                }
            }
        }

        VertexBCC vb(n, edges);
        if (vb.cc == 0 || vb.cc > 1) return 0; // 没节点 或 已经不连通
        if (n == 1) return 1;
        int cut_cnt = 0;
        for (int i = 0; i < n; i++) if (vb.cut[i]) cut_cnt++;
        if (cut_cnt > 0) return 1;
        return 2;
    }
};

int main(int argc, char const *argv[]) {
    Solution1568 solu;
    cout << solu.minDays(*new vector<vector<int>>{{1, 1}, {1, 0}}) << endl;
    return 0;
}