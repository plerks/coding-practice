/*
参考: https://oi-wiki.org/ds/seg/
      https://www.bilibili.com/video/BV18t4y1p736/
*/

#include <bits/stdc++.h>

using namespace std;

// 要求set时提供的val > 0，因为要用lazy[p]的值是否>0来区分是否有懒惰标记
class SegTreeRangeSetRangeSum {
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

    int range_sum(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) return tree[p];
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        int sum = 0;
        if (L <= m) sum += range_sum(L, R, s, m, p * 2);
        if (R > m) sum += range_sum(L, R, m + 1, t, p * 2 + 1);
        return sum;
    }

    void range_set(int L, int R, int val, int s, int t, int p) {
        if (L <= s && t <= R) {
            tree[p] = (t - s + 1) * val;
            lazy[p] = val;
            return;
        }
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        if (L <= m) range_set(L, R, val, s, m, p * 2);
        if (R > m) range_set(L, R, val, m + 1, t, p * 2 + 1);
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
    SegTreeRangeSetRangeSum(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        lazy.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    int range_sum(int L, int R) { return range_sum(L, R, 0, n - 1, 1); }

    void range_set(int L, int R, int val) { return range_set(L, R, val, 0, n - 1, 1); }
};

int main(int argc, char const *argv[]) {
    vector<int> v = {1, 3, 4, 5, 7};
    SegTreeRangeSetRangeSum segTree(v);
    cout << segTree.range_sum(0, 3) << endl;
    cout << segTree.range_sum(0, 2) << endl;
    segTree.range_set(0, 2, 2);
    cout << segTree.range_sum(0, 2) << endl;
    cout << segTree.range_sum(0, 3) << endl;
    cout << segTree.range_sum(0, 4) << endl;
    return 0;
}
