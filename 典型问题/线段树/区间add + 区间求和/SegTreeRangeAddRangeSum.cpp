/*
参考: https://oi-wiki.org/ds/seg/
      https://www.bilibili.com/video/BV18t4y1p736/
相关: 洛谷P3372 【模板】线段树 1
*/

#include <bits/stdc++.h>

using namespace std;

/* 牵涉到求和的部分容易溢出，例如洛谷P3372需要把vector<int> tree，int sum，int range_sum(int L, int R)，int range_sum(int L, int R, int s, int t, int p)
牵涉到求和的部分全改成long long */
class SegTreeRangeAddRangeSum {
private:
    vector<int> tree, lazy; // tree和lazy分别存储线段树和懒惰标记，tree[p]是相应区间的求和，lazy[p]是相应区间的lazy add量
    int n;

    void build(vector<int>& nums, int s, int t, int p) { // [s, t]为当前节点包含的区间, p为当前节点的编号
        if (s == t) {
            tree[p] = nums[s];
            return;
        }
        int m = s + ((t - s) >> 1); // 将当前区间分为[s, m]和[m + 1, t]
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(s, t, p);
    }

    int range_sum(int L, int R, int s, int t, int p) { // [L, R]为查询区间, [s, t]为当前节点包含的区间, p为当前节点的编号
        /* 如果当前节点区间[s, t]是查询区间[L, R]的子集时，直接返回当前区间的和。
        这里range_sum()表达的是: 返回当前节点p在[L, R]区间内的数之和。 */
        if (L <= s && t <= R) return tree[p]; // 查询整个当前区间
        pushdown(s, t, p); // 向子节点细分，需要先把标记下放
        int m = s + ((t - s) >> 1); // 将当前区间分为[s, m]和[m + 1, t]
        int sum = 0;
        // 查询当前区间的部分
        // 递归一定能结束，一直往下递归，到了叶节点后，若其在[L, R]范围内，则会走if (L <= s && t <= R)的判断，不会再递归。若不在[L, R]范围内，则以下两个递归进不去
        /* 左儿子[s, m]和查询区间[L, R]有重合部分。写成if (!(R < s) && !(L > m))也行，但是只要一开始[L,R]没给错(属于根节点区间)，那么
        只要有L<=m，查询区间与左儿子区间就一定有重合部分，不会出现L<=m且R<s的情况 */
        if (L <= m) sum += range_sum(L, R, s, m, p * 2);
        // 左儿子[m + 1, t]和查询区间[L, R]有重合部分。写成if (!(R < m + 1) && !(L > t))也行，不过没必要
        if (R > m) sum += range_sum(L, R, m + 1, t, p * 2 + 1);
        return sum;
    }

    void range_add(int L, int R, int val, int s, int t, int p) { // [L, R]为查询区间, val为要add的值, [s, t]为当前节点包含的区间, p为当前节点的编号
        if (L <= s && t <= R) {
            tree[p] += (t - s + 1) * val;
            lazy[p] += val; // 懒惰标记。如果当前区间是查询区间的子集则直接截住。一个节点的值是结合了标记之后的，是最新的。而lazy标记是在要访问子节点时下放。
            return; // 懒惰修改，这里直接就返回了
        }
        // 否则，需要向子节点细分，此时要先把标记下放，因为当前节点p的标记是懒惰标记没传给儿子，儿子的值不对
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        if (L <= m) range_add(L, R, val, s, m, p * 2);
        if (R > m) range_add(L, R, val, m + 1, t, p * 2 + 1);
        pushup(s, t, p); // 子节点更新后更新回来p
    }

    // 懒惰标记下放
    void pushdown(int s, int t, int p) {
        int m = s + ((t - s) >> 1);
        if (s != t && lazy[p] > 0) { // s==t代表是叶节点，叶节点没有儿子无需下放
            tree[p * 2] += (m - s + 1) * lazy[p];
            lazy[p * 2] += lazy[p];
            tree[p * 2 + 1] += (t - m) * lazy[p];
            lazy[p * 2 + 1] += lazy[p];
            lazy[p] = 0;
        }
    }

