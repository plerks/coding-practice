/*
url: https://www.luogu.com.cn/problem/P3374
相关: 典型问题/树状数组/单点add + 区间求和
标签: 树状数组, 模板
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
        // 更新各个关键区间
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
    int n, m;
    cin >> n >> m;
    vector<int> nums;
    while (n-- > 0) {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    Fenwick f(nums);
    while (m-- > 0) {
        int type;
        cin >> type;
        if (type == 1) {
            int x, k;
            cin >> x >> k;
            f.modify(x - 1, k);
        }
        else {
            int x, y;
            cin >> x >> y;
            cout << f.query(x - 1, y - 1) << endl;
        }
    }
    return 0;
}

/* 一个用例：
输入：
5 5
1 5 4 2 3
1 1 3
2 2 5
1 3 -1
1 4 2
2 1 4
输出：
14
16 */