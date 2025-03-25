/*
url: https://leetcode.cn/problems/maximum-frequency-of-an-element-after-performing-operations-ii/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3347 {
public:
    /* 我能想到的，关键在于当变成的值非nums中的元素时，应该尝试哪些值。
    */
    int maxFrequency_wa(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<int, int> mp;
        for (int x : nums) mp[x]++;
        int ans = 0;

        auto testx = [&](int x) {
            int index1 = lower_bound(nums.begin(), nums.end(), x - k) - nums.begin();
            int index2 = upper_bound(nums.begin(), nums.end(), x + k) - nums.begin() - 1;
            int cnt = min(numOperations, index2 - index1 + 1 - mp[x]); // 能变x的数的数量
            ans = max(ans, mp[x] + cnt);
        };

        for (int i = 0; i < n; i++) { // 枚举nums[i]为元素，能变nums[i]的数范围为[nums[i] - k, nums[i] + k]
            int x = nums[i];
            testx(x);
            if (i < n - 1) testx((nums[i] + nums[i + 1]) / 2);
        }
        return ans;
    }

    /* 参考灵茶题解与TsReaper题解<https://leetcode.cn/problems/maximum-frequency-of-an-element-after-performing-operations-ii/solutions/2983200/mei-ju-by-tsreaper-4ndy/>，
    每个x有个变的范围[x - k, x + k]，重合次数最高的点y就是最优解要变成的值，这个最优解要么是段区间，要么是个点，因此，额外要枚举的变化
    可能就是每个nums[i] - k（或者nums[i] + k）
    */
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<int, int> mp;
        for (int x : nums) mp[x]++;
        int ans = 0;

        auto testx = [&](int x) {
            int index1 = lower_bound(nums.begin(), nums.end(), x - k) - nums.begin();
            int index2 = upper_bound(nums.begin(), nums.end(), x + k) - nums.begin() - 1;
            int cnt = min(numOperations, index2 - index1 + 1 - mp[x]); // 能变x的数的数量
            ans = max(ans, mp[x] + cnt);
        };

        for (int i = 0; i < n; i++) { // 枚举nums[i]为元素，能变nums[i]的数范围为[nums[i] - k, nums[i] + k]
            int x = nums[i];
            testx(x);
            testx(nums[i] - k); // 写testx((long long)nums[i] + k);也行，不过要开long long，这题范围可能溢出，x, k都是1e9规模，nums[i] + k进testx()，里面会再加一次k，会溢出
        }
        return ans;
    }

    // 灵茶题解解法一，用差分数组，通过差分数组端点计数的方式，统计每个基区间的区间覆盖数。时间复杂度O(nlogn)，运行用时1419ms。
    int maxFrequency_implementation2(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> cnt;
        map<int, int> diff;
        for (int x : nums) {
            cnt[x]++;
            diff[x]; // 把x加入diff，但是增量为0，只是为了后面能遍历到x，因为有numOperations的限制，重叠次数最大不一定能确实做，要考虑所有x点
            diff[x - k]++;
            diff[x + k + 1]--;
        }
        int ans = 0;
        int sum = 0;
        for (auto &[x, d] : diff) {
            sum += d; // 当前位置重叠数
            ans = max(ans, cnt[x] + min(numOperations, sum - cnt[x]));
        }
        return ans;
    }

    /* 灵茶题解解法二，对于变成nums中的数，用三指针求[x - k, x + k]内的数有多少个，
    对于变成非nums中的数，总有一个数是变化的数中最大的，枚举这个数，然后求[x - 2k, x]中的数有多少个，
    这些是能通过操作变成相等的数(x - k)
    时间复杂度O(nlogn)，运行用时59ms。
    */
    int maxFrequency_implementation3(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 0;
        int l = 0, r = 0;
        int cnt = 0; // 统计x的个数
        // 变成nums中的数
        for (int m = 0; m < n; m++) {
            int x = nums[m];
            cnt++;
            if (m < n - 1 && nums[m + 1] == x) { // 统计x的出现次数
                continue;
            }
            while (nums[l] < x - k) l++;
            while (r < n && nums[r] <= x + k) r++;
            // [l, r)
            ans = max(ans, min(r - l, cnt + numOperations)); // 要么全变，要么部分变
            cnt = 0;
        }

        if (ans >= numOperations) return ans; // 变成非nums中的数最多只能达到numOperations个

        // 变成非nums中的数
        l = 0;
        for (int r = 0; r < n; r++) {
            int x = nums[r];
            while (nums[l] < x - 2 * k) l++;
            // [l, r]
            ans = max(ans, min(r - l + 1, numOperations)); // 要么全变，要么部分变
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3347 solu;
    // cout << solu.maxFrequency(*new vector<int>{1,4,5}, 1, 2) << endl;
    // cout << solu.maxFrequency(*new vector<int>{5,64}, 42, 2) << endl;
    // cout << solu.maxFrequency(*new vector<int>{1,78,70}, 39, 3) << endl;
    cout << solu.maxFrequency(*new vector<int>{999999997,999999999,999999999}, 999999999, 2) << endl;
    return 0;
}