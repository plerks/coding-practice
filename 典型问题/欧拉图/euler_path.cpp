/*
url: https://www.luogu.com.cn/problem/P2731
参考: https://leetcode.cn/problems/reconstruct-itinerary/solutions/389885/zhong-xin-an-pai-xing-cheng-by-leetcode-solution/
      https://oi-wiki.org/graph/euler/
相关: LuoguP2731 [USACO3.3] 骑马修栅栏 Riding the Fences
标签: Hierholzer 算法
*/
#include <bits/stdc++.h>

using namespace std;

class Hierholzer {
private:
    vector<priority_queue<int, vector<int>, greater<int>>> g; // 为了得到字典序最小的欧拉路径，将边排序
    vector<int> st;
    map<pair<int, int>, int> cnt; // 标记已经删除的边，由于有重边，这里 value 是剩余边数。不过这题的范围可以直接用邻接矩阵

    void dfs(const int& root) {
        while (g[root].size() > 0) {
            int nbr = g[root].top();
            g[root].pop();
            if (!cnt.count({root, nbr}) || cnt[{root, nbr}] == 0) { // 已经删除的边
                cnt.erase({root, nbr});
                continue;
            }
            cnt[{root, nbr}]--;
            cnt[{nbr, root}]--; // 将无向图的对称边标记为已删除
            dfs(nbr);
        }
        st.emplace_back(root);
    }
public:
    // 返回从 root 开始的欧拉路径，edges 允许重边，需要外部保证从 root 开始的欧拉路径存在
    vector<int> find_euler_path(const int n, const vector<vector<int>>& edges, int start) {
        g.resize(n + 1); // 节点编号从 1 开始
        for (auto& e : edges) {
            g[e[0]].emplace(e[1]);
            g[e[1]].emplace(e[0]);
            cnt[{e[0], e[1]}]++;
            cnt[{e[1], e[0]}]++;
        }
        dfs(start);
        reverse(st.begin(), st.end());
        return st;
    }
};

int main(int argc, char const *argv[]) {
    Hierholzer h;
    // 图为有重边的无向图，节点编号从 1 开始
    int n = 3;
    vector<vector<int>> edges = {{1, 2}, {1, 2}, {2, 3}};
    vector<int> deg(n + 1);
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0], v = edges[i][1];
        deg[u]++;
        deg[v]++;
    }
    // 选能达到字典序最小的欧拉路径的起点
    int start = -1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 0 && deg[i] % 2 == 0) {
            start = i; break;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 0 && deg[i] % 2 == 1) {
            start = i; break;
        }
    }
    auto a = h.find_euler_path(n, edges, start);
    return 0;
}