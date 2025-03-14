/*
url: https://leetcode.cn/problems/count-subarrays-where-max-element-appears-at-least-k-times/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2962 {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        long long ans = 0;
        int l = 0;
        int cnt = 0;
        for (int r = 0; r < n; r++) {
            if (nums[r] == mx) cnt++;
            while (cnt >= k) {
                if (nums[l] == mx) cnt--;
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2962 solu;
    cout << solu.countSubarrays(*new vector<int>{1,3,2,3,3}, 2) << endl;
    return 0;
}