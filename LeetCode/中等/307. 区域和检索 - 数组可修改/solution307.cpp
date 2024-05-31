/*
url: https://leetcode.cn/problems/range-sum-query-mutable/description/
相关: 典型问题/线段树/区间set + 区间求和, 典型问题/树状数组/单点set + 区间求和
标签: 线段树, 模板
*/

#include <bits/stdc++.h>

using namespace std;

// 使用典型问题/线段树/区间set + 区间求和的代码，把[L, R]设置成一样就是单点set
class NumArray {
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
    NumArray(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        lazy.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    int sumRange(int L, int R) { return range_sum(L, R, 0, n - 1, 1); }

    void update(int index, int val) { return range_set(index, index, val, 0, n - 1, 1); }
};

// 使用典型问题/树状数组/单点set + 区间求和的代码
class NumArray_implementation2 {
private:
    vector<int> nums;
    vector<int> tree;

    int lowbit(int x) { return x & -x; }

    int prefixSum(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }

public:
    NumArray_implementation2(vector<int>& _nums) : nums(_nums), tree(_nums.size() + 1) {
        // tree[0]位置不用，从1开始。因为要对i使用lowbit()，如果tree[0]也要使用的话i到了0之后i -= lowbit(i)会一直保持为0，在prefixSum()中会死循环
        for (int i = 1; i <= nums.size(); i++) {
            tree[i] += nums[i - 1]; // tree[i]直接加上nums[i - 1]即可，前面的部分已经在前面的循环中加了
            if (i + lowbit(i) <= nums.size()) tree[i + lowbit(i)] += tree[i]; // tree[i + lowbit(i)]的范围包含tree[i]，直接加进去
        }
    }

    void update(int index, int val) {
        int diff = val - nums[index];
        nums[index] = val;
        for (int i = index + 1; i < tree.size(); i = i + lowbit(i)) {
            tree[i] += diff;
        }
    }

    int sumRange(int L, int R) {
        return prefixSum(R + 1) - prefixSum(L);
    }
};

int main(int argc, char const *argv[]) {
    vector<int> v = {1, 3, 5};
    NumArray segTree(v);
    cout << segTree.sumRange(0, 2) << endl;
    segTree.update(1, 2);
    cout << segTree.sumRange(0, 2) << endl;

    NumArray_implementation2 f(v);
    cout << f.sumRange(0, 2) << endl;
    f.update(1, 2);
    cout << f.sumRange(0, 2) << endl;
    return 0;
}
