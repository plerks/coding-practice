#include <bits/stdc++.h>

using namespace std;

class SegTreePointSetRangeMax {
private:
    vector<int> tree; // 单点修改，只会在叶节点上修改，无需懒惰标记
    int n;

    void build(vector<int>& nums, int s, int t, long long p) {
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

    void modify(int I, int val, int s, int t, long long p) { // I为要修改值的位置
        if (s == t) {
            tree[p] = val;
            return;
        }
        int m = s + ((t - s) >> 1);
        if (I <= m) modify(I, val, s, m, p * 2);
        if (I > m) modify(I, val, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    int query(int L, int R, int s, int t, long long p) {
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

    int query(int L, int R) { 
        if (L < 0 || R < 0) {
            int x = 1;
        }
        return query(L, R, 0, n - 1, 1); 
    }
};

class Solution3814 {
public:
    // 用值域线段树也可以通过，但是要2000多ms，很低效
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        int ans = 0;
        for (int i = 0; i < n; i++) { // 只选一台
            if (costs[i] < budget) ans = max(ans, capacity[i]);
        }
        vector<int> nums(1e5 + 1);
        SegTreePointSetRangeMax sgt(nums);
        for (int i = 0; i < n; i++) {
            // 1 <= costs[i], capacity[i] <= 10^5，x == 0 代表找不到合法的
            int x = budget - costs[i] - 1 <= 0 ? 0 : sgt.query(0, budget - costs[i] - 1);
            if (x != 0) ans = max(ans, capacity[i] + x);
            sgt.modify(costs[i], max(sgt.query(costs[i], costs[i]), capacity[i]));
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}