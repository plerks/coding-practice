// https://leetcode.cn/problems/critical-connections-in-a-network/

#include <bits/stdc++.h>

using namespace std;

class EdgeBCC {
private:
    struct Edge { // 链式前向星
        int from;
        int to;
        int next;
    };
public:
    int n = 0, m = 0;
    vector<Edge> edge;
    vector<int> head;

    void add_edge(int u, int v) {
        edge.emplace_back(u, v, head[u]);
        head[u] = edge.size() - 1;
    }

    void add_uedge(int u, int v) {
        add_edge(u, v); add_edge(v, u);
    }

    vector<bool> isbridge;
    vector<int> dfn; int dfncnt = 0; // 遇到节点的顺序编号。dfn[i] = 0 顺便代表未访问
    vector<int> low;
    vector<int> vis_bcc; // 每个节点所属的 bcc 编号，为 0 代表未访问
    int bcc_cnt = 0;
    vector<vector<int>> bcc;

    EdgeBCC(int n, vector<pair<int, int>>& edges) {
        this->n = n;
        this->m = edges.size();
        head.resize(n + 1, -1); // 节点编号从 1 开始
        isbridge.resize(2 * m, false);
        dfn.resize(n + 1);
        low.resize(n + 1);
        vis_bcc.resize(n + 1);

        // 分解边双分量
        for (int i = 0; i < m; i++) {
            auto [u, v] = edges[i];
            if (u == v) continue; // 自环直接忽略即可
            add_uedge(u, v);
        }
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == 0) tarjan(i, -1);
        }
        int bcc_id = 0;
        for (int i = 1; i <= n; i++) {
            if (vis_bcc[i] == 0) {
                bcc.push_back(vector<int>());
                dfs(i, ++bcc_id);
            }
        }
        this->bcc_cnt = bcc_id;
    }

    // 对可能 有重边 的无向图求割边。重边的处理方式是：
    // 1. 第一条回边：如果是直接连向父节点，应该忽略（否则会把桥误判为非桥）
    // 2. 第二条及更多的重边：即使连向父节点，也应该被当作回边处理
    void tarjan(int u, int from_edge_idx) { // fedge 是来的那条边，即 fedge 号边的终点是 u
        dfn[u] = low[u] = ++dfncnt;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (!dfn[v]) {
                tarjan(v, i);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) { // 注意这里是 > 而非点双分解的 >=
                    isbridge[i] = isbridge[i ^ 1] = true;
                }
            }
            else {
                if (i != (from_edge_idx ^ 1)) low[u] = min(low[u], dfn[v]); // 不是那条回去的边，就要处理
            }
        }
    }

    // 通过tarjan()找出割边之后分解边双分量(把 bcc id 写到 vis_bcc 中)
    void dfs(int u, int id) {
        vis_bcc[u] = id; bcc[id - 1].push_back(u);
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (vis_bcc[v] != 0 || isbridge[i]) continue;
            dfs(v, id);
        }
    }
};

class Solution1192 {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        int m = connections.size();
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++) edges.push_back({connections[i][0], connections[i][1]});
        EdgeBCC eb(n, edges);
        vector<vector<int>> ans;
        for (int i = 0; i < 2 * m; i += 2) {
            if (eb.isbridge[i]) {
                ans.push_back({eb.edge[i].from, eb.edge[i].to});
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1192 solu;
    auto a = solu.criticalConnections(4, *new vector<vector<int>>{{0,1},{1,2},{2,0},{1,3}});
    return 0;
}