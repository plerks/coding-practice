/*
url: https://leetcode.cn/problems/find-if-array-can-be-sorted/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3011 {
public:
    bool canSortArray(vector<int>& nums) {
        int n = nums.size();
        int mx = 0; // 前一段的最大
        for (int i = 0; i < n;) {
            int tmi = nums[i];
            int tmx = nums[i];
            int cnt = __builtin_popcount(nums[i]);
            for (i++; i < n && __builtin_popcount(nums[i]) == cnt; i++) {
                tmi = min(tmi, nums[i]);
                tmx = max(tmx, nums[i]);
            }
            if (tmi < mx) return false;
            mx = tmx;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution3011 solu;
    cout << solu.canSortArray(*new vector<int>{8,4,2,30,15}) << endl;
    return 0;
}