/*
url: https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
相关: LeetCode2762. 不间断子数组, LeetCode239. 滑动窗口最大值
标签: 【题单】滑动窗口与双指针, 单调队列
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1438 {
public:
    // 这题和LeetCode2762. 不间断子数组不一样，那题相当于limit为2，所以即使用map总时间复杂度也是线性的。这样写时间复杂度O(nloglimit)
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        map<int, int> mp;
        int ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            mp[nums[r]]++;
            while (mp.rbegin()->first - mp.begin()->first > limit) {
                mp[nums[l]]--;
                if (mp[nums[l]] == 0) mp.erase(nums[l]);
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }

    // 官方题解的单调队列解法，时间复杂度O(n)，用两个单调队列分别维护窗口最大值和最小值
    int longestSubarray_implementation2(vector<int>& nums, int limit) {
        int n = nums.size();
        deque<int> qMax, qMin;
        int l = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            while (!qMax.empty() && nums[qMax.back()] <= nums[r]) qMax.pop_back();
            while (!qMin.empty() && nums[qMin.back()] >= nums[r]) qMin.pop_back();
            qMax.push_back(r);
            qMin.push_back(r);
            // 这行不需要写排出头部过时元素的代码，初始时没有过时元素，当l++时，紧接着过时元素就被排出了
            while (nums[qMax.front()] - nums[qMin.front()] > limit) {
                l++;
                while (!qMax.empty() && qMax.front() < l) qMax.pop_front();
                while (!qMin.empty() && qMin.front() < l) qMin.pop_front();
                // 这里也可以写成：
                /* if (qMax.front() == l) qMax.pop_front();
                if (qMin.front() == l) qMin.pop_front();
                l++; */
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1438 solu;
    cout << solu.longestSubarray(*new vector<int>{8,2,4,7}, 4) << endl;
    cout << solu.longestSubarray_implementation2(*new vector<int>{8,2,4,7}, 4) << endl;
    return 0;
}