    // 从子节点更新当前节点
    void pushup(int s, int t, int p) {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

public:
    SegTreeRangeAddRangeSum(vector<int>& nums) {
        this->n = nums.size();
        // __builtin_clz()若参数为0，则结果是ub，这里要求n > 0
        /* 线段树有n个叶子(每个叶子代表的区间长度为1)，且一定是真二叉的。当n为2的幂次时，线段树一定是满的二叉树，有2n+1个节点；
        当n不为2的幂次时，线段树最终出来的结构不一定是完全二叉树，例如数组长度为6，但是倒数第二层一定是满的二叉树。
        虽然线段树不是完全二叉树，但是这只是意味着层序遍历的结果不是按编号每次加1递增，中间是有空位的。而父子的编号关系是直接定义的，仍然适用。
        
        要能充分容纳线段树的节点，vector<int> tree的size需要多大？
        考虑将n向上取为最近的2的幂次(例如n=15，补充到16)，则每经过一次二分，区间长度减半，则只需⌈logn⌉次，区间长度就会降到1，到达
        叶节点，因此，线段树的高度为⌈logn⌉(这里证明不严谨，具体证明见../线段树.md)，最多有2^(⌈logn⌉ + 1) - 1个节点，又因为tree存储线段树节点从下标1开始，因此tree的size需要
        为2^(⌈logn⌉ + 1)。

        oi wiki上提到: "如果你懒得计算的话可以直接把数组长度设为4n"
        tree存储线段树节点从下标1开始不是必须的(树状数组从1开始不用0号位置是必须的，因为要用lowbit)，可以从下标0开始，那样要把左右儿子位置
        对应改成2i + 1和2i + 2
        */
        tree.resize(2 << (32 - __builtin_clz(n)));
        lazy.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1); // 线段树的根设置在tree[1]位置，根节点管辖的数组区间为[0, n - 1]
    }

    int range_sum(int L, int R) { return range_sum(L, R, 0, n - 1, 1); }

    void range_add(int L, int R, int val) { return range_add(L, R, val, 0, n - 1, 1); }
};

/*
线段树建树的时间复杂度为O(n) (不过有动态开点线段树，节点只有在有需要的时候才被创建)

树高为O(logn) (因为每往下长一次区间长度减半，减到1就到叶子了)，节点规模为O(n)

建树的时间复杂度为O(n)

查询和修改的时间复杂度为O(logn)

查询和修改时，每次最多可能有两个递归分支，这样看来，时间复杂度有可能达到O(n)，但是能感觉出来，每次都要递归两个分支的情况并
不多，于是时间复杂度应该没有O(n)，如何证明？

参考<https://stackoverflow.com/questions/27185066/segment-tree-time-complexity-analysis>，每一层，需要递归下去的节点
最多只有2个，因此每层最多只有4个节点要访问，于是时间复杂度为O(logn)。

为什么每一层需要递归下去的节点最多只有两个？

第一层有一个节点

假设第二层需要递归2个节点

假设第二层的两个节点又都需要递归，于是第三层需要访问4个节点

第三层的这4个节点，需要递归下去的最多有几个？

这4个节点从左到右记为node1, node2, node3, node4。注意，我们需要访问node1和node4，说明我们要查询的区间左端点 <= node1左端点，
右端点 >= node4右端点，这就意味着，node2和node3所对应的区间是被查询区间完全包含的，由于懒惰传播的特性，访问node2和node3不会发
生递归（虽然暂时下面节点的值不对，但是会在后面需要访问时先下放标记进行更新）。

也就是说，每一层，partial overlap的节点只会有两个。于是，每一层需要递归下去的节点最多只有两个。
*/

int main(int argc, char const *argv[]) {
    vector<int> v = {1, 3, 4, 5, 7};
    SegTreeRangeAddRangeSum segTree(v);
    cout << segTree.range_sum(0, 3) << endl;
    cout << segTree.range_sum(0, 2) << endl;
    segTree.range_add(0, 2, 2);
    cout << segTree.range_sum(0, 2) << endl;
    return 0;
}
