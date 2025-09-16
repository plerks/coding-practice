/*
描述: 对于有向图，求强连通分量
参考: https://oi-wiki.org/graph/scc/
      https://www.bilibili.com/video/BV162U6YCE7o/
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 9;

// 图见img/refence3.png，把节点标号改成从0开始
vector<pair<int, int>> edges = {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{4,0},{4,7},{4,8},{5,2},{6,5},{7,1}};

vector<vector<int>> g(N);

auto init = []() {
    for (auto [u, v] : edges) {
        g[u].push_back(v);
    }
    return 0;
}();

int dfn[N], dfncnt; // 遇到节点的顺序编号。dfn[i] = 0 顺便代表未访问
int low[N]; // 节点通过后向边能到达的最高节点
stack<int> st; // 暂存节点的栈
int in_st[N]; // 每个节点是否在栈中，在栈中代表被发现，但还未访问完毕
int scc[N], scc_id; // 每个节点所在的SCC编号，scc_id为编号数字
int sz[N]; // 强连通分量scc_id的大小

// Tarjan求强连通分量SCC
void Tarjan(int u) {
    dfn[u] = low[u] = ++dfncnt;
    st.push(u); in_st[u] = true;
    for (int v : g[u]) {
        if (!dfn[v]) { // v未访问，树边
            Tarjan(v); // 递归
            low[u] = std::min(low[u], low[v]); // u能到v，v能回溯到的点u也能回溯到，递归返回后用low[v]更新low[u]
        }
        // v在暂存节点的栈中，代表 u, v 在一个潜在SCC分量中
        // (u, v)可能是后向边 / 前向边 / 同一个SCC分量里的跨边，不管如何更新low[u]就行。v不会高于其所在的SCC的根。
        else if (in_st[v]) {
            low[u] = std::min(low[u], dfn[v]); // 这里写 low[u] = std::min(low[u], low[v]); 也行
        }
        // 如果不判断 v 在栈中就更新low[u]，v 可能是之前已经访问完了的SCC分量，这会导致把 low[u] 更新地过小
    }
    // 看u是否为一个SCC根
    if (dfn[u] == low[u]) {
        ++scc_id;
        int node;
        do { // 出栈直到 u 出去
            node = st.top(); st.pop();
            scc[node] = scc_id;
            sz[scc_id]++;
            in_st[node] = false;
        } while (node != u);
    }
}

int main(int argc, char const *argv[]) {    
    for (int i = 0; i < N; i++) {
        if (!dfn[i]) Tarjan(i);
    }

    // 每个强连通分量，对上面的用例，结果为 {1,2,5,8}, {4}, {9}, {3,6,7}
    map<int, vector<int>> components;
    for (int i = 0; i < N; i++) {
        components[scc[i]].push_back(i + 1); // 节点标号得加1回去
    }
    return 0;
}