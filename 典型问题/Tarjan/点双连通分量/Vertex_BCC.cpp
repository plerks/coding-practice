/*
描述: 对于无向图，求点双连通分量
参考: https://oi-wiki.org/graph/bcc/#%E7%82%B9%E5%8F%8C%E8%BF%9E%E9%80%9A%E5%88%86%E9%87%8F
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 12;

// 图见img/refence.png，上部是原图，下部是点双分解结果
vector<pair<int, int>> edges = {{0,1},{0,4},{1,5},{2,3},{2,5},{2,7},{3,7},{4,5},{4,8},{5,6},{5,8},{5,9},{5,10},{6,10},{9,10},{10,11}};

vector<vector<int>> g(N);

auto init = []() {
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return 0;
}();

int dfn[N], dfncnt; // 遇到节点的顺序编号。dfn[i] = 0 顺便代表未访问
int low[N]; // 节点通过后向边能到达的最高节点
stack<int> st; // 暂存节点的栈
bool cut[N]; // 是否是割点
vector<vector<int>> bcc; // 点双分量
int root; // 当前dfs的树根

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfncnt;
    st.push(u);
    int child = 0; // u 的 dfs 子树数量
    for (int v : g[u]) {
        if (!dfn[v]) { // 树边
            child++;
            Tarjan(v);
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

int main(int argc, char const *argv[]) {    
    for (int i = 0; i < N; i++) {
        if (!dfn[i]) {
            root = i;
            Tarjan(i);
        }
    }

    for (auto& v : bcc) {
        cout << '{';
        for (int i = 0; i < (int)v.size(); i++) {
            if (i < (int)v.size() - 1) cout << (char)(v[i] + 'A') << ", ";
            else cout << (char)(v[i] + 'A');
        }
        cout << '}' << endl;
    }

    auto _ = [&]() {
        cout << "cut vertex: ";
        for (int i = 0; i < N; i++) {
            if (cut[i]) cout << (char)(i + 'A');
        }
        return 0;
    }();
    return 0;
}