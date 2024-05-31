/*
url: https://leetcode.cn/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/
LeetCode参考: https://leetcode.cn/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/solutions/2790603/fen-zhi-si-xiang-xian-duan-shu-pythonjav-xnhz/
相关: LeetCode198. 打家劫舍
标签: LeetCode第399场周赛, 线段树
*/

// 这次周赛3题

#include <bits/stdc++.h>

using namespace std;

// 单点修改的线段树
struct SegTree {
    vector<array<int, 4>> tree; // array的0123分别代表00 01 10 11
    int n;

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            tree[p][0] = 0;
            tree[p][1] = 0;
            tree[p][2] = 0;
            tree[p][3] = max(nums[s], 0);
            return;
        }
        int m = (s + t) / 2;
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    void pushup(int p) {
        tree[p] = {
            max(tree[p * 2][0] + tree[p * 2 + 1][2], tree[p * 2][1] + tree[p * 2 + 1][0]),
            max(tree[p * 2][0] + tree[p * 2 + 1][3], tree[p * 2][1] + tree[p * 2 + 1][1]),
            max(tree[p * 2][2] + tree[p * 2 + 1][2], tree[p * 2][3] + tree[p * 2 + 1][0]),
            max(tree[p * 2][2] + tree[p * 2 + 1][3], tree[p * 2][3] + tree[p * 2 + 1][1]),
        };
    }

    void modify(int index, int val, int s, int t, int p) {
        if (s == t) {
            tree[p][3] = max(0, val);
            return;
        }
        int m = (s + t) / 2;
        if (index <= m) modify(index, val, s, m, p * 2);
        if (index > m) modify(index, val, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    int query() { // 直接返回全区间打家劫舍的结果
        return tree[1][3];
        // return max({tree[1][0], tree[1][1], tree[1][2], tree[1][3]});
    }

    SegTree(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(4 * n);
        build(nums, 0, n - 1, 1);
    }
};

class Solution3165 {
public:
    /* 参考灵茶山艾府题解，容易看出来是打家劫舍，但是不同的是这题会修改，按打家劫舍的做法，修改之后重新算dp数组
    需要O(n)时间，会超时。打家劫舍加了要修改查询，所以要考虑把dp数组树化，让修改操作的时间复杂度为O(logn)。

    把nums二分为p, q两个子数组，然后分治。
    在递归的归的过程中合并结果，由于选数要不相邻，需要考虑子数组的选取情况。由于p的最右侧和q的最左侧一定会有一个不选，
    所以确定了哪个位置不选(或者都不选)后，另外一个位置就不用关心选取情况，选取或不选取都可以。(应该也能设成0不选1代表选，
    然后代码要改下)

    这里pq的例子p的最左和q的最右是不必考虑的，但是这两个位置的信息也要维护，因为p后面合并时可能作为右半区间。

    于是需要两个位来表示区间状态。

    用f00(A)表示A的最左侧不选，最右侧也不选 的最大收益
    f01(A)表示A的最左侧不选，最右侧可选可不选 的最大收益
    f10(A)表示A的最左侧可选可不选，最右侧不选 的最大收益
    f11(A)表示A的最左侧可选可不选，最右侧可选可不选 的最大收益

    f00(A) = max{ f00(p) + f10(q), f01(p) + f00(q) }
    f01(A) = max{ f00(p) + f11(q), f01(p) + f01(q) }
    f10(A) = max{ f10(p) + f10(q), f11(p) + f00(q) }
    f11(A) = max{ f10(p) + f11(q), f11(p) + f01(q) }
    */
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        SegTree segTree(nums);
        long long ans = 0;
        for (auto &q : queries) {
            segTree.modify(q[0], q[1], 0, n - 1, 1);
            ans += segTree.query();
        }
        return ans % (int)(1e9 + 7);
    }
};

int main(int argc, char const *argv[]) {
    Solution3165 solu;
    vector<int> nums = {3, 5, 9};
    vector<vector<int>> queries = {{1, -2}, {0, -3}};
    cout << solu.maximumSumSubsequence(nums, queries) << endl;
    return 0;
}
