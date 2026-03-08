#include <bits/stdc++.h>

using namespace std;

struct Edge {
    // int from; // 如果要知道 edge[i] 的起点，需要再加个 from 属性并在 add_edge() 时维护
    int to; // 边的终点
    int w; // 边权
    int next; // 下一条兄弟边的编号
};

vector<Edge> edge;

vector<int> head; // head[i] 表示 i 号节点的第一条边在 edge 中的编号

void add_edge(int u, int v, int w = 1) {
    // 头插法插边
    edge.emplace_back(v, w, head[u]);
    head[u] = edge.size() - 1;
}

bool find_edge(int u, int v) {
    for (int i = head[u]; ~i; i = edge[i].next) { // 遍历 u 的出边的写法，~i 表示 i != -1
        if (edge[i].to == v) return true;
    }
    return false;
}

int main(int argc, char const *argv[]) {
    int n = 5, m = 3; // 节点数和边数
    edge.reserve(m);
    head.resize(n, -1);
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(0, 3);

    // 链式前向星的 dfs 示范
    vector<bool> vis(n);
    auto dfs = [&](auto& dfs, int r) -> void {
        vis[r] = true;
        cout << r << '\n';
        for (int i = head[r]; ~i; i = edge[i].next) {
            if (!vis[edge[i].to]) dfs(dfs, edge[i].to);
        }
    };
    dfs(dfs, 0);
    return 0;
}