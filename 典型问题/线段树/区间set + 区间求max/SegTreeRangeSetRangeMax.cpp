/*
参考: https://oi-wiki.org/ds/seg/
      https://www.bilibili.com/video/BV18t4y1p736/
相关: LeetCode3161. 物块放置查询
*/

#include <bits/stdc++.h>

using namespace std;

// 要求set时提供的val > 0，因为要用lazy[p]的值是否>0来区分是否有懒惰标记
class SegTreeRangeSetRangeMax {
private:
    vector<int> tree, lazy; // tree[p]是相应区间的最大值，lazy[p]是相应区间的lazy set值
    int n;

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            tree[p] = nums[s];
            return;
        }
        int m = s + ((t - s) >> 1);
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(p);
    }
    
    void pushup(int p) {
        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }

    void modify(int L, int R, int val, int s, int t, int p) {
        if (L <= s && t <= R) {
            tree[p] = val;
            lazy[p] = val;
            return;
        }
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        if (L <= m) modify(L, R, val, s, m, p * 2);
        if (R > m) modify(L, R, val, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    void pushdown(int s, int t, int p) {
        if (s != t && lazy[p] > 0) { // 这里要求set时提供的val > 0，因为要用lazy[p]的值是否>0来区分是否有懒惰标记
            tree[p * 2] = tree[p];
            lazy[p * 2] = lazy[p];
            tree[p * 2 + 1] = tree[p];
            lazy[p * 2 + 1] = lazy[p];
            lazy[p] = 0;
        }
    }

    int query(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) {
            return tree[p];
        }
        int m = s + ((t - s) >> 1);
        int mx = 0;
        if (L <= m) mx = max(mx, query(L, R, s, m, p * 2));
        if (R > m) mx = max(mx, query(L, R, m + 1, t, p * 2 + 1));
        return mx;
    }

public:
    SegTreeRangeSetRangeMax(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        lazy.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    void modify(int L, int R, int val) { modify(L, R, val, 0, n - 1, 1); }

    int query(int L, int R) { return query(L, R, 0, n - 1, 1); }
};

int main(int argc, char const *argv[]) {
    vector<int> v = {1, 3, 4, 5, 7};
    SegTreeRangeSetRangeMax segTree(v);
    cout << segTree.query(0, 2) << endl;
    segTree.modify(1, 2, 2);
    cout << segTree.query(0, 2) << endl;
    cout << segTree.query(0, 3) << endl;
    return 0;
}
