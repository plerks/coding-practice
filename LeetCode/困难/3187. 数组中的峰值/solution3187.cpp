/*
url: https://leetcode.cn/problems/peaks-in-array/description/
LeetCode参考: https://leetcode.cn/problems/peaks-in-array/solutions/2812394/shu-zhuang-shu-zu-pythonjavacgo-by-endle-tj0w/
              https://www.bilibili.com/video/BV1T1421k7Hi/
标签: LeetCode第402场周赛, 线段树, 树状数组
*/

// 这次周赛3题，第4题做法是对的，但是线段树有个地方没调出来

#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    vector<int> tree;
    vector<int> nums;
    int n;

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            tree[p] = 0;
            return;
        }
        int m = (s + t) / 2;
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(p, s, m, t);
    }

    void pushup(int p, int s, int m, int t) {
        tree[p] = tree[2 * p] + tree[2 * p + 1];
        if (m - 1 >= s && m + 1 <= t && nums[m - 1] < nums[m] && nums[m] > nums[m + 1]) {
            tree[p]++;
        }
        if (m >= s && m + 2 <= t && nums[m] < nums[m + 1] && nums[m + 1] > nums[m + 2]) {
            tree[p]++;
        }
    }

    int query(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) {
            return tree[p];
        }
        int m = s + ((t - s) >> 1);
        int res = 0;
        if (L <= m) {
            res += query(L, R, s, m, p * 2);
            // 这里要测试m这个位置，必须要验证m - 1和m + 1这两个点既在[s, t]内，又在[L, R]内，周赛时只验证了一个，时间不够没调试出来
            if (m - 1 >= s && m + 1 <= t && m - 1 >= L && m + 1 <= R && nums[m - 1] < nums[m] && nums[m] > nums[m + 1]) {
                res++;
            }
        }
        if (R > m) {
            res += query(L, R, m + 1, t, p * 2 + 1);
            if (m >= s && m + 2 <= t && m >= L && m + 2 <= R && nums[m] < nums[m + 1] && nums[m + 1] > nums[m + 2]) {
                res++;
            }
        }
        return res;
    }

    void modify(int pos, int val, int s, int t, int p) {
        if (s == t && s == pos) {
            nums[s] = val;
            return;
        }
        int m = s + ((t - s) >> 1);
        if (pos <= m) modify(pos, val, s, m, p * 2);
        if (pos > m) modify(pos, val, m + 1, t, p * 2 + 1);
        pushup(p, s, m, t);
    }

    SegTree(vector<int>& nums) {
        this->n = nums.size();
        this->nums = nums;
        tree.resize(4 * n);
        build(nums, 0, n - 1, 1);
    }
};

struct Fenwick {
    vector<int> tree;
    vector<int> nums;

    Fenwick(vector<int>& zeroOne) {
        int n = zeroOne.size();
        tree.resize(n + 1);
        nums = zeroOne;
        for (int i = 1; i < tree.size(); i++) {
            tree[i] += nums[i - 1];
            if (i + (i & -i) < tree.size()) tree[i + (i & -i)] += tree[i];
        }
    }

    void modify(int index, int val) {
        int diff = val - nums[index];
        for (int i = index + 1; i < tree.size(); i += (i & -i)) {
            tree[i] += diff;
        }
        nums[index] = val;
    }

    int query(int L, int R) {
        return pre(R + 1) - pre(L);
    }

    int pre(int i) {
        int sum = 0;
        while (i >= 1) {
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }
};

class Solution3187 {
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        SegTree segTree(nums);
        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                int t = segTree.query(q[1], q[2], 0, n - 1, 1);
                ans.push_back(t);
            }
            else {
                segTree.modify(q[1], q[2], 0, n - 1, 1);
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法，用树状数组，把nums峰值元素记为1，非峰值元素记为0，则转化为求区间和
    vector<int> countOfPeaks_implementation2(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> zeroOne(n);
        for (int i = 1; i <= n - 2; i++) {
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
                zeroOne[i] = 1;
            }
        }
        Fenwick f(zeroOne);
        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                if (q[2] - q[1] + 1 < 3) {
                    ans.push_back(0);
                    continue;
                }
                int t = f.query(q[1] + 1, q[2] - 1);
                ans.push_back(t);
            }
            else {
                int index = q[1], val = q[2];
                nums[index] = val;
                // 修改之后index，index - 1，index + 1三个位置受到影响
                if (index - 1 >= 0 && index + 1 < n && nums[index - 1] < nums[index] && nums[index] > nums[index + 1]) {
                    f.modify(index, 1);
                }
                else if (index - 1 >= 0 && index + 1 < n) f.modify(index, 0);

                if (index - 2 >= 0 && index < n && nums[index - 2] < nums[index - 1] && nums[index - 1] > nums[index]) {
                    f.modify(index - 1, 1);
                }
                else if (index - 2 >= 0 && index < n) f.modify(index - 1, 0);

                if (index >= 0 && index + 2 < n && nums[index] < nums[index + 1] && nums[index + 1] > nums[index + 2]) {
                    f.modify(index + 1, 1);
                }
                else if (index >= 0 && index + 2 < n) f.modify(index + 1, 0);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3187 solu;
    vector<int> nums = {7,10,7};
    vector<vector<int>> queries = {{1,2,2},{2,0,6},{1,0,2}};
    auto a = solu.countOfPeaks(nums, queries);
    auto b = solu.countOfPeaks_implementation2(nums, queries);
    return 0;
}
