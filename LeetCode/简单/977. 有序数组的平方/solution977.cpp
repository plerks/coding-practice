/*
url: https://leetcode.cn/problems/squares-of-a-sorted-array/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution977 {
public:
    // 我的解法
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int pos = -1;
        int mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (nums[i] * nums[i] < mn) {
                pos = i;
                mn = nums[i] * nums[i];
            }
        }
        int l, r;
        if (nums[pos] == 0) {
            l = pos;
            r = pos + 1;
        }
        else {
            if (nums[pos] > 0) {
                l = pos - 1;
                r = pos;
            }
            else {
                l = pos;
                r = pos + 1;
            }
        }
        vector<int> ans;
        while (l >= 0 && r <= n - 1) {
            if (abs(nums[l]) < abs(nums[r])) {
                ans.push_back(nums[l] * nums[l]);
                l--;
            }
            else {
                ans.push_back(nums[r] * nums[r]);
                r++;
            }
        }
        while (l >= 0) {
            ans.push_back(nums[l] * nums[l]);
            l--;
        }
        while (r <= n - 1) {
            ans.push_back(nums[r] * nums[r]);
            r++;
        }
        return ans;
    }

    // 灵茶题解写法，双指针从两边往中间移动，就不用麻烦的初始化了
    vector<int> sortedSquares_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        int l = 0, r = n - 1;
        for (int p = n - 1; p >= 0; p--) {
            if (nums[l] * nums[l] > nums[r] * nums[r]) {
                ans[p] = nums[l] * nums[l];
                l++;
            }
            else {
                ans[p] = nums[r] * nums[r];
                r--;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution977 solu;
    auto a = solu.sortedSquares(*new vector<int>{-4,-1,0,3,10});
    return 0;
}