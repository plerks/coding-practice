/*
url: https://leetcode.cn/problems/count-the-number-of-good-subarrays/
标签: 【题单】滑动窗口与双指针, 动态维护
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2537 {
public:
    long long countGood(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mp; // 记录当前窗口元素出现频率
        long long cnt = 0; // 窗口好子数组数量
        long long ans = 0;
        int l = 0;
        for (int r = 0; r < n; r++) {
            cnt += mp[nums[r]];
            mp[nums[r]]++;
            while (cnt >= k) {
                cnt -= mp[nums[l]] - 1;
                mp[nums[l]]--;
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2537 solu;
    cout << solu.countGood(*new vector<int>{3,1,4,3,2,2,4}, 2) << endl;
    return 0;
}