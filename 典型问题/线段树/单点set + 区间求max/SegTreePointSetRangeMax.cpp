/*
参考: https://oi-wiki.org/ds/seg/
      https://www.bilibili.com/video/BV18t4y1p736/
相关: LeetCode3161. 物块放置查询
*/

#include <bits/stdc++.h>

using namespace std;

// 单点修改 + 区间求max，功能被区间set + 区间求max的线段树覆盖，把[L, R]设置成一样就是单点set，但像`LeetCode3161. 物块放置查询`灵茶山艾府题解也用到了这类线段树，所以也写下
class SegTreePointSetRangeMax {
private:
    vector<int> tree; // 单点修改，只会在叶节点上修改，无需懒惰标记
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

    void modify(int I, int val, int s, int t, int p) { // I为要修改值的位置
        if (s == t) {
            tree[p] = val;
            return;
        }
        int m = s + ((t - s) >> 1);
        if (I <= m) modify(I, val, s, m, p * 2);
        if (I > m) modify(I, val, m + 1, t, p * 2 + 1);
        pushup(p);
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
    SegTreePointSetRangeMax(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    void modify(int I, int val) { modify(I, val, 0, n - 1, 1); }

    int query(int L, int R) { return query(L, R, 0, n - 1, 1); }
};

int main(int argc, char const *argv[]) {
    vector<int> v = {1, 3, 4, 5, 7};
    SegTreePointSetRangeMax segTree(v);
    cout << segTree.query(0, 2) << endl;
    segTree.modify(1, 6);
    cout << segTree.query(0, 3) << endl;
    cout << segTree.query(0, 4) << endl;
    return 0;
}
