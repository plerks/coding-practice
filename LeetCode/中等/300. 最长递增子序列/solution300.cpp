/*
url: https://leetcode.cn/problems/longest-increasing-subsequence/
相关: LeetCode3825. 按位与结果非零的最长上升子序列
*/

#include <bits/stdc++.h>

using namespace std;

class Solution300 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> d; // (长度，最小结尾值)
        // 看 < x 的最后那个点 d[j - 1]，考虑 d[j - 1] + x 是否能更新 d[j]
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = lower_bound(d.begin(), d.end(), x);
            if (it != d.end()) *it = x;
            else d.push_back(x);
        }
        return d.size();
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}