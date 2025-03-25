/*
url: https://leetcode.cn/problems/adjacent-increasing-subarrays-detection-ii/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3350 {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int pre = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && nums[i] > nums[i - 1]; i++);
            ans = max({ans, min(pre, i - start), (i - start) / 2});
            pre = i - start;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3350 solu;
    cout << solu.maxIncreasingSubarrays(*new vector<int>{2,5,7,8,9,2,3,4,3,1}) << endl;
    return 0;
}