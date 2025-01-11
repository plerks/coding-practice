/*
url: https://leetcode.cn/problems/sliding-subarray-beauty/description/
参考: https://leetcode.cn/problems/sliding-subarray-beauty/solutions/2241294/hua-dong-chuang-kou-bao-li-mei-ju-by-end-9mvl/
标签: 【题单】滑动窗口与双指针, 考虑值域
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2653 {
public:
    /* 我的解法，超时，716 / 717 个通过的测试用例。始终维持窗口全序来找第x小，但是不是每次排序，而是每次二分找插入和删除位置。
    时间复杂度O(klogk + (n-k+1)*logk) */
    vector<int> getSubarrayBeauty_tle(vector<int>& nums, int k, int x) {
        int n = nums.size();
        // 初始的窗口为[0, k - 1]
        int left = 0, right = k - 1;
        vector<int> t;
        for (int i = left; i < right; i++) {
            t.push_back(nums[i]);
        }
        sort(t.begin(), t.end());
        vector<int> ans(n - k + 1);
        while (left < n - k + 1) {
            // 搜索第一个 >= nums[right] 的位置
            int pos = lower_bound(t.begin(), t.end(), nums[right]) - t.begin();
            t.insert(t.begin() + pos, nums[right]);
            if (t[x - 1] < 0) ans[left] = t[x - 1];
            else ans[left] = 0;
            // 搜索第一个 >= nums[left]的位置，这里一定能搜索到等于
            pos = lower_bound(t.begin(), t.end(), nums[left]) - t.begin();
            t.erase(t.begin() + pos);
            left++;
            right++;
        }
        return ans;
    }

    /* 参考灵茶山艾府题解，值域很小所以考虑值域，然后用计数排序中计数的思想处理求窗口第x小的问题，
    直接枚举值域内每个数的出现次数
    */
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();
        // -50 <= nums[i] <= 50
        vector<int> cnt(101);
        // 先放进去k - 1个数
        for (int i = 0; i < k - 1; i++) {
            cnt[50 + nums[i]]++;
        }
        vector<int> ans(n - k + 1);
        for (int i = 0; i < n - k + 1; i++) {
            // 先把right加进来
            cnt[50 + nums[i + k - 1]]++;
            // 查找第x小，只需查找负数即可
            int xx = x;
            for (int val = 0; val < 50; val++) {
                xx -= cnt[val];
                if (xx <= 0) {
                    ans[i] = val - 50;
                    break;
                }
            }
            // left出去
            cnt[50 + nums[i]]--;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2653 solu;
    auto a = solu.getSubarrayBeauty(*new vector<int>{1,-1,-3,-2,3}, 3, 2);
    return 0;
}