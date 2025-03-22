/*
url: https://leetcode.cn/problems/count-the-number-of-incremovable-subarrays-ii/
相关: LeetCode1574. 删除最短的子数组使剩余数组有序
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2972 {
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        int r = n - 1;
        while (r > 0 && nums[r - 1] < nums[r]) r--; // 这题是严格递增
        if (r == 0) return 1LL * n * (n + 1) / 2; // 原nums就是单增，那么就是非空子数组的个数
        // 枚举[0, l]作为删除后左部的单增部分
        ans += n - r + 1; // 左部为空
        for (int l = 0; l == 0 || nums[l - 1] < nums[l]; l++) {
            while (r < n && nums[r] <= nums[l]) r++;
            // [0, l] + [r, n)是单增的，可以有 n - r + 1种删除情况
            ans += n - r + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2972 solu;
    // cout << solu.incremovableSubarrayCount(*new vector<int>{1,2,3,4}) << endl;
    // cout << solu.incremovableSubarrayCount(*new vector<int>{6,5,7,8}) << endl;
    cout << solu.incremovableSubarrayCount(*new vector<int>{8,7,6,6}) << endl;
    return 0;
}