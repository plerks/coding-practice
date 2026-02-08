/*
url: https://leetcode.cn/problems/count-subarrays-with-cost-less-than-or-equal-to-k/
相关: LeetCode239. 滑动窗口最大值
标签: LeetCode第488场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3835 {
public:
    // 周赛时的解法，由于子数组扩大，min能更小，max能更大，r - l + 1能更大，更不满足(max(nums[l..r]) - min(nums[l..r])) * (r - l + 1) <= k，
    // 因此有单调性，可以滑窗。
    // 为了维护滑窗中的max和min，可以用个map，时间复杂度 O(nlogn)
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        map<int, int> mp;
        long long ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            mp[nums[r]]++;
            // 这里不用判断 l <= r，l == r 时一定合法，窗口不会再缩了
            while (l <= r && (mp.rbegin()->first - mp.begin()->first) * 1LL * (r - l + 1) > k) {
                mp[nums[l]]--;
                if (mp[nums[l]] == 0) mp.erase(nums[l]);
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }

    // 参考灵茶题解，用两个单调队列维护滑窗的max和min，时间复杂度 O(n)
    long long countSubarrays_impl2(vector<int>& nums, long long k) {
        int n = nums.size();
        deque<int> minq;
        deque<int> maxq;
        long long ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            while (!minq.empty() && nums[minq.back()] >= nums[r]) minq.pop_back();
            minq.push_back(r);
            while (!maxq.empty() && nums[maxq.back()] <= nums[r]) maxq.pop_back();
            maxq.push_back(r);

            while ((nums[maxq.front()] - nums[minq.front()]) * 1LL * (r - l + 1) > k) {
                l++;
                if (minq.front() < l) minq.pop_front(); // 每次都及时删除单调队列中过时的元素，所以这里最多只需要做一次，不过改成while也不会错
                if (maxq.front() < l) maxq.pop_front();
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}