/*
url: https://leetcode.cn/problems/palindromic-path-queries-in-a-tree/
参考: https://www.bilibili.com/video/BV15TZ4B1Eev/
      https://leetcode.cn/problems/palindromic-path-queries-in-a-tree/solutions/3903005/lca-chai-fen-shu-zhuang-shu-zu-pythonjav-cuf3/
标签: LeetCode第176场双周赛, 时间戳, 树的扁平化, dfs 序, dfn, 差分树状数组 / 线段树, lca, 倍增
*/

// 这次双周赛三题

#include <bits/stdc++.h>

using namespace std;

struct Fenwick {
    vector<int> tree;

    Fenwick(int n) : tree(n + 1) {}

    void update(int i, int diff) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] ^= diff;
        }
    }

    int pre(int i) {
        int res = 0;
        for (; i > 0; i &= i - 1) {
            res ^= tree[i];
        }
        return res;
    }
};

class LcaBinaryLifting {
private:
    vector<int> depth;
    vector<vector<int>> pa; // pa[i][x] 表示 x 的第 2^i 个祖先，由于后面外层循环要按 2^i 来跳，第一维选为 i

public:
    vector<int> tin; // dfs 时间戳，dtime，也是 dfn
    vector<int> tout; // 子树里最大的 dtime，注意不是 ftime，这个问题里只有 discover time 的概念
    vector<int> path_xor_from_root; // 到 root 的 xor 结果，表示了节点 x 的前缀成分。这里只记初始状态的值

    LcaBinaryLifting(vector<vector<int>>& edges, string& s) {
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
        tin.resize(n);
        tout.resize(n);
        path_xor_from_root.resize(n);
        path_xor_from_root[0] = 1 << (s[0] - 'a');
        int clock = 0;
        auto dfs = [&](auto&& dfs, int x, int fa) -> void {
            pa[0][x] = fa; // dfs 过程只记录了 pa[0]，即父节点关系
            tin[x] = ++clock; // 从 1 开始
            for (int y : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    path_xor_from_root[y] = path_xor_from_root[x] ^ (1 << (s[y] - 'a'));
                    dfs(dfs, y, x);
                }
            }
            tout[x] = clock; // 子树里最大的 dfn 编号
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

class Solution3841 {
public:
    /* 参考灵茶题解，时间复杂度 O((n + q)logn)
    首先，题目是要在更改中高效判断 x - lca(x, y) - y 的成分，能构成回文的充要条件是最多一个字母的出现频率为奇数，
    这里可以用位运算压缩，并且计算频率时由于只关心奇偶性，只需要在那个位置上异或1就行。
    关于如何计算 x - lca(x, y) - y 的频率成分，可以用前缀和的思想，维护"各个节点到 root 的成分"，用一遍 dfs 得到初始时各个节点到 root 的成分，
    x - lca(x, y) - y 的成分 = (x —— root) + (y —— root) - (lca —— root) - lca
    （注意对异或 减state 等价于 加state）

    现在要对每个原树节点维护到root的路径上的成分变化量(没加上初始时刻，初始时刻的状态通过一遍dfs计算出来后不需要往线段树中更新)

    当一个节点的字符被修改时，其下的所有节点到根的成分都会变，都需要修改，如何高效修改整个子树？
    用时间戳。根据dfs序，我们可以在子树根上记录 子树根的dfn 和 子树中最大的dfn ，然后可以把子树修改变成区间修改[dfn_root, dfn_last]，
    这样会达到把树拍平的效果。注意子树的 dfn 一定是连续紧邻的，所以才能用线段树维护
    
    线段树维护的是什么？
    原树是每个节点有个自己的字符，而线段树的每个节点是维护的对应dfn编号到root的路径上的成分变化量(没加上初始时刻)
    

    这里是区间修改 + 单点查询，可以直接用线段树(维护按dfn编号的节点的状态增量)，不过题解中用了种特殊技巧，差分树状数组，
    我们把区间修改用差分的思想来完成，只需要标记开始和结束位置的变化量，区间修改变成了两个单点修改，同时单点查询变成了对差分数组的前缀和，
    于是用树状数组也可以完成功能。

    最后一件事是求 lca，这里需要倍增，毕竟要多次查询
    */
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        Fenwick tree(n);
        LcaBinaryLifting g(edges, s);
        vector<bool> ans;
        string op; int u, v; char c;

        for (auto& q : queries) {
            stringstream ss(q);
            ss >> op >> u;
            if (op[0] == 'u') { // 更新
                ss >> c;
                int diff = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                s[u] = c;
                int l = g.tin[u], r = g.tout[u]; // 把 diff 异或到 [l, r] ，可以直接用线段树，这里用差分树状数组完成
                tree.update(l, diff);
                tree.update(r + 1, diff);
            }
            else { // 查询
                ss >> v;
                int lca = g.get_lca(u, v);
                // g.path_xor_from_root 只记了初始时候的，tree 里记了增量，由于异或可加性，最后加起来就是最终状态
                // 不用考虑 (lca —— root) 那段，自动消掉了
                int res = g.path_xor_from_root[u] ^ g.path_xor_from_root[v] ^ (tree.pre(g.tin[u]) ^ tree.pre(g.tin[v])) ^ (1 << (s[lca] - 'a'));
                ans.push_back((res & (res - 1)) == 0);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3841 solu;
    // auto a = solu.palindromePath(3, *new vector<vector<int>>{{0, 1}, {1, 2}}, "aac", *new vector<string>{"query 0 2","update 1 b","query 0 2"});
    auto b = solu.palindromePath(4, *new vector<vector<int>>{{0, 1}, {0, 2}, {0, 3}}, "abca", *new vector<string>{"query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"});
    return 0;
}