/*
url: https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/description/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1658 {
public:
    // 两侧之和为x，则中间有段的和为total - x，题目范围nums的元素，x都是正数，有单调性，可以滑窗
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int l = 0;
        int total = accumulate(nums.begin(), nums.end(), 0);
        int sum = 0;
        int ans = INT_MAX;
        for (int r = 0; r < n; r++) {
            sum += nums[r];
            while (l <= r && sum > total - x) {
                sum -= nums[l];
                l++;
            }
            if (sum == total - x) {
                ans = min(ans, n - (r - l + 1));
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1658 solu;
    cout << solu.minOperations(*new vector<int>{1,1,4,2,3}, 5) << endl;
    return 0;
}