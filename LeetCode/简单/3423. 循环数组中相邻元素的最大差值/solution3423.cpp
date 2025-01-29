/*
url: https://leetcode.cn/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/
标签: LeetCode第148场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3423 {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size();
        int ans = abs(nums[0] - nums[n - 1]);
        for (int i = 1; i < n; i++) ans = max(ans, abs(nums[i] - nums[i - 1]));
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}