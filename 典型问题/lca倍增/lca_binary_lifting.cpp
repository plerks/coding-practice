/*
# 参考

https://oi-wiki.org/graph/lca/

https://leetcode.cn/problems/palindromic-path-queries-in-a-tree/solutions/3903005/lca-chai-fen-shu-zhuang-shu-zu-pythonjav-cuf3/

# 描述

预处理花 O(nlogn) 时间，后续单次 query lca 只需 O(logn) 时间

# 相关

LeetCode3841. 查询树上回文路径
*/

#include <bits/stdc++.h>

using namespace std;

class LcaBinaryLifting {
private:
    vector<int> depth;
    vector<vector<int>> pa; // pa[i][x] 表示 x 的第 2^i 个祖先，由于后面外层循环要按 2^i 来跳，第一维选为 i

public:
    LcaBinaryLifting(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        int m = __bit_width((uint32_t)n);
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        depth.resize(n);
        pa.resize(m, vector<int>(n, -1));
        auto dfs = [&](auto&& dfs, int x, int fa) -> void {
            pa[0][x] = fa; // dfs 过程只记录了 pa[0]，即父节点关系
            for (int y : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dfs(dfs, y, x);
                }
            }
        };
        dfs(dfs, 0, -1);

        // x 的 2^(i + 1) 祖先 = x 的 2^i 祖先的 2^i 祖先，由此递推
        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                int p = pa[i][x]; 
                if (p != -1) pa[i + 1][x] = pa[i][p];
            }
        }
    }

    // 返回 node 的第 k 个祖先节点，对父节点，k 是 1
    // 如果不存在，返回 -1
    int get_kth_ancestor(int node, int k) {
        for (; k > 0 && node >= 0; k &= k - 1) {
            node = pa[__builtin_ctz((uint32_t)k)][node];
        }
        return node;
    }

    // 返回 x 和 y 的 lca，编号从 0 开始
    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]); // 让深的那个跳到同一深度
        if (y == x) return x;
        for (int i = pa.size() - 1; i >= 0; i--) {
            int px = pa[i][x], py = pa[i][y]; // 每次跳 2^i 步，跳之前先谨慎检查 px != py 才跳，有点像试填法
            if (px != py) {
                x = px;
                y = py;
            }
        }
        return pa[0][x];
    }
};

int main(int argc, char const *argv[]) {
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    LcaBinaryLifting g(edges);
    cout << g.get_lca(1, 3) << endl;
    cout << g.get_lca(3, 4) << endl;
    return 0;
}