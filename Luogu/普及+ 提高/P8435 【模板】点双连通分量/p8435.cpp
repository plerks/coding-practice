// https://www.luogu.com.cn/problem/P8435

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

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 题目节点编号从 1 开始的
        edges.emplace_back(u, v);
    }
    
    VertexBCC vb(n, edges);

    cout << vb.bcc.size() << '\n';

    for (auto& v : vb.bcc) {
        cout << v.size();
        for (int i = 0; i < (int)v.size(); i++) {
            if (i < (int)v.size() - 1) cout << ' ' << (v[i] + 1); // +1 是为了把编号还原成从 1 开始
            else cout << ' ' << (v[i] + 1);
        }
        cout << '\n';
    }
    return 0;
}