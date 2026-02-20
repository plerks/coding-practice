/*
# 参考

https://www.bilibili.com/video/BV15TZ4B1Eev/

# 描述

对于一棵树，每个节点有一个值，现在修改操作每次修改一棵子树的所有值，如何高效修改整个子树并查询？
用时间戳。根据dfs序，我们可以在子树根上记录 子树根的dfn 和 子树中最大的dfn ，然后可以把子树修改变成区间修改[dfn_root, dfn_last]，
这样会达到把树拍平的效果，然后再用线段树更新和查询。

# 相关

LeetCode3841. 查询树上回文路径
*/

// 这里以：更新整颗子树的值，以及查询子树 sum 为例，需要区间修改和区间查询

#include <bits/stdc++.h>

using namespace std;

class SegTree {
private:
    vector<int> tree, lazy; // tree[p]是相应区间的求和，lazy[p]是相应区间的lazy set值
    int n;

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            tree[p] = nums[s];
            return;
        }
        int m = s + ((t - s) >> 1);
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(s, t, p);
    }

    int query(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) return tree[p];
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        int sum = 0;
        if (L <= m) sum += query(L, R, s, m, p * 2);
        if (R > m) sum += query(L, R, m + 1, t, p * 2 + 1);
        return sum;
    }

    void update(int L, int R, int val, int s, int t, int p) {
        if (L <= s && t <= R) {
            tree[p] = (t - s + 1) * val;
            lazy[p] = val;
            return;
        }
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        if (L <= m) update(L, R, val, s, m, p * 2);
        if (R > m) update(L, R, val, m + 1, t, p * 2 + 1);
        pushup(s, t, p);
    }

    void pushdown(int s, int t, int p) {
        int m = s + ((t - s) >> 1);
        if (s != t && lazy[p] > 0) { // 这里要求set时提供的val > 0，因为要用lazy[p]的值是否>0来区分是否有懒惰标记
            tree[p * 2] = (m - s + 1) * lazy[p];
            lazy[p * 2] = lazy[p];
            tree[p * 2 + 1] = (t - m) * lazy[p];
            lazy[p * 2 + 1] = lazy[p];
            lazy[p] = 0;
        }
    }

    void pushup(int s, int t, int p) {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    SegTree(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        lazy.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    int query(int L, int R) { return query(L, R, 0, n - 1, 1); }

    void update(int L, int R, int val) { return update(L, R, val, 0, n - 1, 1); }
};

class TreeFlatten {
public:
    vector<int> tin; // dfs 时间戳，dtime，也是 dfn
    vector<int> tout; // 子树里最大的 dtime，注意不是 ftime，这个问题里只有 discover time 的概念

    TreeFlatten(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        tin.resize(n);
        tout.resize(n);
        int clock = -1;
        auto dfs = [&](auto&& dfs, int x, int fa) -> void {
            tin[x] = ++clock; // 从 0 开始
            for (int y : g[x]) {
                if (y != fa) {
                    dfs(dfs, y, x);
                }
            }
            tout[x] = clock; // 子树里最大的 dfn 编号
        };
        dfs(dfs, 0, -1);
    }
};

int main(int argc, char const *argv[]) {
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    TreeFlatten tf(edges);
    int n = edges.size() + 1;
    vector<int> nums(n, 0);
    SegTree tree(nums);
    // 子树 2 的值全 + 2
    tree.update(tf.tin[2], tf.tout[2], 2);
    // 子树 1 的值全 + 1
    tree.update(tf.tin[1], tf.tout[1], 1);

    // 查询子树 0 的节点值总和
    cout << tree.query(tf.tin[0], tf.tout[0]) << endl;
    return 0;
}