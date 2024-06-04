/*
url: https://leetcode.cn/problems/find-subarray-with-bitwise-and-closest-to-k/description/
LeetCode参考: https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/solutions/343107/zhao-dao-zui-jie-jin-mu-biao-zhi-de-han-shu-zhi-by/
              https://www.bilibili.com/video/BV1Qx4y1E7zj/
相关: LeetCode1521. 找到最接近目标值的函数值
标签: LeetCode第400场周赛, 子数组, 位运算, 二分查找, 线段树
*/

// 这次周赛3题

#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    vector<int> tree;
    int n;

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            tree[p] = nums[s];
            return;
        }
        int m = (s + t) / 2;
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    void pushup(int p) {
        tree[p] = tree[2 * p] & tree[2 * p + 1];
    }

    int query(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) {
            return tree[p];
        }
        int m = s + ((t - s) >> 1);
        int res1 = -1, res2 = -1;
        if (L <= m) res1 = query(L, R, s, m, p * 2);
        if (R > m) res2 = query(L, R, m + 1, t, p * 2 + 1);
        return res1 & res2;
    }

    SegTree(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(4 * n);
        build(nums, 0, n - 1, 1);
    }
};

// 此题与`LeetCode1521. 找到最接近目标值的函数值`完全相同
class Solution3171 {
public:
    /* 周赛时的做法，用线段树暴力枚举所有子数组，使用线段树维护区间&结果以快速求区间&，时间复杂度O(n^2 * logn)，804 / 813 个通过的测试用例，超时
    实际这样做还不如i从0->n枚举，j从i->0枚举，然后一步步算&的结果，这样时间复杂度O(n^2)，试了下这样能过807个用例 */
    int minimumDifference_time_limit_exceeded(vector<int>& nums, int k) {
        int n = nums.size();
        SegTree segTree(nums);
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int andValue = segTree.query(i, j, 0, n - 1, 1);
                ans = min(ans, abs(andValue - k));
                if (andValue <= k) break;
            }
        }
        return ans;
    }

    /* 用二分的思路，对于给定的右端点，左端点越往左，&的结果越小，存在单调性，用二分找第一个&结果>=k和最后一个<=k的位置。
    时间复杂度O(n * logn * logn)，需要用线段树快速求区间&的结果 */
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        SegTree segTree(nums); // 用线段树求区间&结果
        int ans = INT_MAX;

        // 找最后一个结果<=k的
        for (int i = 0; i < n; i++) {
            int left = 0, right = i;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (segTree.query(mid, i, 0, n - 1, 1) <= k) {
                    left = mid + 1;
                }
                else right = mid - 1;
            }
            int pos = left - 1;
            if (pos >= 0) ans = min(ans, abs(segTree.query(pos, i, 0, n - 1, 1) - k));

            // 对于第一个结果>=k的，只需要额外尝试pos + 1即可
            if (pos + 1 < n) ans = min(ans, abs(segTree.query(pos + 1, i, 0, n - 1, 1) - k));
        }
        return ans;
    }

    /* LeetCode3171官方题解的做法，考虑以j为右端点，假设所有以j为右端点的子数组已经算出了&值，考虑以j + 1为右端点的子数组，
    其为nums[j + 1] & 上以j为右端点的子数组的不重复值。用一个set去记录以j为右端点的结果，然后用nums[j + 1]去&，从nums[j + 1]
    开始，越往左1的个数越少(或不变)，所以这个set不会太大，不超过32个。
    */
    int minimumDifference_implementation2(vector<int>& nums, int k) {
        unordered_set<int> *set = new unordered_set<int>();
        unordered_set<int> *setNew = new unordered_set<int>();
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            ans = min(ans, abs(nums[i] - k));
            setNew->insert(nums[i]);
            for (int pre : *set) {
                ans = min(ans, abs((nums[i] & pre) - k));
                setNew->insert(nums[i] & pre);
            }
            set->clear();
            swap(set, setNew);
        }
        return ans;
    }

    // 灵茶山艾府题解解法，不需要额外空间，视频讲解里还提到，如果把题面中的用&改成用|或者gcd也可以做(都有一定单调性)
    int minimumDifference_implementation3(vector<int>& nums, int k) {
        int ans = INT_MAX;
        // 用nums[j]存nums[j...i]的&结果
        for (int i = 0; i < nums.size(); i++) {
            // 现在nums[j]是nums[j...i-1] &的结果
            ans = min(ans, abs(nums[i] - k));
            // 现在要考虑以i为右端点的所有情况，左端点会有i种，但不需要全部算
            for (int j = i - 1; j >= 0; j--) {
                int temp = nums[j] & nums[i];
                if (temp == nums[j]) {
                    /* 如果nums[j...i-1]与nums[j...i]相同，则j往左就没必要再做了。
                    因为nums[i]对于[j...i-1]，相当于一个全1的数，或者说相当于个单位元。
                    nums[x...i]一定和nums[x...i-1]相同，不需要去计算。具体来说，
                    nums[x...i] = nums[x...j-1] & nums[j...i] = nums[x...j-1] & nums[j...i-1] = nums[x...j-1]
                    */
                    break;
                }
                ans = min(ans, abs(temp - k));
                nums[j] = temp; // 把nums[j]变为nums[j...i] &的结果
                /* 由于在nums[j] != nums[j] & nums[i]的情况下把nums[j]变成了nums[j] & nums[i]，nums[j]一定会严格变小，
                题目nums[i] <= 10^9，2^29 < 10^9 < 2^30，nums[j]最多30个1，因此所有nums[j]减小次数最多30次，虽然循环是二重的，
                但是这里的时间复杂度是O(30 * n)
                */
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3171 solu;
    vector<int> nums = {1,2,4,5};
    cout << solu.minimumDifference(nums, 3) << endl;
    return 0;
}
