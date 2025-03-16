/*
url: https://leetcode.cn/problems/find-subarray-with-bitwise-and-closest-to-k/description/
LeetCode参考: https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/solutions/343107/zhao-dao-zui-jie-jin-mu-biao-zhi-de-han-shu-zhi-by/
              https://www.bilibili.com/video/BV1Qx4y1E7zj/
相关: LeetCode1521. 找到最接近目标值的函数值, LeetCode2401. 最长优雅子数组
标签: LeetCode第400场周赛, 子数组, 位运算, logtrick, 二分查找, 线段树
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
    // 这题之前周赛题面是AND，现在一看力扣改成OR了，以下是按AND来写的代码
    // AND的话相当于nums[i]1的个数不断减少，OR的话相当于nums[i]0的个数不断减少，gcd的话相当于nums[i]的素因子的个数不断减少
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
                    /* 如果nums[j...i-1]与nums[j...i]相同，即 nums[j] & x 与 nums[j]的旧值 一样，则j往左就没必要再做了。
                    因为nums[i]对于[j...i-1]，相当于一个全1的数，或者说相当于个单位元。
                    nums[x...i]一定和nums[x...i-1]相同，不需要去计算。具体来说，
                    nums[x...i] = nums[x...j-1] & nums[j...i] = nums[x...j-1] & nums[j...i-1] = nums[x...j-1]
                    */
                    /* 每一次内层循环，新旧nums[j]相同（即 nums[j...i-1] 与 nums[j...i-1] & x 相同）是否会迅速发生？
                    是，对于每个nums[j]，其在新一轮中会多&当前的nums[i](记为x)，如果新值nums[j] & x == 旧值nums[j]，则
                    内层循环结束。否则，新num[j]代表的&序列多&了一个数，其中1的个数一定会减小，而最多减少logU次就会变成0，然后
                    就一定会相等了。也就是说，每个位置nums[j]最多减少logU次，其挡不住内层循环继续向左的次数为logU，总时间复杂度O(nlogU)。
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

    /* 灵茶题解的滑窗解法，时间复杂度O(n)，
    注意: 本题力扣改过题面，题目从AND改成了OR，以下是按OR写的代码。
    固定右端点，越往左，or的值越大，有单调性可以滑窗。但是，由于或没有逆运算，（此题不像LeetCode2401那样特殊），
    所以当移出nums[l]时，无法得知or应该改成多少，所以要用一个栈，暂存结果。
    栈中存储[r - 1, r - 1], [r - 2, r - 1]...的|结果，当r加入时，while (st.top() | nums[r] > k)，就出栈尝试更新ans。
    当到r + 1时，前面出栈的部分如果|nums[r + 1]只会更大，不会成为最优解，要关心的是剩余部分 < k的部分|nums[r + 1]变大后能更
    靠近k。但是这部分栈里的数还没| nums[r]，所以用一个right_or记录右侧一段的or值。
    用bottom记录分隔线的位置，当栈中元素都出栈后，要把[r - 1, r], [r - 2, r] ... [bottom, r]重新入栈。
    栈可以直接在nums上原地修改，不需要单调创建一个栈，用nums[l]表示[l, bottom]的|。
    */
    int minimumDifference_implementation4(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = INT_MAX;
        int l = 0;
        int bottom = 0; // bottom是最后一个计算了后缀or的右边界
        int right_or = 0;
        for (int r = 0; r < n; r++) {
            right_or |= nums[r];
            while (l <= r && (nums[l] | right_or) >= k) { // nums[l] | right_or可能重复|了nums[r]，但是不影响值
                ans = min(ans, (nums[l] | right_or) - k);
                l++;
                if (l > bottom) { // 如果越过了分隔线的话，栈中元素要重新计算
                    for (int j = r - 1; j >= l; j--) {
                        nums[j] |= nums[j + 1];
                    }
                    right_or = 0;
                    bottom = r;
                }
            }
            // 第一个<k的，可能成为最优解
            if (l <= r) ans = min(ans, k - (nums[l] | right_or));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3171 solu;
    // cout << solu.minimumDifference(*new vector<int>{1,2,4,5}, 3) << endl;

    cout << solu.minimumDifference_implementation4(*new vector<int>{1,3,1,3}, 2) << endl;
    return 0;
}
