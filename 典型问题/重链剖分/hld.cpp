/*
# 参考

https://oi-wiki.org/graph/hld/

https://leetcode.cn/problems/palindromic-path-queries-in-a-tree/solutions/3902929/liang-chong-fang-fa-si-fen-mo-ban-da-fan-8u4d/

# 描述

优化树上两个点之间路径信息的修改和查询。

先这样想: 靠 dfs 序把树拍平，然后建一棵线段树去维护整棵树，x - lca - y 这条路径的信息，
分为 x - lca 和 lca - y 两部分，我们能方便维护和修改吗？
不行，无论是何种 dfs 序，x - lca - y 这条路径上的节点编号不一定是连续紧邻的，无法用线段树维护。

任意路径都可以看作某些链的组合，树链剖分由此而生，我们把整棵树划分为多个链，链的划分方式暗含一种 dfs 序，
且单条链的 dfn 一定是连续紧邻的，那么，就可以用一棵线段树来维护这些链。

对于任意路径 x - lca - y，可以拆成多条链的组合，虽然不一定每条链都是全的，但是由于一条链上的 dfn 都是紧邻的，
可以用线段树维护和修改。

现在的问题是对于一条路径，会用多少条链？如果不加控制，可能会涉及 O(n) 个链

为 dfs 序增加重链剖分的约束，由于都是重链，当我们向下经过一条 轻边 时，所在子树的大小至少会除以二，
因此，树上的每条路径都可以被拆分成不超过 O(logn) 条重链

参考 oiwiki:

当我们向下经过一条 轻边 时，所在子树的大小至少会除以二．

因此，对于树上的任意一条路径，把它拆分成从 LCA 分别向两边往下走，分别最多走 O(logn) 次，
因此，树上的每条路径都可以被拆分成不超过 O(logn) 条重链．

除了配合数据结构来维护树上路径信息，树剖还可以用来 O(log n)（且常数较小）地求 LCA．

# 相关

LeetCode3841. 查询树上回文路径
*/

#include <bits/stdc++.h>

using namespace std;

class HeavyLightDecomposition {
public:
    int n;
    vector<int> fa; // 父节点
    vector<int> dep; // 节点深度
    vector<int> siz; // 子树节点个数
    vector<int> hson; // 重儿子
    vector<int> top; // 所在重链的顶部节点
    vector<int> dfn; // 节点 x 的dfs 序编号
    vector<int> rnk; // dfs 序编号所对应的结点 x，有 rnk(dfn(x)) = x

    HeavyLightDecomposition(vector<vector<int>>& edges, int root) {
        this->n = edges.size() + 1; // 节点数
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        fa.assign(n, -1);
        dep.assign(n, 0);
        siz.assign(n, 1);
        hson.assign(n, -1);
        top.assign(n, -1);
        dfn.assign(n, -1);
        rnk.assign(n, -1);

        // 第一次 dfs ，计算出 fa(x), dep(x), siz(x), hson(x)，非递归写法
        vector st = {root};
        int time = 0;
        while (!st.empty()) { // 计算 fa, dep, rnk
            int u = st.back(); st.pop_back();
            rnk[time++] = u; // 不是最终的 rnk ，hson 还没算出来，无法计算 rnk，只是为了能逆拓扑序计算 siz
            for (int v : g[u]) {
                if (v != fa[u]) {
                    fa[v] = u;
                    dep[v] = dep[u] + 1;
                    st.push_back(v);
                }
            }
        }
        for (int i = rnk.size() - 1; i >= 0; i--) { // 从底向上计算 siz 和 hson
            int mxsz = 0;
            int u = rnk[i];
            for (int v : g[u]) {
                if (v != fa[u]) {
                    if (siz[v] > mxsz) mxsz = siz[v], hson[u] = v;
                    siz[u] += siz[v];
                }
            }
        }

        // 第二次 dfs ，计算出 rnk(x), top(x), dfn(x)，非递归写法
        st.clear();
        st.push_back(root);
        top[root] = root;
        time = 0;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            rnk[time] = u;
            dfn[u] = time++;
            for (int v : g[u]) {
                if (v != fa[u] && v != hson[u]) { // 所有轻儿子
                    top[v] = v;
                    st.push_back(v);
                }
            }
            if (hson[u] != -1) { // 重儿子没被父亲写 top，这时候写
                top[hson[u]] = top[u];
                st.push_back(hson[u]);
            }
        }
    }

    // 返回 node 的第 k 个祖先节点，对父节点，k 是 1
    // 如果不存在，返回 -1
    int get_kth_ancestor(int u, int k) {
        int d = dep[u] - k;
        if (d < 0) return -1;
        while (dep[u] > d) {
            int tu = top[u];
            if (dep[tu] <= d) return rnk[dfn[u] - (dep[u] - d)]; // 在这条链上。这里也可写成 dfn[tu] + (d - dep[tu])
            u = fa[tu];
        }
        return u;
    }

    int get_lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]]; // 让 lca 在 v 的链头
        }
        return dep[u] < dep[v] ? u : v;
    }

    // 返回 u-v 路径上经过的 dfn 区间链以供更新路径区间，注意 pair 的值是 dfn ，保证每个 pair = [l, r] 的 l <= r
    // 例如 1 - 0 - 2 会返回 [{0, 1}, {2, 2}]
    vector<pair<int,int>> get_path(int u, int v) {
        vector<pair<int, int>> pathu, pathv;
        int tu, tv;
        while ((tu = top[u]) != (tv = top[v])) {
            if (dep[tu] >= dep[tv]) { // 链头更低的走
                pathu.emplace_back(dfn[tu], dfn[u]);
                u = fa[tu];
            }
            else {
                pathv.emplace_back(dfn[tv], dfn[v]);
                v = fa[tv];
            }
        }
        if (dep[u] < dep[v]) pathu.emplace_back(dfn[u], dfn[v]);
        else pathv.emplace_back(dfn[v], dfn[u]);
        std::reverse(pathv.begin(), pathv.end());
        pathu.insert(pathu.end(), pathv.begin(), pathv.end());
        return pathu;
    }
};

int main(int argc, char const *argv[]) {
    HeavyLightDecomposition hld(*new vector<vector<int>>{{0, 1}, {0, 2}, {0, 3}}, 0);
    cout << hld.get_kth_ancestor(0, 1) << endl;
    auto a = hld.get_path(1, 3);
    return 0;
}