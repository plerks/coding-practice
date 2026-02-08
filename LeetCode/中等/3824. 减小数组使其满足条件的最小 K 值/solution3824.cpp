/*
url: https://leetcode.cn/problems/minimum-k-to-reduce-array-within-limit/
标签: LeetCode第175场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3824 {
public:
    // 双周赛时的写法。
    int minimumK(vector<int>& nums) {
        int n = nums.size();
        // bool all_neg_or_zero = true;
        // for (int i = 0; i < n; i++) {
        //     if (nums[i] > 0) all_neg_or_zero = false;
        // }
        // if (all_neg_or_zero) return 0;

        int left = 1, right = 1e5 + 1;

        auto check = [&](int k) {
            long long cnt = 0;
            for (int i = 0; i < n; i++) {
                if (nums[i] <= 0) continue;
                cnt += (nums[i] + k - 1) / k; // 注意 left 不能取 0 ，否则这里除 0 了，但是题目 nums[i] 全为正，所以答案不会为 0 ，不会漏 0
            }
            return cnt <= (long long)k * k;
        };

        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    /* 参考灵茶题解，优化边界，
    nums[i] >= 1，每个元素至少操作一次，所以操作次数 >= n，n <= k^2，所以 ans >= ⌈sqrt(n)​⌉
    取 k 的上边界为 M，此时需要的操作次数为 n ，n <= M^2 吗？（注意此时右边界 M 有可能比 左边界 更小）
    当 M >= sqrt(n) 时是的，
    当 M < sqrt(n) 时，回答为否，此时 [left, right] 为空，但是 left >= M，所以每个数操作 1 次就够，
    操作次数为 n，且 n <= (left = ⌈sqrt(n)​⌉)^2，left 刚好为答案。
    (按理来说右边界不能取这么一个回答不确定的值，但是左边界这样取又是刚好的，左边界要是单纯取 1 反而对这个右边界取法会出问题，
    左边界要够大，这样当 M < ans 时，才能靠左边界在右边而保证搜索到 ans。)
    */

    // 很奇妙，不过这样选一个回答不确定的右边界分析很麻烦，不如直接 left = 1, right = max(⌈sqrt(n)​⌉, M)
    int minimumK_impl2(vector<int>& nums) {
        int n = nums.size();

        int M = *max_element(nums.begin(), nums.end());
        int left = ceil(sqrt(n)), right = M;

        auto check = [&](int k) {
            long long cnt = 0;
            for (int i = 0; i < n; i++) {
                if (nums[i] <= 0) continue;
                cnt += (nums[i] + k - 1) / k;
            }
            return cnt <= (long long)k * k;
        };

        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    /* 参考灵茶题解，再优化边界，
    ∑⌈nums[i] / k​⌉ <= k^2 ，而 ∑nums[i] / k​ <= ∑⌈nums[i] / k​⌉，所以 ∑nums[i] / k​ <= k^2，k^3 >= ∑nums[i]
    所以取下边界 low = max(⌈sqrt(n)​⌉, ⌈cbrt(sum(nums))​⌉)
    取上边界 high = ⌈k 取为 low 时的操作次数(op_cnt(low))​⌉，只要 high >= low，则有 op_cnt(high) <= op_cnt(low) <= high^2，
    说明 high 是满足的；
    若 high < low，则会和上面一样，搜索区间为空，但是此时 op_cnt(low) < low^2 ，初始的 left 就是答案
    */
    int minimumK_impl3(vector<int>& nums) {
        int n = nums.size();
        long long sum = accumulate(nums.begin(), nums.end(), 0LL);

        auto op_cnt = [&](int k) {
            long long cnt = 0;
            for (int i = 0; i < n; i++) {
                if (nums[i] <= 0) continue;
                cnt += (nums[i] + k - 1) / k;
            }
            return cnt;
        };

        int left = max(ceil(sqrt(n)), ceil(cbrt(sum)));
        int right = ceil(op_cnt(left));
        while (left <= right) {
            int mid = (left + right) / 2;
            if (op_cnt(mid) > (long long)mid * mid) left = mid + 1;
            else right = mid - 1; 
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution3824 solu;
    cout << solu.minimumK_impl2(*new vector<int>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}) << endl;
    return 0;
}