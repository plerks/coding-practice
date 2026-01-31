/*
参考: https://www.bilibili.com/video/BV14r421W7oR/
      https://leetcode.cn/problems/range-sum-query-mutable/solutions/2524481/dai-ni-fa-ming-shu-zhuang-shu-zu-fu-shu-lyfll/
      https://oi-wiki.org/ds/fenwick/
相关: 洛谷P3374 【模板】树状数组 1
*/

#include <bits/stdc++.h>

using namespace std;

// 单点add + 区间求和的树状数组。
class Fenwick {
private:
    vector<int> nums;
    vector<int> tree;

    int lowbit(int x) { return x & -x; }

    // 拆分为关键区间求nums[0...i-1]之和，注意这里i已经是+1了的
    int prefixSum(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i); // i -= lowbit(i)等价于i &= i - 1
        }
        return sum;
    }

public:
    Fenwick(vector<int>& _nums) : nums(_nums), tree(_nums.size() + 1) {
        // tree[0]位置不用，从1开始。因为要对i使用lowbit()，如果tree[0]也要使用的话i到了0之后i -= lowbit(i)会一直保持为0，在prefixSum()中会死循环
        for (int i = 1; i <= nums.size(); i++) {
            tree[i] += nums[i - 1]; // tree[i]直接加上nums[i - 1]即可，前面的部分已经在前面的循环中加了
            if (i + lowbit(i) <= nums.size()) tree[i + lowbit(i)] += tree[i]; // tree[i + lowbit(i)]的范围包含tree[i]，直接加进去
        }
    }

    // 将nums[index]增加val
    void modify(int index, int val) {
        int diff = val;
        nums[index] += val;
        // 更新各个关键区间，i + lowbit(i) 为父节点
        for (int i = index + 1; i < tree.size(); i = i + lowbit(i)) {
            tree[i] += diff;
        }
    }

    // 求nums[L...R]之和，注意[L...R]要处理成[L+1...R+1]
    int query(int L, int R) {
        return prefixSum(R + 1) - prefixSum(L);
    }
};

int main(int argc, char const *argv[]) {
    vector<int> nums = {1, 3, 5};
    Fenwick f(nums);
    cout << f.query(0, 2) << endl;
    f.modify(1, 2);
    cout << f.query(0, 2) << endl;
    return 0;
}
